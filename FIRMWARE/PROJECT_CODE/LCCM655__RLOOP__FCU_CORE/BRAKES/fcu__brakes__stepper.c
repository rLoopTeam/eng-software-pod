/**
 * @file		FCU__BRAKES__STEPPER.C
 * @brief		Stepper interface for the brakes.
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
 * @addtogroup FCU__BRAKES__STEPPER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//locals
void vFCU_BRAKES_STEP__LimitMove(Lint32 s32Brake0PosIn, Lint32 s32Brake1PosIn, Lint32 *ps32Brake0PosOut, Lint32 *ps32Brake1PosOut);

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the stepper interface
 * 
 * @st_funcMD5		D30F783904FC50285A0DBBD96FACE951
 * @st_funcID		LCCM655R0.FILE.025.FUNC.001
 */
void vFCU_BRAKES_STEP__Init(void)
{
	Luint8 u8Test;

	//init any IO as neede

	//setup the stepper drive system
	vSIL3_STEPDRIVE__Init();

	//reload the memory
	//check the CRC
	u8Test = u8SIL3_EEPARAM_CRC__Is_CRC_OK(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
	if(u8Test == 1U)
	{
		//valid
		sFCU.sBrakes[0].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC);
		sFCU.sBrakes[0].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL);
		sFCU.sBrakes[1].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC);
		sFCU.sBrakes[1].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL);

	}//if(u8Test == 1U)
	else
	{
		//CRC is invalid
		vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC, 1000U, DELAY_T__DELAYED_WRITE);
		vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL, 10000U, DELAY_T__DELAYED_WRITE);
		vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC, 1000U, DELAY_T__DELAYED_WRITE);
		vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL, 10000U, DELAY_T__IMMEDIATE_WRITE);

		//redo the CRC;
		vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);

		//1. Reload the structures.
		sFCU.sBrakes[0].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC);
		sFCU.sBrakes[0].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL);
		sFCU.sBrakes[1].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC);
		sFCU.sBrakes[1].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL);

		//set the flags for a general fault and cal data reload fault.
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sBrakesGlobal.sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sBrakesGlobal.sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);


	}//else if(u8Test == 1U)

}

/***************************************************************************//**
 * @brief
 * Process any brake commands
 * 
 * @st_funcMD5		792382B2C7B93024D59EDDDE0DBD345D
 * @st_funcID		LCCM655R0.FILE.025.FUNC.002
 */
void vFCU_BRAKES_STEP__Process(void)
{


}

/***************************************************************************//**
 * @brief
 * Returns the current position of the lead screw for the brakes
 * 
 * @param[in]		eBrake				The brake index
 * @st_funcMD5		3BF5E1F91C16F1F30165C47A35510773
 * @st_funcID		LCCM655R0.FILE.025.FUNC.003
 */
Lint32 s32FCU_BRAKES__Get_CurrentPos(E_FCU__BRAKE_INDEX_T eBrake)
{
	return s32SIL3_STEPDRIVE_POSITION__Get_Position((Luint8)eBrake);
}


/***************************************************************************//**
 * @brief
 * Move the brakes as a pair to a position based on the lead screw distance
 * 
 * @param[in]		s32Brake1Pos				Microns of brake pos R
 * @param[in]		s32Brake0Pos				Microns on brake pos L
 * @st_funcMD5		3B43DC76587675958F6129042FEBF569
 * @st_funcID		LCCM655R0.FILE.025.FUNC.004
 */
void vFCU_BRAKES_STEP__Move(Lint32 s32Brake0Pos, Lint32 s32Brake1Pos)
{
	Lint16 s16Return;

	//The poistion to move to in microns
	Lint32 s32Pos[2];

	//The linear velocity for the move
	Lint32 s32Velocity[2];

	//The linear accel for the move.
	Lint32 s32Accel[2];

	/** Unique ID for each task */
	Luint32 u32TaskID;


	//format the move
	//s32Pos[0] = s32Brake0Pos;
	//s32Pos[1] = s32Brake1Pos;

	s32Velocity[0] = sFCU.sBrakes[0].sMove.s32LinearVeloc;
	s32Velocity[1] = sFCU.sBrakes[1].sMove.s32LinearVeloc;

	//note this must be larger than target accel / microns/revrate
	s32Accel[0] = sFCU.sBrakes[0].sMove.s32LinearAccel;
	s32Accel[1] = sFCU.sBrakes[1].sMove.s32LinearAccel;

	//just a dummy task ID
	u32TaskID = sFCU.sBrakesGlobal.u32MoveTaskID;

	//clear the prev task if needed.
	vSIL3_STEPDRIVE__Clear_TaskComplete();

	vFCU_BRAKES_STEP__LimitMove(s32Brake0Pos, s32Brake1Pos, &s32Pos[0], &s32Pos[1]);

	//command the stepper to actual position, it will start moving based on timer interrupts
	//it is OK to do address of near here because we copy into the move planner in this call.
	s16Return = s16SIL3_STEPDRIVE_POSITION__Set_Position(&s32Pos[0], &s32Velocity[0], &s32Accel[0], u32TaskID);

	//check the return to see if we were able to move.

	//int the task ID
	sFCU.sBrakesGlobal.u32MoveTaskID++;

}


//before we move check the values of the limit swtiches and if needed limit the move in one direction
void vFCU_BRAKES_STEP__LimitMove(Lint32 s32Brake0PosIn, Lint32 s32Brake1PosIn, Lint32 *ps32Brake0PosOut, Lint32 *ps32Brake1PosOut)
{


	if(sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
	{
		//prevent movements less than 0
		if(s32Brake0PosIn < 0)
		{
			*ps32Brake0PosOut = 0;
		}
		else
		{
			*ps32Brake0PosOut = s32Brake0PosIn;
		}

	}
	else
	{
		*ps32Brake0PosOut = s32Brake0PosIn;
	}

	if(sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].eSwitchState == SW_STATE__CLOSED)
	{
		//prevent movements > 75mm
		if(s32Brake0PosIn > 75000)
		{
			*ps32Brake0PosOut = 75000;
		}
		else
		{
			*ps32Brake0PosOut = s32Brake0PosIn;
		}
	}
	else
	{
		*ps32Brake0PosOut = s32Brake0PosIn;
	}

	if(sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].eSwitchState == SW_STATE__CLOSED)
	{
		//prevent movements less than 0
		if(s32Brake1PosIn < 0)
		{
			*ps32Brake1PosOut = 0;
		}
		else
		{
			*ps32Brake1PosOut = s32Brake1PosIn;
		}
	}
	else
	{
		*ps32Brake1PosOut = s32Brake1PosIn;
	}

	if(sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].eSwitchState == SW_STATE__CLOSED)
	{
		//prevent movements > 75mm
		if(s32Brake1PosIn > 75000)
		{
			*ps32Brake1PosOut = 75000;
		}
		else
		{
			*ps32Brake1PosOut = s32Brake1PosIn;
		}
	}
	else
	{
		*ps32Brake1PosOut = s32Brake1PosIn;
	}

}


//update the veloc and accel values.
void vFCU_BRAKES_STEP__UpdateValues(Luint32 u32Brake, Luint32 u32Type, Lint32 s32Value)
{

	//handle the brake channel
	switch(u32Brake)
	{

		case 0:

			//handle the variable type
			switch(u32Type)
			{
				case 0:
					vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC, s32Value, DELAY_T__IMMEDIATE_WRITE);
					//redo the CRC;
					vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
					sFCU.sBrakes[0].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC);
					break;

				case 1:
					vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL, s32Value, DELAY_T__IMMEDIATE_WRITE);
					//redo the CRC;
					vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
					sFCU.sBrakes[0].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL);
					break;
				default:
					break;
			}
			break;

		case 1:
			//handle the variable type
			switch(u32Type)
			{
				case 0:
					vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC, s32Value, DELAY_T__IMMEDIATE_WRITE);
					//redo the CRC;
					vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
					sFCU.sBrakes[1].sMove.s32LinearVeloc = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC);
					break;

				case 1:
					vSIL3_EEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL, s32Value, DELAY_T__IMMEDIATE_WRITE);
					//redo the CRC;
					vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
															C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
					sFCU.sBrakes[1].sMove.s32LinearAccel = s32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL);
					break;
				default:
					break;
			}
			break;

		default:
			break;


	}//switch(u32Brake)


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

