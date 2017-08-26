/**
 * @file		FCU__BRAKES__CALIBRATION.C
 *
 *
 * @note
 * http://confluence.rloop.org/display/SD/Brake+Control
 *
 * Position Considerations
 * 1. Motors are at the FWD of the pod
 * 2. Fully RETRACTED = 0.0mm = Closest to the motor (FWD)
 * 3. Fully EXTENDED = ~75.0mm = AFT of the pod
 *
 * Procedure
 * 1. Retract both brakes in sequence. Its important to retract in sequence
 * 2. Stop each brake motor on the RETRACTED limit switch interrupt.
 * 3. Consider each brake motor at 0.0mm now
 * 4. Fully extend each brake motor to 72mm + a fudge factor. The FF is needed to bring the
 * 		brake pad distance to 2.5mm
 * 5. Check the range of the MLP sensors and calibrate accordingly
 *
 *
 *
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


// Calibration Types
// 1: Both Magnets
// 2: One magnet at a time.
#define C_FCU_BRAKES__CAL_TYPE				(2U)

//divide by to slow brakes down during cal.
#define C_BRAKES_CAL_SPEED_FACTOR (25)


//the structure
extern struct _strFCU sFCU;

/*
Keith Kstorminator [MFG, Mech, Syst] [6:35 PM]
@safetylok 2.5 mm air gap fully deployed at the switch (but the hard stop is about 2.2 or 2.3 mm air gap) and
24.4 mm air gap when fully retracted.  It also depends if you are triggering the switch at the ends by
switching at the first change in the switch or are you going by the switch and then slowly backing
up until the switch just returns to normal [that is how my Haas X & Y & Z axis are zeroed]
it goes by and then slowly backs up until changing switch again back to what it is in the working area
of the table.  These distances are the magnet to aluminum rail web (not the distances measured by the
laser measurement sensors to the beam web.
 */


/***************************************************************************//**
 * @brief
 * Init the calibration module.
 * 
 * @st_funcMD5		0D4C59962EF7DD7F98DCFA022EB3D530
 * @st_funcID		LCCM655R0.FILE.068.FUNC.002
 */
void vFCU_BRAKES_CAL__Init(void)
{

	sFCU.sBrakesGlobal.u8IgnoreRetractSwitches = 0U;
	sFCU.sBrakesGlobal.u8IgnoreExtendSwitches = 0U;

	//set initial states
	sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__IDLE;
}

/***************************************************************************//**
 * @brief
 * Calibration process to ensure brakes are RETRACTED in sequence
 * 
 * @st_funcMD5		D3D30A35BF6FF699F2CFBBC51D1466E5
 * @st_funcID		LCCM655R0.FILE.068.FUNC.003
 */
void vFCU_BRAKES_CAL__Process(void)
{

	//The poistion to move to in microns
	Lint32 s32Pos_um[2];

	//The linear velocity for the move
	Lint32 s32Velocity_um_s[2];

	//The linear accel for the move.
	Lint32 s32Accel_um_ss[2];
	Luint8 u8Test;
	Lint16 s16Return;


	switch(sFCU.sBrakesGlobal.sCalibration.eState)
	{

		case BRAKE_CAL_STATE__IDLE:
			//we stay here until told to being retracting motors.
			break;

		case BRAKE_CAL_STATE__STEP1__RETRACT_MOTORS:

			sFCU.sBrakesGlobal.u8IgnoreExtendSwitches = 1U;

			//set the current zero point and release any interrupts
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__LEFT);
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__RIGHT);

			//setup some initial conditions to slowly retract the motors

			//set the position to -77mm this means that if the brakes are at fully EXTENDED we can
			//run back -77mm to below -0
			s32Pos_um[FCU_BRAKE__LEFT] = -77 * 1000;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//set the velocity to 1/10th of our normal veloc
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / C_BRAKES_CAL_SPEED_FACTOR;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//set the accel to 1/10th
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / C_BRAKES_CAL_SPEED_FACTOR;
			s32Accel_um_ss[FCU_BRAKE__RIGHT] = s32Accel_um_ss[FCU_BRAKE__LEFT];

			//clear the previous task flag
			vSIL3_STEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//increment the movement task ID so as we can track ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//wait for the motors to hit the retract switches
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP2__WAIT_RETRACT_LIMITS;
			break;

		/** Step 2, wait until both motors have retracted and hit their limits */
		case BRAKE_CAL_STATE__STEP2__WAIT_RETRACT_LIMITS:

			//by checking if all motor state machines are IDLE we know both of the motors have stopped moving.
			u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if(u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				sFCU.sBrakesGlobal.u8IgnoreExtendSwitches = 0U;

				//move to the next state
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP3__RELEASE_RETRACT_ZERO;
			}

			break;

		/** Step 3, because we have run up against the brake limit switches
		 * Now we need to release the software interlocks.
		 */
		case BRAKE_CAL_STATE__STEP3__RELEASE_RETRACT_ZERO:

			//release the end stops, by manually setting the zero position
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__LEFT);
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__RIGHT);

			//next state, move off the endstops
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP4__EXTEND_FROM_RETRACT;
			break;

		/** Step 4, extend a small amount from the retracted limit switches */
		case BRAKE_CAL_STATE__STEP4__EXTEND_FROM_RETRACT:

			//ignore any bouncing interrupts.
			sFCU.sBrakesGlobal.u8IgnoreRetractSwitches = 1U;

			//set 2mm
			s32Pos_um[FCU_BRAKE__LEFT] = 250;
			s32Pos_um[FCU_BRAKE__RIGHT] = 2850;

			//keep the velocity low
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / C_BRAKES_CAL_SPEED_FACTOR;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//keep acceleration low
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / C_BRAKES_CAL_SPEED_FACTOR;
			s32Accel_um_ss[FCU_BRAKE__RIGHT] = s32Accel_um_ss[FCU_BRAKE__LEFT];

			//clear the previous task flag
			vSIL3_STEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//increment the task ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//if the limit switches don't permit symetrical operation, apply some new zero's here.
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP5__WAIT_EFR;
			break;

		/** Wait until all motos have stopped */
		case BRAKE_CAL_STATE__STEP5__WAIT_EFR:
			//by checking if all motor state machines are IDLE we know both of the motors have stopped moving.
			u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if(u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				//Clear the ignore
				sFCU.sBrakesGlobal.u8IgnoreRetractSwitches = 0U;

				//move to the next state, apply the new zero
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP6__APPLY_ZERO;
			}
			break;


		/** Call our 2mm position the new zero */
		case BRAKE_CAL_STATE__STEP6__APPLY_ZERO:

			//set the zero on both left and right motors
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__LEFT);
			vSIL3_STEPDRIVE_ZERO__Set_Zero(FCU_BRAKE__RIGHT);

			//do an extension check.
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP7_EXTEND_MOTORS; //BRAKE_CAL_STATE__COMPLETE
			break;

			/** Extend both motors down to the brake limits of 2.5mm */
		case BRAKE_CAL_STATE__STEP7_EXTEND_MOTORS:

			//for this we should use the calculation tool

			//for now until we solve the math, lets take those to +72mm, at worst
			//we will hit the limits
			s32Pos_um[FCU_BRAKE__LEFT] = 60000;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//keep the velocity low
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / C_BRAKES_CAL_SPEED_FACTOR;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//keep acceleration low
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / C_BRAKES_CAL_SPEED_FACTOR;
			s32Accel_um_ss[FCU_BRAKE__RIGHT] = s32Accel_um_ss[FCU_BRAKE__LEFT];

			//clear the previous task flag
			vSIL3_STEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//increment the task ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//if the limit switches don't permit symetrical operation, apply some new zero's here.
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP8_WAIT_EXTEND_MOTORS;
						
			break;

		case BRAKE_CAL_STATE__STEP8_WAIT_EXTEND_MOTORS:

			//wait until they are on targer
			u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if (u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				//move to the next state, apply the new zero
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP9_RETRACT_MOTORS;
			}

			break;

		case BRAKE_CAL_STATE__STEP9_RETRACT_MOTORS:

			//back to zer
			s32Pos_um[FCU_BRAKE__LEFT] = 0;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//full speed
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / C_BRAKES_CAL_SPEED_FACTOR;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//full accel
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / C_BRAKES_CAL_SPEED_FACTOR;
			s32Accel_um_ss[FCU_BRAKE__RIGHT] = s32Accel_um_ss[FCU_BRAKE__LEFT];

			//clear the previous task flag
			vSIL3_STEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//increment the task ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//if the limit switches don't permit symetrical operation, apply some new zero's here.
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP10_WAIT_RETRACT_MOTORS;
			break;

		case BRAKE_CAL_STATE__STEP10_WAIT_RETRACT_MOTORS:
			//wait until they are on targer
			u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if (u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				//move to the next state, apply the new zero
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__COMPLETE;
			}

			break;


		case BRAKE_CAL_STATE__COMPLETE:
			//we are done calibrating.
			//stay here for ever now.
			break;

		default:
			//?
			break;

		}//switch(sFCU.sBrakesGlobal.sCalibration.eState)

}

/***************************************************************************//**
 * @brief
 * returns 1 if we are busy
 * 
 * @st_funcMD5		50D0AE035BAB4BC40A403C24490A26C8
 * @st_funcID		LCCM655R0.FILE.068.FUNC.004
 */
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


/***************************************************************************//**
 * @brief
 * begin the calibration routine
 * 
 * @param[in]		u32Key				0x00112233U
 * @st_funcMD5		9B1223B11F79047CC907BFE442A9FE69
 * @st_funcID		LCCM655R0.FILE.068.FUNC.005
 */
void vFCU_BRAKES_CAL__BeginCal(Luint32 u32Key)
{
	if((sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__IDLE) || (sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__COMPLETE))

	{
		//start
		if(u32Key == 0x00112233U)
		{
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP1__RETRACT_MOTORS;
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

