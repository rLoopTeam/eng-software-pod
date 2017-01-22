/**
 * @file		FCU__BRAKES.C
 * @brief		Brake control subsystem for the FCU
 *
 * @note
 * When the brake is fully deployed the airgap is 2.5 mm.
 * The airgap increases by tan 17 deg x mm moved by lead screw.
 * If counting revolutions, every rotation of the ball screw moves the wedge 3 mm.
 * 0.9172 mm airgap increase per revolution.
 *
 * @NOTE
 * http://confluence.rloop.org/display/SD/5.+Control+Eddy+Brakes
 * http://confluence.rloop.org/display/SD/Brake+Control
 *
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__BRAKES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init any brakes variables, etc.
 * 
 * @st_funcMD5		5365FE6C1140E5A501525B2F171D7CEB
 * @st_funcID		LCCM655R0.FILE.007.FUNC.001
 */
void vFCU_BRAKES__Init(void)
{
	Luint8 u8Counter;

	//init the state machine variables
	sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__RESET;
	sFCU.sBrakesGlobal.u32MoveTaskID = 0U;
	sFCU.sBrakesGlobal.u8Timer_100ms = 0U;

	//setup the fault flags
	vFAULTTREE__Init(&sFCU.sBrakesGlobal.sFaultFlags);

	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{

		sFCU.sBrakes[u8Counter].sCurrent.f32ScrewPos_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sCurrent.f32IBeam_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sCurrent.f32MLP_mm = 0.0F;

		sFCU.sBrakes[u8Counter].sTarget.f32IBeam_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sTarget.f32LeadScrew_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sTarget.u32LeadScrew_um = 0U;
	}

	//init the limit switches
	vFCU_BRAKES_SW__Init();

	//init the MLP sensor
	vFCU_BRAKES_MLP__Init();

	//init the stepper rotate module
	vFCU_BRAKES_STEP__Init();

	//any ethernet stuff as needed
	vFCU_BRAKES_ETH__Init();

	//setup the claibration system
	vFCU_BRAKES_CAL__Init();

	//brakes watchdog
	vFCU_BRAKES_WDT__Init();

}

/***************************************************************************//**
 * @brief
 * Process any brakes tasks.
 * 
 * @st_funcMD5		4685D605141B18C8E55D1490ABB0DC0C
 * @st_funcID		LCCM655R0.FILE.007.FUNC.002
 */
void vFCU_BRAKES__Process(void)
{
	Luint8 u8Test;
	Lfloat32 f32Temp;
	Luint8 u8Counter;

	//process the stepper driver if its active
	vSTEPDRIVE__Process();

	//Process the MLP
	vFCU_BRAKES_MLP__Process();

	//process the switches
	vFCU_BRAKES_SW__Process();

	//process any calibration tasks
	vFCU_BRAKES_CAL__Process();

	switch(sFCU.sBrakesGlobal.eBrakeStates)
	{

		case BRAKE_STATE__RESET:
			//we have come out of reset, and now need to calibrate the brakes before they can be used.

			//
			break;

		case BRAKE_STATE__BEGIN_CAL:
			//being the calibration process
			vFCU_BRAKES_CAL__BeginCal(0x00112233U);

			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__WAIT_CAL_DONE;
			break;

		case BRAKE_STATE__WAIT_CAL_DONE:

			//monitor the state
			sFCU.sBrakes[(Luint8)FCU_BRAKE__LEFT].sMove.s32currentPos = s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__LEFT);
			sFCU.sBrakes[(Luint8)FCU_BRAKE__RIGHT].sMove.s32currentPos = s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__RIGHT);


			u8Test = u8FCU_BRAKES_CAL__Is_Busy();
			if(u8Test == 1U)
			{
				//still busy wait here
			}
			else
			{
				//done calibrating, move states
				sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__IDLE;

				//clear the cal in progress flag
				vFAULTTREE__Clear_Flag(&sFCU.sBrakesGlobal.sFaultFlags, 30U);
			}
			break;


		case BRAKE_STATE__IDLE:
			//idle state, wait here until we are commanded to move via a chance state.

			break;

		case BRAKE_STATE__BEGIN_MOVE:
			//begin to move the brakes, setup the movement planner
			//compare brake distances with known postion, limit switch postion and MLP position before moving.
			//alert upper layer if movement not possible due to position sensor error

			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__COMPUTE;

			break;

		case BRAKE_STATE__COMPUTE:

			//compute the planned move, take the I-beam request and translate into linear screw pos

			//we compute for each brake side.
			//While it seams redundant, we could apply some real-world hardware offets here
			for(u8Counter = 0U; u8Counter < FCU_BRAKE__MAX_BRAKES; u8Counter++)
			{
				//get the target I-Beam distance
				f32Temp = sFCU.sBrakes[u8Counter].sTarget.f32IBeam_mm;

				//equation:
				//screw_pos = tan(17) * ibeam_dist

				//div by Tan(17)
				f32Temp /= 0.305730681F;

				//because our min brake gap is 2.5mm, and this should equal to 0mm lead screw, we
				//need to subtract -2.5mm/tan(17)
				f32Temp -= 8.1771F;

				//convert to a target distance
				sFCU.sBrakes[u8Counter].sTarget.f32LeadScrew_mm = f32Temp;

				//to microns
				f32Temp *= 1000.0F;
				sFCU.sBrakes[u8Counter].sTarget.u32LeadScrew_um = (Luint32)f32Temp;

			}//for(u8Counter = 0U; u8Counter < FCU_BRAKE__MAX_BRAKES; u8Counter++)

			//clear the previous task flag
			vSTEPDRIVE__Clear_TaskComplete();

			//feed this to the stepper system
			vFCU_BRAKES_STEP__Move(sFCU.sBrakes[0].sTarget.u32LeadScrew_um, sFCU.sBrakes[1].sTarget.u32LeadScrew_um);

			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__MOVING;
			break;

		case BRAKE_STATE__MOVING:
			//the brakes are moving,
			//monitor their performance by getting the current pos from the move planner
			//check the MLP (it will lag)
			//process any PID algo's here too

			//check the movement planner
			sFCU.sBrakes[(Luint8)FCU_BRAKE__LEFT].sMove.s32currentPos = s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__LEFT);
			sFCU.sBrakes[(Luint8)FCU_BRAKE__RIGHT].sMove.s32currentPos = s32FCU_BRAKES__Get_CurrentPos(FCU_BRAKE__RIGHT);

			//todo, compute the brake position in terms of Ibeam distance.


			//check to see if the curent move task is done.
			u8Test = u8STEPDRIVE__Get_TaskComplete();
			if(u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				//change state
				sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__MOVE_STOPPED;
			}


			break;

		case BRAKE_STATE__MOVE_STOPPED:
			//once we have completed moving, switch to stop state

			//once stopped go back to idle state
			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__IDLE;
			break;


		case BRAKE_STATE__FAULT:

			//a fault has occurred
			break;

		default:
			//do nothing
			break;

	}//switch(sFCU.sBrakesGlobal.eBrakeStates)


	//handle WDT tasks
	if(sFCU.sBrakesGlobal.u8Timer_100ms == 2U)
	{
		//watchdog start
		vFCU_BRAKES_WDT__Pet_Start();

	}
	else if(sFCU.sBrakesGlobal.u8Timer_100ms >= 4U)
	{

		//watchdog end
		vFCU_BRAKES_WDT__Pet_End();

		sFCU.sBrakesGlobal.u8Timer_100ms = 0U;
	}
	else
	{
		//fall on
	}

}


/***************************************************************************//**
 * @brief
 * must start calibration from the ground station to put the brakes into a mode
 * where they can be used.
 * 
 * @param[in]		u32Key				0x98765432U
 * @st_funcMD5		EE29EBB23A41C03E43DD253219CFD50C
 * @st_funcID		LCCM655R0.FILE.007.FUNC.009
 */
void vFCU_BRAKES__Begin_Init(Luint32 u32Key)
{

	//can only cal from reset state
	if(sFCU.sBrakesGlobal.eBrakeStates == BRAKE_STATE__RESET)
	{
		if(u32Key == 0x98765432U)
		{
			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__BEGIN_CAL;

			//we should also set a flag
			vFAULTTREE__Set_Flag(&sFCU.sBrakesGlobal.sFaultFlags, 30U);
		}
		else
		{
			//error wrong key
		}
	}
	else
	{
		//error not in reset state
	}

}


/***************************************************************************//**
 * @brief
 * Gets the computed screw position
 * 
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		9CBBBE5E8D057A34CAE54C50F502D802
 * @st_funcID		LCCM655R0.FILE.007.FUNC.003
 */
Lfloat32 f32FCU_BRAKES__Get_ScrewPos(E_FCU__BRAKE_INDEX_T eBrake)
{
	return sFCU.sBrakes[(Luint8)eBrake].sCurrent.f32ScrewPos_mm;
}

/***************************************************************************//**
 * @brief
 * Returns the brake switch state
 * 
 * @st_tsID			LCCM655R0.TS.000
 *
 * @param[in]		eSwitch					The switch type
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		458791C58F924A8B4F72976BC03CD51D
 * @st_funcID		LCCM655R0.FILE.007.FUNC.004
 */
E_FCU__SWITCH_STATE_T eFCU_BRAKES__Get_SwtichState(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch)
{
	return sFCU.sBrakes[eBrake].sLimits[eSwitch].eSwitchState;
}

/***************************************************************************//**
 * @brief
 * Get the RAW ADC values
 * 
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		8BA9CA2F3074B6DB93DAD5CAA61B4C01
 * @st_funcID		LCCM655R0.FILE.007.FUNC.005
 */
Luint16 u16FCU_BRAKES__Get_ADC_Raw(E_FCU__BRAKE_INDEX_T eBrake)
{
	return sFCU.sBrakes[(Luint8)eBrake].sMLP.u16ADC_Sample;
}

/***************************************************************************//**
 * @brief
 * Get the distance between the brake and the I-Beam
 * 
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		26D65B8A8047383128E9ED614EEF4349
 * @st_funcID		LCCM655R0.FILE.007.FUNC.006
 */
Lfloat32 f32FCU_BRAKES__Get_IBeam_mm(E_FCU__BRAKE_INDEX_T eBrake)
{
	return sFCU.sBrakes[(Luint8)eBrake].sCurrent.f32IBeam_mm;
}

/***************************************************************************//**
 * @brief
 * Get the computed MLP measurement
 * 
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		822B17DF4905F7682819FF79F9101BBB
 * @st_funcID		LCCM655R0.FILE.007.FUNC.007
 */
Lfloat32 f32FCU_BRAKES__Get_MLP_mm(E_FCU__BRAKE_INDEX_T eBrake)
{
	return sFCU.sBrakes[(Luint8)eBrake].sCurrent.f32MLP_mm;
}


/***************************************************************************//**
 * @brief
 * Move the brakes to a distance in microns from the I Beam
 *
 * @note
 * Approx distances are 25,000 um (fully open) to 0um (fully closed)
 * 
 * @param[in]		u32Distance				The distance in microns
 * @st_funcMD5		609D069BE1337B6F02723640B571D4A9
 * @st_funcID		LCCM655R0.FILE.007.FUNC.008
 */
void vFCU_BRAKES__Move_IBeam_Distance_mm(Lfloat32 f32Distance)
{

	//stop upper layers interfering if we have development mode on
	if((sFCU.sBrakesGlobal.sBrakesDev.u8DevMode != 1U) && (sFCU.sBrakesGlobal.sBrakesDev.u32DevKey != 0xABCD0987U))
	{
		//we know each brake has to move proportionally, they can't move independantly.

		//remember here our min brake distance is 2.500mm, if we go lower than this
		if(f32Distance < C_FCU__BRAKES__MIN_IBEAM_DIST_MM)
		{
			//tell the target distance for both brakes
			sFCU.sBrakes[0].sTarget.f32IBeam_mm = C_FCU__BRAKES__MIN_IBEAM_DIST_MM;
			sFCU.sBrakes[1].sTarget.f32IBeam_mm = C_FCU__BRAKES__MIN_IBEAM_DIST_MM;

		}
		else
		{
			if(f32Distance > C_FCU__BRAKES__MAX_IBEAM_DIST_MM)
			{
				//tell the target distance for both brakes
				sFCU.sBrakes[0].sTarget.f32IBeam_mm = C_FCU__BRAKES__MAX_IBEAM_DIST_MM;
				sFCU.sBrakes[1].sTarget.f32IBeam_mm = C_FCU__BRAKES__MAX_IBEAM_DIST_MM;

			}
			else
			{
				//tell the target distance for both brakes
				sFCU.sBrakes[0].sTarget.f32IBeam_mm = f32Distance;
				sFCU.sBrakes[1].sTarget.f32IBeam_mm = f32Distance;
			}
		}



		//change state
		//Don't change state if we are not idle.
		if(sFCU.sBrakesGlobal.eBrakeStates == BRAKE_STATE__IDLE)
		{
			sFCU.sBrakesGlobal.eBrakeStates = BRAKE_STATE__BEGIN_MOVE;
		}
		else
		{
			//brake move not possible yet
			//todo: report back up the stack
		}

	}
	else
	{
		//we are in development mode, don't allow the upper level system to move the brakes.
	}


}

/***************************************************************************//**
 * @brief
 * 100ms timer input
 * 
 * @st_funcMD5		49FEC7B1A6D39C29B063D402AE617167
 * @st_funcID		LCCM655R0.FILE.007.FUNC.010
 */
void vFCU_BRAKES__100MS_ISR(void)
{

	sFCU.sBrakesGlobal.u8Timer_100ms++;
}


void vFCU_BRAKES__10MS_ISR(void)
{
	#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_BRAKES == 1U
		//not exactly IDEAL, but has to be done here
		vDAQ_APPEND__U8(C_FCU_DAQ_SET__DAQ_FOR_BRAKES__CPU_LOAD_U8, u8RM4_CPULOAD__Get_LoadPercent());

		vDAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_BRAKES__LEFT_CURRENTPOS_S32, sFCU.sBrakes[(Luint8)FCU_BRAKE__LEFT].sMove.s32currentPos);
		vDAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_BRAKES__RIGHT_CURRENTPOS_S32, sFCU.sBrakes[(Luint8)FCU_BRAKE__RIGHT].sMove.s32currentPos);

		vDAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_BRAKES__LEFT_TARGET_U32, sFCU.sBrakes[(Luint8)FCU_BRAKE__LEFT].sTarget.u32LeadScrew_um);
		vDAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_BRAKES__RIGHT_TARGET_U32, sFCU.sBrakes[(Luint8)FCU_BRAKE__RIGHT].sTarget.u32LeadScrew_um);


	#endif
}


#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#ifndef C_LOCALDEF__LCCM655__ENABLE_BRAKES
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

