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
 * @st_funcMD5		F6CE3AA056D2303BC48EC140E01279AC
 * @st_funcID		LCCM655R0.FILE.007.FUNC.001
 */
void vFCU_BRAKES__Init(void)
{
	Luint8 u8Counter;

	//init the state machine variables
	sFCU.eBrakeStates = BRAKE_STATE__IDLE;
	sFCU.sBrakesDev.u8DevMode = 0U;
	sFCU.sBrakesDev.u32DevKey = 0U;

	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{
		//setup the fault flags
		vFAULTTREE__Init(&sFCU.sBrakes[u8Counter].sFaultFlags);

		sFCU.sBrakes[u8Counter].sCurrent.f32ScrewPos_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sCurrent.f32IBeam_mm = 0.0F;
		sFCU.sBrakes[u8Counter].sCurrent.f32MLP_mm = 0.0F;
	}

	//init the limit switches
	vFCU_BRAKES_SW__Init();

	//init the MLP sensor
	vFCU_BRAKES_MLP__Init();

	//init the stepper rotate module
	vFCU_BRAKES_STEP__Init();

	//any ethernet stuff as needed
	vFCU_BRAKES_ETH__Init();

}

/***************************************************************************//**
 * @brief
 * Process any brakes tasks.
 * 
 * @st_funcMD5		75C796A5A849FD25A9B5FCFFBB25E6E5
 * @st_funcID		LCCM655R0.FILE.007.FUNC.002
 */
void vFCU_BRAKES__Process(void)
{
	Luint8 u8Test;

	//process the stepper driver if its active
	vSTEPDRIVE__Process();

	//Process the MLP
	vFCU_BRAKES_MLP__Process();

	//process the switches
	vFCU_BRAKES_SW__Process();

	switch(sFCU.eBrakeStates)
	{

		case BRAKE_STATE__IDLE:
			//idle state, wait here until we are commanded to move via a chance state.

			break;

		case BRAKE_STATE__BEGIN_MOVE:
			//begin to move the brakes, setup the movement planner
			//compare brake distances with known postion, limit switch postion and MLP position before moving.
			//alert upper layer if movement not possible due to position sensor error

			sFCU.eBrakeStates = BRAKE_STATE__MOVING;

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
				sFCU.eBrakeStates = BRAKE_STATE__MOVE_STOPPED;
			}


			break;

		case BRAKE_STATE__MOVE_STOPPED:
			//once we have completed moving, switch to stop state

			//once stopped go back to idle state
			break;


		case BRAKE_STATE__FAULT:

			//a fault has occurred
			break;

		case BRAKE_STATE__TEST:
			//just LG test area.
			vFCU_BRAKES__Move_IBeam_Distance_mm(500);
			break;


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



//permit brake development/testing mode
//Key1 should be 0xABCD0987U
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Key1		## Desc ##
 * @param[in]		u32Key0		## Desc ##
 * @st_funcMD5		DD5AE64FE86CF4E1876898239A4D8937
 * @st_funcID		LCCM655R0.FILE.007.FUNC.010
 */
void vFCU_BRAKES__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1)
{

	if(u32Key0 == 0x01293847U)
	{
		//activate mode
		sFCU.sBrakesDev.u8DevMode = 1U;
		sFCU.sBrakesDev.u32DevKey = u32Key1;
	}
	else
	{
		//disable mode
		sFCU.sBrakesDev.u8DevMode = 0U;
		sFCU.sBrakesDev.u32DevKey = 0U;
	}



}


//huge caution, this can kill the magnets
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Position		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		E0074F5868F10D2D16D8B94B032C1EA0
 * @st_funcID		LCCM655R0.FILE.007.FUNC.011
 */
void vFCU_BRAKES__Dev_MoveMotor(Luint32 u32Index, Luint32 u32Position)
{

	if(sFCU.sBrakesDev.u8DevMode == 1U)
	{
		//check the safety key
		if(sFCU.sBrakesDev.u32DevKey == 0xABCD0987U)
		{

			switch(u32Index)
			{
				case 0:
					vFCU_BRAKES_STEP__Move(u32Position, 0U);
					break;
				case 1:
					vFCU_BRAKES_STEP__Move(0U, u32Position);
					break;
				case 2:
					vFCU_BRAKES_STEP__Move(u32Position, u32Position);
					break;
				default:
					//do nothing.
					break;
			}//switch(u32Index)

		}
		else
		{
			//key wrong
		}
	}
	else
	{
		//not enabled
	}

}


//move the brakes to a distance in MM from the I Beam
//approx distances are 25mm (fully open) to 0mm (fully closed)
//some calibration will be needed here.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Distance		## Desc ##
 * @st_funcMD5		17768A6EF4640223240BC52B342622A4
 * @st_funcID		LCCM655R0.FILE.007.FUNC.008
 */
void vFCU_BRAKES__Move_IBeam_Distance_mm(Luint32 u32Distance)
{

	//temp

	//Tell the movement planner to go
	vFCU_BRAKES_STEP__Move(2000, 2000);

	//change state
	sFCU.eBrakeStates = BRAKE_STATE__BEGIN_MOVE;
}

//move the brakes position by a certain percentage between 0-100%
//approx distances are 25mm (fully open) to 0mm (fully closed)
//some calibration will be needed here.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		eBrake					The brake index
 * @param[in]		f32Percent		## Desc ##
 * @st_funcMD5		661C17121624146AA0AB15490D2D66B9
 * @st_funcID		LCCM655R0.FILE.007.FUNC.009
 */
void vFCU_BRAKES__Move_Percent_Position(Lfloat32 f32Percent, E_FCU__BRAKE_INDEX_T eBrake)
{
	if((f32Percent < 0) || (f32Percent > 100))
	{
		//do nothing
	}
	else
	{
		if(eBrake < FCU_BRAKE__MAX_BRAKES)
		{
			//set BrakePosition_Percent to value
			sFCU.sBrakes[(Luint32)eBrake].sMLP.f32BrakePosition_mm = f32Percent;
		}
	}
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

