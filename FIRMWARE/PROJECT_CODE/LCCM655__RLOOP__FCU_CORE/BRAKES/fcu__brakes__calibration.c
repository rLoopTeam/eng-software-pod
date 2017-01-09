/**
 * @file		FCU__BRAKES__CALIBRATION.C
 * @brief		Brake Calibration Routines
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
 * @addtogroup FCU__BRAKES__CAL
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//the structure
extern struct _strFCU sFCU;

/*
Keith (Kstorminator) [MFG, Mech, Syst] [6:35 PM]
@safetylok 2.5 mm air gap fully deployed at the switch (but the hard stop is about 2.2 or 2.3 mm air gap) and
24.4 mm air gap when fully retracted.  It also depends if you are triggering the switch at the ends by
switching at the first change in the switch or are you going by the switch and then slowly backing
up until the switch just returns to normal (that is how my Haas X & Y & Z axis are zeroed)
it goes by and then slowly backs up until changing switch again back to what it is in the working area
of the table.  These distances are the magnet to aluminum rail web (not the distances measured by the
laser measurement sensors to the beam web).
 */


void vFCU_BRAKES_CAL__Init(void)
{

	//set initial states
	sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__IDLE;
}


void vFCU_BRAKES_CAL__Process(void)
{

	//The poistion to move to in microns
	Lint32 s32Pos[2];

	//The linear velocity for the move
	Lint32 s32Velocity[2];

	//The linear accel for the move.
	Lint32 s32Accel[2];

	Lint16 s16Return;


	switch(sFCU.sBrakesGlobal.sCalibration.eState)
	{

		case BRAKE_CAL_STATE__IDLE:
			//we stay here until told to being retracting motors.
			break;

		case BRAKE_CAL_STATE__RETRACT_MOTORS:

			//we need to fully retract the motors backwards until we hit the limit swiches

			//move back to -100mm
			s32Pos[0] = -100000;
			s32Pos[1] = -100000;


			s32Velocity[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc;
			s32Velocity[1] = sFCU.sBrakes[1].sMove.s32LinearVeloc;

			//note this must be larger than target accel / microns/revrate
			s32Accel[0] = sFCU.sBrakes[0].sMove.s32LinearAccel;
			s32Accel[1] = sFCU.sBrakes[1].sMove.s32LinearAccel;

			//clear the prev task if needed.
			vSTEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			//it is OK to do address of near here because we copy into the move planner in this call.
			s16Return = s16STEPDRIVE_POSITION__Set_Position(&s32Pos[0], &s32Velocity[0], &s32Accel[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//check the return to see if we were able to move.

			//int the task ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//on win32 emulator, just as in the real pod we will hit our limit switches.

			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__WAIT_RETRACT_MOTORS;
			break;

		case BRAKE_CAL_STATE__WAIT_RETRACT_MOTORS:
			//wait here until the motors retract, they will stop when hitting the axis switches
			//and they will be re-zero'd
			break;

		case BRAKE_CAL_STATE__RELEASE_ZERO:
			//release the end stops
			do
			{

			}while(u8STEPDRIVE_ACCEL__Get_AllMotorsIdle() == 0U);

			vSTEPDRIVE_ZERO__Set_Zero(0);
			vSTEPDRIVE_ZERO__Set_Zero(1);
			break;

		case BRAKE_CAL_STATE__COMPLETE:
			//we are done calibrating.
			break;

		default:
			//?
			break;

	}//switch(sFCU.sBrakesGlobal.sCalibration.eState)

}

//returns 1 if we are busy
Luint8 u8FCU_BRAKES_CAL__Is_Busy(void)
{
	Luint8 u8Return;

	if((sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__COMPLETE) || (sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__IDLE))
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;

}

//begin the calibration routine
void vFCU_BRAKES_CAL__BeginCal(Luint32 u32Key)
{
	if(sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__IDLE)
	{
		//start
		if(u32Key == 0x00112233U)
		{
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__RETRACT_MOTORS;
		}
		else
		{
			//big error
		}
	}
	else
	{
		//not in the right state yet
	}
}


#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

