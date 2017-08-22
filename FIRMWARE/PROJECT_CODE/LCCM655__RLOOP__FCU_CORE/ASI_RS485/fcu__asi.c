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
	sFCU.sASI.u8RxCount = 0U;


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



		sFCU.sASI.sHolding[u8Counter].u16Faults = 0U;
		sFCU.sASI.sHolding[u8Counter].f32TempC = 0.0F;
		sFCU.sASI.sHolding[u8Counter].f32MotorCurrentA = 0.0F;
		sFCU.sASI.sHolding[u8Counter].u16RPM = 0U;
		sFCU.sASI.u8ThrottleCommand[u8Counter] = 0U;
		sFCU.sASI.u8SerialNetworkCommand[u8Counter] = 1U;
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
			if(sFCU.sASI.u810MS_Timer > 10U)
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

			}
			else
			{
				//wait here
			}


/*
			//format the command
			if(sFCU.sASI.u8SerialNetworkCommand[sFCU.sASI.u8ScanIndex] == 1U)
			{

				//address devices by their index

				sFCU.sASI.sCurrentCommand.u8SlaveAddress = C_ASI__DEFAULT_SLAVE_ADDX;
				sFCU.sASI.sCurrentCommand.eFunctionCode = FUNCTION_CODE__WRITE_SINGLE_REG;
				sFCU.sASI.sCurrentCommand.eObjectType = C_FCU_ASI__THROT_SENSOR_SOURCE;
				//network voltage source
				sFCU.sASI.sCurrentCommand.u16ParamValue = 5;
				sFCU.sASI.sCurrentCommand.eDestVarType = E_UINT16;

				//clear now that we are done.
				sFCU.sASI.u8SerialNetworkCommand[sFCU.sASI.u8ScanIndex] = 0U;
			}
			else if(sFCU.sASI.u8ThrottleCommand[sFCU.sASI.u8ScanIndex] == 1U)
			{
				//updat the trhottle
				sFCU.sASI.sCurrentCommand.u8SlaveAddress = C_ASI__DEFAULT_SLAVE_ADDX;
				sFCU.sASI.sCurrentCommand.eFunctionCode = FUNCTION_CODE__WRITE_SINGLE_REG;
				sFCU.sASI.sCurrentCommand.eObjectType = C_FCU_ASI__REMOTE_THROTTLE_VOLTAGE;
				sFCU.sASI.sCurrentCommand.u16ParamValue = sFCU.sASI.u16Throttle[sFCU.sASI.u8CommandListIndex];
				sFCU.sASI.sCurrentCommand.eDestVarType = E_UINT16;

				sFCU.sASI.u8ThrottleCommand[sFCU.sASI.u8ScanIndex] = 0U;
			}
			else
			{
				//do a normal read
				sFCU.sASI.sCurrentCommand.u8SlaveAddress = C_ASI__DEFAULT_SLAVE_ADDX;
				sFCU.sASI.sCurrentCommand.eFunctionCode = FUNCTION_CODE__READ_HOLDING_REGS;
				sFCU.sASI.sCurrentCommand.eObjectType = sFCU.sASI.eCommandList[sFCU.sASI.u8CommandListIndex]; // C_FCU_ASI__FAULTS;
				sFCU.sASI.sCurrentCommand.u16ParamValue = 1;	// we just want to read one register
				sFCU.sASI.sCurrentCommand.eDestVarType = E_UINT16;
			}


			s16Return = s16FCU_ASI__SendCommand();
*/

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
				}

				//move on
				sFCU.sASI.eMainState = ASI_STATE__INC_SCAN_INDEX;
			}
			else
			{
				//stay here, protect timeout
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
	//sFCU.sASI.u32ASI_turnaround_Counter++;
	//sFCU.sASI.u32ASI_replywait_Counter++;
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

#if 0
/***************************************************************************//**
 * @brief
 * Send Read/Write register command to ASI controller
 *
 * @param[in]	pCmd		Command structure
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI__SendCommand(void)
{
	Lint16 s16Return;

	if(sFCU.sASI.u8NewCommandToSend == 1U)
	{
		// still processing another command, can't send message
		s16Return = -1;
	}
	else
	{
		// build the frame of bytes to send for this command
		vFCU_ASI__BuildCmdFrame(&sFCU.sASI.sCurrentCommand);

		sFCU.sASI.u8NewCommandToSend = 1;
		s16Return = 0;
	}
	
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Build Modbus read/write register command frame to issue to ASI controller
 *
  * @param[in]	pCmd		Command structure
 */
void vFCU_ASI__BuildCmdFrame(struct _strASICmd *pCmd)
{
	Luint16 u16Object;

	//type convert
	u16Object = (Luint16)pCmd->eObjectType;

	pCmd->framedCmd[0] = pCmd->u8SlaveAddress;
	pCmd->framedCmd[1] = (Luint8)pCmd->eFunctionCode;
	pCmd->framedCmd[2] = (Luint8)(u16Object >> 8);				// register address Hi
	pCmd->framedCmd[3] = (Luint8)(u16Object & 0x00FF);	 		// register address Lo
	pCmd->framedCmd[4] = (Luint8)(pCmd->u16ParamValue >> 8);  				// register value Hi
	pCmd->framedCmd[5] = (Luint8)(pCmd->u16ParamValue & 0x00FF);				// register value Lo

	//compute the CRC
	vFCU_ASI_CRC__AddCRC(pCmd->framedCmd);
}

/***************************************************************************//**
 * @brief
 * Process error from ASI device
 *
 * @param[in]	pCmd		Command being processed
 */
Lint16 s16FCU_ASI__ProcessError(struct _strASICmd *pCmd)
{
	Lint16 s16Return;

	if (pCmd)
	{
		// TODO: log error
		if(pCmd->eErrorType == E_ERROR_RESPONSE)
		{
			// TODO: add exception code: pTail->response[1] to error log

			s16Return = -1;
		}
		else
		{
			// set requesting variable to 0 to alert about error
			vFCU_ASI__SetErr(&sFCU.sASI.sCurrentCommand);

		}

		s16Return = 0;
	}
	else
	{
		s16Return = -2;
	}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Set variable with appropriate error from ASI device
 *
 * @param[in]	pCmd		Command being processed
 */
void vFCU_ASI__SetErr(struct _strASICmd *pCmd)
{
	if (pCmd && pCmd->destVar)
	{
		switch(pCmd->eDestVarType)
		{
			case E_INT8:
				*((Lint8*)pCmd->destVar) = 0;
				break;
			case E_UINT8:
				*((Luint8*)pCmd->destVar) = 0;
				break;
			case E_INT16:
				*((Lint16*)pCmd->destVar) = 0;
				break;
			case E_UINT16:
				*((Luint16*)pCmd->destVar) = 0;
				break;
		}
	}
}

void vFCU_ASI__MemSet(Luint8 *pu8Buffer, Luint8 u8Value, Luint32 u32Count)
{
	Luint32 u32Counter;
	for(u32Counter = 0; u32Counter < u32Count; u32Counter++)
	{
		pu8Buffer[u32Counter] = u8Value;
	}

}

 
void vFCU_ASI__MemCopy(Luint8 *pu8Dest, const Luint8 *cpu8Source, Luint32 u32Length)
{
	Luint32 u32Counter;
	for(u32Counter = 0; u32Counter < u32Length; u32Counter++)
	{
		pu8Dest[u32Counter] = cpu8Source[u32Counter];	
	} 

}


/***************************************************************************//**
 * @brief
 * Process reply from ASI device
 *
 * @param[in]	pCmd		Command being processed in command queue
 * @return			-1 = crc error
 * 					0 = success
 */
Lint16 s16FCU_ASI__ProcessReply(void)
{
	Lint16 s16Return;

	// check CRC
	s16Return = s16FCU_ASI_CRC__CheckCRC(&sFCU.sASI.sCurrentCommand.u8Response[0], 7U- 2U);
	if(s16Return < 0)
	{
		sFCU.sASI.sCurrentCommand.eErrorType = E_CRC_CHECK_FAILED;
		s16Return = -1;
	}
	else
	{
		// check return slave address vs sent slave address, they should match
		if(sFCU.sASI.sCurrentCommand.framedCmd[0] != sFCU.sASI.sCurrentCommand.u8Response[0])
		{
			sFCU.sASI.sCurrentCommand.eErrorType = E_SLAVE_MISMATCH;
			s16Return = -2;
		}
		else
		{
			// check function code in response, if it's error reply, process error
			if((sFCU.sASI.sCurrentCommand.u8Response[1] & 0x80U) == 0x80U)
			{
				sFCU.sASI.sCurrentCommand.eErrorType = E_ERROR_RESPONSE;
				s16Return = -3;
			}
			else
			{
				//get the variable
				switch(sFCU.sASI.sCurrentCommand.eDestVarType)
				{
					case E_INT8:
						sFCU.sASI.sCurrentCommand.unDestVar.s8[0] = (Lint8)(sFCU.sASI.sCurrentCommand.u8Response[4]);
						break;

					case E_UINT8:
						sFCU.sASI.sCurrentCommand.unDestVar.u8[0] = (Luint8)(sFCU.sASI.sCurrentCommand.u8Response[4]);
						break;

					case E_INT16:
						sFCU.sASI.sCurrentCommand.unDestVar.s16[0] = (Lint16)(((Luint16)sFCU.sASI.sCurrentCommand.u8Response[3] << 8) | (Luint16)sFCU.sASI.sCurrentCommand.u8Response[4]);
						break;

					case E_UINT16:
						sFCU.sASI.sCurrentCommand.unDestVar.u16[0] = ((Luint16)sFCU.sASI.sCurrentCommand.u8Response[3] << 8) | (Luint16)sFCU.sASI.sCurrentCommand.u8Response[4];

						switch(sFCU.sASI.sCurrentCommand.eObjectType)
						{
							case C_FCU_ASI__FAULTS:
								sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16Faults = sFCU.sASI.sCurrentCommand.unDestVar.u16[0];
								break;
							case C_FCU_ASI__CONT_TEMP:
								sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32TempC = (Lfloat32)sFCU.sASI.sCurrentCommand.unDestVar.u16[0];
								break;
							case C_FCU_ASI__TEMPERATURE:
								break;
							case C_FCU_ASI__MOTOR_CURRENT:
								sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].f32MotorCurrentA = (Lfloat32)sFCU.sASI.sCurrentCommand.unDestVar.u16[0];
								break;
							case C_FCU_ASI__MOTOR_RPM:
								sFCU.sASI.sHolding[sFCU.sASI.u8ScanIndex].u16RPM = sFCU.sASI.sCurrentCommand.unDestVar.u16[0];
								break;
							default:
								break;

						}//switch(sFCU.sASI.sCurrentCommand.eObjectType)

					break;

					default:
						//fall on.
						break;
				}//switch(sFCU.sASI.sCurrentCommand.eDestVarType)
			}

		}

	}

	return s16Return;
}
#endif



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

