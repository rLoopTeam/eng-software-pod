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


/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_ASI__Init(void)
{
	Lint16 s16Return;

	vFAULTTREE__Init(&sFCU.sASIComms.sFaultFlags);

	//configure the multiplexer
	vFCU_ASI_MUX__Init();

	//eth layer
	vFCU_ASI_ETH__Init();

	//todo: check we need this.
	vFCU_ASI__MemSet((Luint8 *)&sFCU.sASIComms, 0, (Luint32)sizeof(sFCU.sASIComms));

	//Note:
	//SC16's are already configured here with correct baud rate./

	sFCU.sASIComms.u32ASI_turnaround_Counter = 0;
	sFCU.sASIComms.u32ASI_replywait_Counter = 0;


	// initialize all slaves
	s16Return = s16FCU_ASI_CTRL__Init();
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

	//handle the mux
	vFCU_ASI_MUX__Process();

	// modbus over serial line state machine
	switch(sFCU.sASIComms.eMbState)
	{
		case ASI_COMM_STATE__IDLE:

			// see if we have a command to transmit in the queue
			if(sFCU.sASIComms.cmdToProcess)
			{
				// transmit
				vSC16__Tx_ByteArray(C_FCU__SC16_ASI_INDEX, (Luint8*)&sFCU.sASIComms.cmd.framedCmd, C_ASI__RW_FRAME_SIZE);


				if (sFCU.sASIComms.cmd.u8SlaveAddress == 0)
				{
					// we have a broadcast command, start turn around timer
					sFCU.sASIComms.u32ASI_turnaround_Counter  = 0;
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__WAIT_TURNAROUND_DELAY;
				}
				else
				{
					// we have a unicast command, start reply wait timer
					sFCU.sASIComms.u32ASI_replywait_Counter = 0;
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__WAIT_REPLY;
				}
			}
			break;

		case ASI_COMM_STATE__WAIT_TURNAROUND_DELAY:
			// sent broadcast, wait for slaves to process
			if (sFCU.sASIComms.u32ASI_turnaround_Counter > C_ASI__MAX_TURNAROUND_DELAY)
			{
				sFCU.sASIComms.cmdToProcess = 0;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			else
			{

			}
			break;

		case ASI_COMM_STATE__WAIT_REPLY:
			// see if we have a reply
#ifdef C_ASI__SW_TEST
			// simulate a fake response
			u8Temp = 1U;
#else
			u8Temp = u8SC16_USER__Get_ByteAvail(C_FCU__SC16_ASI_INDEX);
#endif
			if(u8Temp == 0U)
			{
				// no response yet
				// check to see if reply wait timer expired
				if (sFCU.sASIComms.u32ASI_replywait_Counter > C_ASI__MAX_REPLYWAIT_DELAY)
				{
					sFCU.sASIComms.cmd.eErrorType = E_REPLY_TIMEOUT_EXPIRED;
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_ERROR;
				}
				else
				{

				}
			}
			else
			{
				// receive the response
				Luint8* pByte = sFCU.sASIComms.cmd.response;
#ifdef C_ASI__SW_TEST
				// simulate a fake response
				*pByte++ = sFCU.sASIComms.cmd.framedCmd[0];
				*pByte++ = sFCU.sASIComms.cmd.framedCmd[1];
				*pByte++ = 2;
				*Luint16 val = 1750;
				*pByte++ = val & 0xff00;
				*pByte = val & 0x00ff;
				vFCU_ASI_CRC__AddCRC(sFCU.sASIComms.cmd.response);
#else
				for (u8ByteIndex=0; u8ByteIndex < C_ASI__RW_FRAME_SIZE; u8ByteIndex++)
				{
					*pByte++ = u8SC16_USER__Get_Byte(C_FCU__SC16_ASI_INDEX);
				}

#endif

				sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_REPLY;
			}
			break;

		case ASI_COMM_STATE__PROCESS_REPLY:
			s16Return = s16FCU_ASI_CTRL__ProcessReply(&sFCU.sASIComms.cmd);
			if(s16Return < 0)
			{
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_ERROR;

			}
			else
			{
				// done processing this command, ready for next command
				sFCU.sASIComms.cmdToProcess = 0;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;

			}
			break;

		case ASI_COMM_STATE__PROCESS_ERROR:
			s16FCU_ASI__ProcessError(&sFCU.sASIComms.cmd);
			sFCU.sASIComms.cmdToProcess = 0;
			sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			break;
	}

}

/***************************************************************************//**
 * @brief
 * Send Read/Write register command to ASI controller
 *
 * @param[in]	pCmd		Command structure
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI__SendCommand(struct _strASICmd *pCmd)
{
	Lint16 s16Return;

	if(pCmd != 0x00000000U)
	{
		if (sFCU.sASIComms.cmdToProcess)
		{
			// still processing another command, can't send message
			s16Return = -1;
		}
		else
		{
			// clear contents of cmd
			vFCU_ASI__MemSet((Luint8 *)&sFCU.sASIComms.cmd, 0U, (Luint32)sizeof(struct _strASICmd));

			// build the frame of bytes to send for this command
			vFCU_ASI__BuildCmdFrame(pCmd);

			// add command to next available slot in command queue
			vFCU_ASI__MemCopy((Luint8*)&sFCU.sASIComms.cmd, (Luint8*)&pCmd, (Luint32)sizeof(struct _strASICmd));

			sFCU.sASIComms.cmdToProcess = 1;
			s16Return = 0;
		}

	}
	else
	{
		s16Return = -2;
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
	if (pCmd)
	{
		pCmd->framedCmd[0]=pCmd->u8SlaveAddress;
		pCmd->framedCmd[1]=pCmd->u8FunctionCode;
		pCmd->framedCmd[2]=(Luint8)(pCmd->u16ParamAddx >> 8);				// register address Hi
		pCmd->framedCmd[3]=(Luint8)(pCmd->u16ParamAddx & 0x00FF);	 		// register address Lo
		pCmd->framedCmd[4]=(Luint8)(pCmd->u16ParamValue >> 8);  				// register value Hi
		pCmd->framedCmd[5]=(Luint8)(pCmd->u16ParamValue & 0x00FF);				// register value Lo
		vFCU_ASI_CRC__AddCRC(pCmd->framedCmd);
	}
}






/***************************************************************************//**
 * @brief
 * Set variable with response from ASI device
 *
 * @param[in]	pCmd		Command being processed
 */
void vFCU_ASI__SetVar(struct _strASICmd *pCmd)
{
	if (pCmd && pCmd->destVar)
	{
		switch(pCmd->eDestVarType)
		{
			case E_INT8:
				*((Lint8*)pCmd->destVar) = (Lint8)(pCmd->response[4]);
				break;
			case E_UINT8:
				*((Luint8*)pCmd->destVar) = (Luint8)(pCmd->response[4]);
				break;
			case E_INT16:
				*((Lint16*)pCmd->destVar) = (Lint16)(((Luint16)pCmd->response[3] << 8) | pCmd->response[4]);
				break;
			case E_UINT16:
				*((Luint16*)pCmd->destVar) = ((Luint16)pCmd->response[3] << 8) | pCmd->response[4];
				break;
			default:
				//fall on.
				break;
		}
	}
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
			vFCU_ASI__SetErr(&sFCU.sASIComms.cmd);

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


/***************************************************************************//**
 * @brief
 * 10MS ISR point
 *
 */
void vFCU_ASI__10MS_ISR(void)
{
	sFCU.sASIComms.u32ASI_turnaround_Counter++;
	sFCU.sASIComms.u32ASI_replywait_Counter++;
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

