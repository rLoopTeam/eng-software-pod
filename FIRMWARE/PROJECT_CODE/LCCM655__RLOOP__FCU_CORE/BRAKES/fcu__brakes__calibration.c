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

	//set initial states
	sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__IDLE;
}

#if C_FCU_BRAKES__CAL_TYPE == 2U

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

			//setup some initial conditions to slowly retract the motors

			//set the position to -77mm this means that if the brakes are at fully EXTENDED we can
			//run back -77mm to below -0
			s32Pos_um[FCU_BRAKE__LEFT] = -77 * 1000;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//set the velocity to 1/10th of our normal veloc
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / 10;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//set the accel to 1/10th
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / 10;
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

		/** Step 4, extend a small amount (~2mm) from the retracted limit switches */
		case BRAKE_CAL_STATE__STEP4__EXTEND_FROM_RETRACT:

			//set 2mm
			s32Pos_um[FCU_BRAKE__LEFT] = 2 * 1000;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//keep the velocity low
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / 10;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//keep acceleration low
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / 10;
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
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP7_EXTEND_MOTORS;
			break;

			/** Extend both motors down to the brake limits of 2.5mm */
		case BRAKE_CAL_STATE__STEP7_EXTEND_MOTORS:

			//for this we should use the calculation tool

			//for now until we solve the math, lets take those to +72mm, at worst
			//we will hit the limits
			s32Pos_um[FCU_BRAKE__LEFT] = 72 * 1000;
			s32Pos_um[FCU_BRAKE__RIGHT] = s32Pos_um[FCU_BRAKE__LEFT];

			//keep the velocity low
			s32Velocity_um_s[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearVeloc_um_s / 10;
			s32Velocity_um_s[FCU_BRAKE__RIGHT] = s32Velocity_um_s[FCU_BRAKE__LEFT];

			//keep acceleration low
			s32Accel_um_ss[FCU_BRAKE__LEFT] = sFCU.sBrakes[FCU_BRAKE__LEFT].sMove.s32LinearAccel_um_ss / 10;
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
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__COMPLETE;
			}

			break;

		case BRAKE_CAL_STATE__COMPLETE:
			//we are done calibrating.
			//stay here for ever now.
			break;
#if 0
			case BRAKE_CAL_STATE__EXTEND_MOTORS:

				//we need to fully extend the lead screws to the fwd position.
				//Because we have zero at the fwd switches we could assume our brakes are fully retracted
				//so this will be +75.0, move -80.0mm from the worst pos as we should go to the limits
				if(sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
				{
					vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
					s32Pos_um[0] = 0;
				}
				else
				{
					s32Pos_um[0] = -80000;
				}

				if(sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
				{
					vSIL3_STEPDRIVE_ZERO__Set_Zero(1);
					s32Pos_um[1] = 0;
				}
				else
				{
					s32Pos_um[1] = -80000;
				}


				s32Velocity_um_s[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc_um_s / 10;
				s32Velocity_um_s[1] = s32Velocity_um_s[0];

				//note this must be larger than target accel / microns/revrate
				s32Accel_um_ss[0] = sFCU.sBrakes[0].sMove.s32LinearAccel_um_ss / 10;
				s32Accel_um_ss[1] = s32Accel_um_ss[0];

				//clear the prev task if needed.
				vSIL3_STEPDRIVE__Clear_TaskComplete();

				//command the stepper to actual position, it will start moving based on timer interrupts
				//it is OK to do address of near here because we copy into the move planner in this call.
				s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

				//check the return to see if we were able to move.

				//int the task ID
				sFCU.sBrakesGlobal.u32MoveTaskID++;

				//on win32 emulator, just as in the real pod we will hit our limit switches.

				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS;
				break;

			case BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS:
				//wait here until the motors retract, they will stop when hitting the axis switches
				//and they will be re-zero'd
				u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
				if(u8Test == 0U)
				{
					//stay in state
				}
				else
				{
					//move to the next state
					sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__RELEASE_ZERO;
				}

				break;

			case BRAKE_CAL_STATE__RELEASE_ZERO:

				//release the end stops, by manually setting the zero position
				vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
				vSIL3_STEPDRIVE_ZERO__Set_Zero(1);


				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__APPLY_NEW_ZERO;
				break;

			case BRAKE_CAL_STATE__APPLY_NEW_ZERO:

				s32Pos_um[0] = 10;
				s32Pos_um[1] = 10;
				s32Velocity_um_s[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc_um_s / 10;
				s32Velocity_um_s[1] = s32Velocity_um_s[0];
				s32Accel_um_ss[0] = sFCU.sBrakes[0].sMove.s32LinearAccel_um_ss / 10;
				s32Accel_um_ss[1] = s32Accel_um_ss[0];

				//clear the previous task flag
				vSIL3_STEPDRIVE__Clear_TaskComplete();

				//command the stepper to actual position, it will start moving based on timer interrupts
				s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);
				sFCU.sBrakesGlobal.u32MoveTaskID++;

				//if the limit switches don't permit symetrical operation, apply some new zero's here.
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__WAIT_NEW_ZERO;
				break;

			case BRAKE_CAL_STATE__WAIT_NEW_ZERO:

				u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
				if(u8Test == 0U)
				{
					//stay here until done
				}
				else
				{
					//if the limit switches don't permit symetrical operation, apply some new zero's here.
					//reset the zeros
					vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
					vSIL3_STEPDRIVE_ZERO__Set_Zero(1);

					//done
					sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__COMPLETE;

				}
				break;




			case BRAKE_CAL__TYPE2__RETRACT_RIGHT:

				//start retracting the right brake, and wait until the switch is closed

				//before we start the right brake was already closed, do ntohing
				if(sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].eSwitchState == SW_STATE__CLOSED)
				{
					vSIL3_STEPDRIVE_ZERO__Set_Zero_Defined(FCU_BRAKE__RIGHT, 75000);
					s32Pos_um[FCU_BRAKE__RIGHT] = 75000;
				}
				else
				{
					//move past 8K
					s32Pos_um[FCU_BRAKE__RIGHT] = 80000;
				}

				//do not move the left brake
				s32Pos_um[FCU_BRAKE__LEFT] = s32FCU_BRAKES__Get_CurrentPos_um(FCU_BRAKE__LEFT);

				s32Velocity_um_s[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc_um_s / 10;
				s32Velocity_um_s[1] = s32Velocity_um_s[0];

				//note this must be larger than target accel / microns/revrate
				s32Accel_um_ss[0] = sFCU.sBrakes[0].sMove.s32LinearAccel_um_ss / 10;
				s32Accel_um_ss[1] = s32Accel_um_ss[0];

				//clear the prev task if needed.
				vSIL3_STEPDRIVE__Clear_TaskComplete();

				//command the stepper to actual position, it will start moving based on timer interrupts
				//it is OK to do address of near here because we copy into the move planner in this call.
				s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

				//check the return to see if we were able to move.

				//int the task ID
				sFCU.sBrakesGlobal.u32MoveTaskID++;

				//on win32 emulator, just as in the real pod we will hit our limit switches.

				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL__TYPE2__WAIT_RETRACT_RIGHT;

				break;

			case BRAKE_CAL__TYPE2__WAIT_RETRACT_RIGHT:

				//wait until we have stopped moving
				u8Test = u8SIL3_STEPDRIVE_ACCEL__Get_AllMotorsIdle();
				if(u8Test == 0U)
				{
					//stay in state
				}
				else
				{
					//move to the next state
					sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL__TYPE2__RELEASE_RIGHT;
				}

				break;

			case BRAKE_CAL__TYPE2__RELEASE_RIGHT:

				//move right brake sligthly off the stop



				break;
#endif //0

			default:
				//?
				break;

		}//switch(sFCU.sBrakesGlobal.sCalibration.eState)

}

#endif //C_FCU_BRAKES__CAL_TYPE


#if C_FCU_BRAKES__CAL_TYPE == 1U

/***************************************************************************//**
 * @brief
 * Process any claibration tasks.
 * 
 * @st_funcMD5		444EB4D7518509D117F19E1E435E517D
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

		case BRAKE_CAL_STATE__EXTEND_MOTORS:

			//we need to fully extend the lead screws to the fwd position.
			//Because we have zero at the fwd switches we could assume our brakes are fully retracted
			//so this will be +75.0, move -80.0mm from the worst pos as we should go to the limits
			if(sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
			{
				vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
				s32Pos_um[0] = 0;
			}
			else
			{
				s32Pos_um[0] = -80000;
			}

			if(sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
			{
				vSIL3_STEPDRIVE_ZERO__Set_Zero(1);
				s32Pos_um[1] = 0;
			}
			else
			{
				s32Pos_um[1] = -80000;
			}


			s32Velocity_um_s[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc_um_s / 10;
			s32Velocity_um_s[1] = s32Velocity_um_s[0];

			//note this must be larger than target accel / microns/revrate
			s32Accel_um_ss[0] = sFCU.sBrakes[0].sMove.s32LinearAccel_um_ss / 10;
			s32Accel_um_ss[1] = s32Accel_um_ss[0];

			//clear the prev task if needed.
			vSTEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			//it is OK to do address of near here because we copy into the move planner in this call.
			s16Return = s16STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);

			//check the return to see if we were able to move.

			//int the task ID
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//on win32 emulator, just as in the real pod we will hit our limit switches.

			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS;
			break;

		case BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS:
			//wait here until the motors retract, they will stop when hitting the axis switches
			//and they will be re-zero'd
			u8Test = u8STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if(u8Test == 0U)
			{
				//stay in state
			}
			else
			{
				//move to the next state
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__RELEASE_ZERO;
			}

			break;

		case BRAKE_CAL_STATE__RELEASE_ZERO:

			//release the end stops, by manually setting the zero position
			vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
			vSIL3_STEPDRIVE_ZERO__Set_Zero(1);


			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__APPLY_NEW_ZERO;
			break;

		case BRAKE_CAL_STATE__APPLY_NEW_ZERO:

			s32Pos_um[0] = 10;
			s32Pos_um[1] = 10;
			s32Velocity_um_s[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc_um_s / 10;
			s32Velocity_um_s[1] = s32Velocity_um_s[0];
			s32Accel_um_ss[0] = sFCU.sBrakes[0].sMove.s32LinearAccel_um_ss / 10;
			s32Accel_um_ss[1] = s32Accel_um_ss[0];

			//clear the previous task flag
			vSTEPDRIVE__Clear_TaskComplete();

			//command the stepper to actual position, it will start moving based on timer interrupts
			s16Return = s16STEPDRIVE_POSITION__Set_Position(&s32Pos_um[0], &s32Velocity_um_s[0], &s32Accel_um_ss[0], sFCU.sBrakesGlobal.u32MoveTaskID);
			sFCU.sBrakesGlobal.u32MoveTaskID++;

			//if the limit switches don't permit symetrical operation, apply some new zero's here.
			sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__WAIT_NEW_ZERO;
			break;

		case BRAKE_CAL_STATE__WAIT_NEW_ZERO:
	
			u8Test = u8STEPDRIVE_ACCEL__Get_AllMotorsIdle();
			if(u8Test == 0U)
			{
				//stay here until done
			}
			else
			{
				//if the limit switches don't permit symetrical operation, apply some new zero's here.
				//reset the zeros
				vSIL3_STEPDRIVE_ZERO__Set_Zero(0);
				vSIL3_STEPDRIVE_ZERO__Set_Zero(1);

				//done
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

#endif


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
	if(sFCU.sBrakesGlobal.sCalibration.eState == BRAKE_CAL_STATE__IDLE)
	{
		//start
		if(u32Key == 0x00112233U)
		{
			#if C_FCU_BRAKES__CAL_TYPE == 1U
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__EXTEND_MOTORS;
			#else
				sFCU.sBrakesGlobal.sCalibration.eState = BRAKE_CAL_STATE__STEP1__RETRACT_MOTORS;
			#endif
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

