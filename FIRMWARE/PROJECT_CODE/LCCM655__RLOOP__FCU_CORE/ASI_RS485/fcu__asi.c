/**
 * @file		FCU__ASI_RS485.C
 * @brief		RS485 interface to ASI controller
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
 * @addtogroup FCU__ASI_RS485
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

//the structure
extern struct _strFCU sFCU;

//locals

void vFCU_ASI__BuildCmdFrame(struct _strASICmd *pCmd);
Lint16 s16FCU_ASI__ProcessError(struct _strASICmd *pCmd);
void vFCU_ASI__SetErr(struct _strASICmd *pCmd);
void vFCU_ASI__MemCopy(Luint8 *pu8Dest, const Luint8 *cpu8Source, Luint32 u32Length);
Lint16 s16FCU_ASI__SendCommand(void);
Lint16 s16FCU_ASI__ProcessReply(void);


//Because of addx 1 always being responded to, we need to do from address 2 to 9
#define C_ASI__ADDX_OFFSET		(2U)

#define C_ASI__MAX_COMMAND_TIMEOUT 		(50U)


/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_ASI__Init(void)
{
	Lint16 s16Return;
	Luint8 u8Counter;
	Luint32 u32Test;

	vSIL3_FAULTTREE__Init(&sFCU.sASI.sFaultFlags);

	sFCU.sASI.u32Guard1 = 0xABCDABCDU;
	sFCU.sASI.u32Guard2 = 0x11223344U;

	sFCU.sASI.eMainState = ASI_STATE__IDLE;
	sFCU.sASI.u8ScanIndex = 0U;
	sFCU.sASI.u810MS_Timer = 0U;
	sFCU.sASI.u8MaxScanTime = 10U;
	sFCU.sASI.u8RxCount = 0U;
	sFCU.sASI.u32WaitCommandTimeout = 0U;


	//configure the multiplexer
	vFCU_ASI_MUX__Init();

	//eth layer
	vFCU_ASI_ETH__Init();

	//init the modbus master
	vSIL3_MODBUS__Init();


	//Note:
	//SC16's are already configured here with correct baud rate./

	//check the PHY
	u32Test = u32SIL3_SC16__Get_FaultFlags(C_FCU__SC16_ASI_INDEX);
	//rule out the Rx Fifo Overflow
	if((u32Test & (0x03 ^ 0xFFFFFFFF)) != 0U)
	{
		//opto fault
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__01);
	}
	else
	{
		//ok
	}


	//setup the command list
	sFCU.sASI.eCommandList[0] = C_FCU_ASI__FAULTS;
	sFCU.sASI.eCommandList[1] = C_FCU_ASI__MOTOR_CURRENT;
	sFCU.sASI.eCommandList[2] = C_FCU_ASI__CONT_TEMP;
	sFCU.sASI.eCommandList[3] = C_FCU_ASI__MOTOR_RPM;
	sFCU.sASI.eCommandList[4] = C_FCU_ASI__THROT_VOLTAGE;
	sFCU.sASI.u8CommandListIndex = 0U;

	//clear our holding data
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
	{
		//set the slave addx
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_SlaveAddx(u8Counter, u8Counter + C_ASI__ADDX_OFFSET);

		//setup the Modbus system to handle the slave data
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(u8Counter, 0, (C_FCU_ASI__FAULTS));
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(u8Counter, 1, (C_FCU_ASI__MOTOR_CURRENT));
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(u8Counter, 2, (C_FCU_ASI__CONT_TEMP));
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(u8Counter, 3, (C_FCU_ASI__MOTOR_RPM));
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(u8Counter, 4, (C_FCU_ASI__THROT_VOLTAGE));

		//default to inhibit
		vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterValue_Addx(u8Counter, C_FCU_ASI__FAULTS, 0xFFFFU);


		sFCU.sASI.sHolding[u8Counter].u16Faults = 0U;
		sFCU.sASI.sHolding[u8Counter].f32TempC = 0.0F;
		sFCU.sASI.sHolding[u8Counter].f32MotorCurrentA = 0.0F;
		sFCU.sASI.sHolding[u8Counter].u16RPM = 0U;
		sFCU.sASI.u8ThrottleCommand[u8Counter] = 0U;
		sFCU.sASI.u8SerialNetworkCommand[u8Counter] = 1U;
		sFCU.sASI.u32TimeoutCounts[u8Counter] = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Process any ASI tasks
 * 
 */
void vFCU_ASI__Process(void)
{
	Luint8 u8Temp;
	Luint8 u8ByteIndex;
	Lint16 s16Return;

	if(sFCU.sASI.u32Guard1 != 0xABCDABCDU)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__02);
	}

	if(sFCU.sASI.u32Guard2 != 0x11223344U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sASI.sFaultFlags, C_LCCM655__ASI__FAULT_INDEX__02);
	}

	//see if there is at least one byte of data avail in the FIFO's
	u8Temp = u8SIL3_SC16_USER__Get_ByteAvail(C_FCU__SC16_ASI_INDEX);
	if(u8Temp == 0U)
	{
		//no new data
	}
	else
	{
		//get the byte
		u8Temp = u8SIL3_SC16_USER__Get_Byte(C_FCU__SC16_ASI_INDEX);

		//Push to modbus stack
		vSIL3_MODBUS_UART__Rx_U8(u8Temp);

		//todo
		//clear any last seen flags.
	}


	//process the modbus master
	vSIL3_MODBUS__Process();

	//handle the mux
	vFCU_ASI_MUX__Process();

	//handle the main state machine
	switch(sFCU.sASI.eMainState)
	{
		case ASI_STATE__IDLE:

			//wait 100ms between scans
			if(sFCU.sASI.u810MS_Timer >= sFCU.sASI.u8MaxScanTime)
			{
				//change to send a command
				sFCU.sASI.eMainState = ASI_STATE__CONFIG_MUX;

				//clear the timer
				sFCU.sASI.u810MS_Timer = 0U;
			}
			else
			{
				//stay in state
			}

			break;

		case ASI_STATE__CONFIG_MUX:
			//setup the channel mux to our current channel
			//vFCU_ASI_MUX__SelectChannel(sFCU.sASI.u8ScanIndex);
			//vFCU_ASI_MUX__SelectChannel(7U);

			//clear the timeout
			sFCU.sASI.u32WaitCommandTimeout = 0U;

			//start issuing commands
			sFCU.sASI.eMainState = ASI_STATE__ISSUE_COMMAND;
			break;

		case ASI_STATE__ISSUE_COMMAND:

			//issue a read request
			u8Temp = u8SIL3_MODBUS_MASTER__Get_IsBusy();
			if(u8Temp == 0U)
			{
				//set the slave Addx to be n + 1 (i.e. first engine is 1)
				s16Return = s16SIL3_MODBUS_MASTER_CMD__Slave_Reqest_Read(sFCU.sASI.u8ScanIndex + C_ASI__ADDX_OFFSET,
																		 MODBUS_FUNCCODE__READ_MULTIPLE_HOLDING_REGS,
																		 sFCU.sASI.eCommandList[sFCU.sASI.u8CommandListIndex],
																		 1U);
				sFCU.sASI.eMainState = ASI_STATE__WAIT_COMMAND_COMPLETE;

				//clear the timeout
				sFCU.sASI.u32WaitCommandTimeout = 0U;

			}
			else
			{

				//see what happened on the last command
				s16Return = s16SIL3_MODBUS_MASTER__Get_LastErrorCode();
				if(s16Return < 0)
				{
					//we had some issue, negative error code
					sFCU.sASI.u32TimeoutCounts[sFCU.sASI.u8ScanIndex]++;

					//move on
					sFCU.sASI.u32WaitCommandTimeout = 0U;
					sFCU.sASI.eMainState = ASI_STATE__INC_SCAN_INDEX;

					//set the faults to all 1
					sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16Faults = 0xFFFFU;

				}
			}
			break;

		case ASI_STATE__WAIT_COMMAND_COMPLETE:

			u8Temp = u8SIL3_MODBUS_MASTER__Get_IsBusy();
			if(u8Temp == 0U)
			{

				s16Return = s16SIL3_MODBUS_MASTER__Get_LastErrorCode();
				if(s16Return >= 0)
				{
					//we passed the read check, now lets look at the packet
					switch(sFCU.sASI.eCommandList[sFCU.sASI.u8CommandListIndex])
					{

						case C_FCU_ASI__FAULTS:
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16Faults = u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(sFCU.sASI.u8ScanIndex, C_FCU_ASI__FAULTS);
							break;

						case C_FCU_ASI__CONT_TEMP:
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32TempC = (Lfloat32)u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(sFCU.sASI.u8ScanIndex, C_FCU_ASI__CONT_TEMP);
							break;

						case C_FCU_ASI__MOTOR_CURRENT:
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32MotorCurrentA = (Lfloat32)u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(sFCU.sASI.u8ScanIndex, C_FCU_ASI__MOTOR_CURRENT);
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32MotorCurrentA /= 32.0F;
							break;

						case C_FCU_ASI__MOTOR_RPM:
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16RPM = u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(sFCU.sASI.u8ScanIndex, C_FCU_ASI__MOTOR_RPM);
							break;

						case C_FCU_ASI__THROT_VOLTAGE:
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32ThrottleV = u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(sFCU.sASI.u8ScanIndex, C_FCU_ASI__THROT_VOLTAGE);
							sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32ThrottleV /= 4096.0F;
							break;

						default:
							//do nothing
							break;

					}//switch(sFCU.sASI.eCommandList[sFCU.sASI.u8CommandListIndex])
				}
				else
				{
					//probably had a timeout

					//if we did, this is ok as it was detected by the modbus master, lets just flag us so as we know what that was
					sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16Faults = 0xFFFFU;

				}

				//move on
				sFCU.sASI.eMainState = ASI_STATE__INC_SCAN_INDEX;
			}
			else
			{
				//stay here, protect timeout

				//wait for
				if(sFCU.sASI.u32WaitCommandTimeout > C_ASI__MAX_COMMAND_TIMEOUT)
				{
					//200ms timeout
					sFCU.sASI.u32TimeoutCounts[sFCU.sASI.u8ScanIndex]++;

					//move on
					sFCU.sASI.u32WaitCommandTimeout = 0U;
					sFCU.sASI.eMainState = ASI_STATE__INC_SCAN_INDEX;

					//set the faults to all 1
					sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16Faults = 0xFFFFU;

				}
				else
				{
					//no timeout
				}

			}
			break;

		case ASI_STATE__INC_SCAN_INDEX:

			if(sFCU.sASI.u8ScanIndex < C_FCU__NUM_HOVER_ENGINES - 1)
			{
				//move to the next scan index
				sFCU.sASI.u8ScanIndex++;
			}
			else
			{
				//clear it
				sFCU.sASI.u8ScanIndex = 0U;

				//inc the command index
				sFCU.sASI.u8CommandListIndex++;
				if(sFCU.sASI.u8CommandListIndex >= C_FCU__ASI_COMMAND_LIST_MAX)
				{
					sFCU.sASI.u8CommandListIndex = 0U;
				}
				else
				{
					//fall on
				}

			}

			//clear the timer
			sFCU.sASI.u810MS_Timer = 0U;

			sFCU.sASI.eMainState = ASI_STATE__IDLE;
			break;

		case ASI_STATE__INHIBIT:
			//spin
			break;

		default:
			//issues
			break;
	}

}

/***************************************************************************//**
 * @brief
 * 10MS ISR point
 *
 */
void vFCU_ASI__10MS_ISR(void)
{

	//tell the modbus layer about our timer.
	vSIL3_MODBUS__10MS_Timer();

	sFCU.sASI.u810MS_Timer++;
	sFCU.sASI.u32WaitCommandTimeout++;
}

Luint16 u16FCU_ASI__ReadMotorRpm(Luint8 u8EngineIndex)
{
	return sFCU.sASI.sHolding[u8EngineIndex].u16RPM;
}

Luint16 u16FCU_ASI__ReadMotorVoltage(Luint8 u8EngineIndex)
{
//TODO: return sFCU.sASI.sHolding[u8EngineIndex].
return 0;
}

Lfloat32 f32FCU_ASI__ReadMotorCurrent(Luint8 u8EngineIndex)
{
	return sFCU.sASI.sHolding[u8EngineIndex].f32MotorCurrentA;
}

Lfloat32 f32FCU_ASI__ReadControllerTemperature(Luint8 u8EngineIndex)
{
	return sFCU.sASI.sHolding[u8EngineIndex].f32TempC;
}

//inhibit tx during programming
void vFCU_ASI__Inhibit(void)
{

	//set the mux
	vFCU_ASI_MUX__SelectChannel_DE(0, 0U);

	//force state
	sFCU.sASI.eMainState = ASI_STATE__INHIBIT;

}

//Set the throttle via the ASI controller.
void vFCU_ASI__Set_Throttle(Luint8 u8Index, Luint16 u16RPM)
{

	if(u8Index < C_FCU__NUM_HOVER_ENGINES)
	{
		//set the flag that we need to change the throttle
		sFCU.sASI.u8ThrottleCommand[u8Index] = 1U;

		//save the RPM
		sFCU.sASI.u16Throttle[u8Index] = u16RPM;
	}
	else
	{

	}

}


#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#ifndef C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
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

