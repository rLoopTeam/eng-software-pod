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

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_ASI__Init(void)
{
	memset(sFCU.sASIComms, 0, sizeof(sFCU.sASIComms));

	// TODO: set baud rate

	sFCU.sASIComms.u32ASI_turnaround_Counter = 0;
	sFCU.sASIComms.u32ASI_replywait_Counter = 0;


	// initialize all slaves
	vFCU_ASI__Controller_Init();
}


/***************************************************************************//**
 * @brief
 * Process any ASI tasks
 * 
 */
void vFCU_ASI__Process(void)
{
	Luint8 u8Temp;

	// modbus over serial line state machine
	switch(sFCU.sASIComms.eMbState)
	{
		case ASI_COMM_STATE__IDLE:
			// see if we have a command to transmit in the queue
			if (sFCU.sASIComms.qHead != sFCU.sASIComms.qTail)
			{
				// transmit
				Luint8* pByte = sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].framedCmd;
				vSC16__Tx_ByteArray(0, pByte, C_ASI__RW_FRAME_SIZE);

				if (sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].u8SlaveAddress == 0)
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
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			break;

		case ASI_COMM_STATE__WAIT_REPLY:
			// see if we have a reply
			u8Temp = u8SC16_USER__Get_ByteAvail(0);	//TODO: verify device number
			if(u8Temp == 0U)
			{
				// no response yet
				// check to see if reply wait timer expired
				if (sFCU.sASIComms.u32ASI_replywait_Counter > C_ASI_MAX_WAITREPLY_DELAY)
				{
					sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].eErrorType = E_REPLY_TIMEOUT_EXPIRED;
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_ERROR;
				}
			}
			else
			{
				// receive the response
				Luint8* pByte = sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].response;
				for (byteIndex=0; byteIndex < C_ASI__RW_FRAME_SIZE; byteIndex++)
				{
					*pByte++ = u8SC16_USER__Get_Byte(0); //TODO: verify device number, plus initialize device?
				}
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_REPLY;
			}
			break;

		case ASI_COMM_STATE__PROCESS_REPLY:
			if (vFCU_ASI__ProcessReply(sFCU.sASIComms.qTail))
			{
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__PROCESS_ERROR;

			}
			else
			{
				// done processing this command, ready for next command
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;

			}
			break;

		case ASI_COMM_STATE__PROCESS_ERROR:
			if (!sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].retry)
			{
				// set retry and go to idle to process this again
				sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].retry = 1;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE
			}
			else
			{
				vFCU_ASI__ProcessError(sFCU.sASIComms.qTail);
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			break;
	}

}

/***************************************************************************//**
 * @brief
 * Send Read/Write register command to ASI controller
 *
 * @param[in]	sCmdParams		Command structure
 * @return			-1 = error
 * 					0 = success
 */
Lint8 vFCU_ASI__SendCommand(struct _strASICmd *sCmdParams)
{
	if (sCmdParams)
	{
		struct _strASICmd *pHead = &sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qHead];

		if ((sFCU.sASIComms.qHead + 1) == sFCU.sASIComms.qTail)
		{
			// queue is backed up, can't send message
			return -1;
		}

		// clear contents of this command queue slot
		memset(sFCU.sASIComms.qHead, 0, sizeof(_strASICmd));

		// build the frame of bytes to send for this command
		vFCU_ASI__BuildCmdFrame(sCmdParams);

		// add command to next available slot in command queue
		memcpy(pHead,sCmdParams,sizeof(struct _strASICmd));

		// adjust head pointer
		sFCU.sASIComms.qHead++;
		if (sFCU.sASIComms.qHead == C_ASI__RW_FRAME_SIZE)
			sFCU.sASIComms.qHead=0;	// rollover
	}
	return 0;
}


/***************************************************************************//**
 * @brief
 * Build Modbus read/write register command frame to issue to ASI controller
 *
  * @param[in]	sCmdParams		Command structure
 */
void vFCU_ASI__BuildCmdFrame(struct _strASICmd *sCmdParams)
{
	if (sCmdParams)
	{
		sCmdParams->framedCmd[0]=sCmdParams->u8SlaveAddress;
		sCmdParams->framedCmd[1]=sCmdParams->fncCode;
		sCmdParams->framedCmd[2]=(Luint8)(sCmdParams->paramAddress >> 8);				// register address Hi
		sCmdParams->framedCmd[3]=(Luint8)(sCmdParams->paramAddress & 0x00FF);	 		// register address Lo
		sCmdParams->framedCmd[4]=(Luint8)(sCmdParams->paramValue >> 8);  				// register value Hi
		sCmdParams->framedCmd[5]=(Luint8)(sCmdParams->paramValue & 0x00FF);				// register value Lo
		vFCU_ASI__AddCRC(sCmdParams->framedCmd);
	}
}

/***************************************************************************//**
 * @brief
 * Compute frame CRC
 *
 * @param[in]	data		framedParameter
 * @return		crc
 *
 */
Luint16 vFCU_ASI__ComputeCRC(Luint8* data, Luint16 dataLen)
{
	Luint16 crc = 0xffff;
	Luint16 tempCRC;
	Luint8 tempLSB, flag;
	Lint8 byteIndex, bitIndex;

	if (data)
	{
		for (byteIndex = 0; byteIndex < dataLen - 2; byteIndex++)
		{
			tempLSB = 0x00FF & crc;

			crc = tempLSB ^ data[byteIndex];

			for (bitIndex= 0; bitIndex < 8; bitIndex++)
			{
				tempCRC = crc;
				flag = tempCRC & 0x0001;
				crc = crc >> 1;

				if (flag)
				{
					crc = crc ^ 0xA001;
				}
			}
		}
	}
	return crc;
}

/***************************************************************************//**
 * @brief
 * Add CRC to modbus command frame
 *
  * @param[in]	data		framedParameter
 */
void vFCU_ASI__AddCRC(Luint8* data)
{
	if (data)
	{
		Luint16 crc = vFCU_ASI__ComputeCRC(data, C_ASI__RW_FRAME_SIZE);
		data[6]=(Luint8)(crc & 0x00ff);	// lower crc byte
		data[7]=(Luint8)(crc >> 8);		// higher crc byte
	}
}

/***************************************************************************//**
 * @brief
 * Process reply from ASI device
 *
 * @param[in]	pTail		Command being processed in command queue
 * @return			-1 = crc error
 * 					0 = success
 */
Lint8 vFCU_ASI__ProcessReply(struct _strASICmd *pTail)
{
	if (pTail)
	{
		// check CRC
		if (vFCU_ASI__CheckCRC(pTail->response, C_ASI__RW_FRAME_SIZE))
		{
			pTail->eErrorType = E_CRC_CHECK_FAILED;
			return -1;
		}
		// check return slave address vs sent slave address, they should match
		if (pTail->framedCmd[0] != pTail->response[0])
		{
			pTail->eErrorType = E_SLAVE_MISMATCH;
			return -1;
		}
		// check function code in response, if it's error reply, process error
		if (pTail->response[2] & 0x80)
		{
			pTail->eErrorType = E_ERROR_RESPONSE;
			return -1;
		}

		vFCU_ASI__SetVar(pTail);

		//adjust tail pointer
		//pop the command out of the queue because it's done being processed
		sFCU.sASIComms.qTail++;
		if (sFCU.sASIComms.qTail == C_ASI__RW_FRAME_SIZE)
			sFCU.sASIComms.qTail=0;	// rollover

	}

	return 0;
}

/***************************************************************************//**
 * @brief
 * Check CRC from ASI device response
 *
 * @param[in]	rData		Response Data
 * @return			-1 = error
 * 					0 = success
 */
Lint8 vFCU_ASI__CheckCRC(Luint8* rData, Luint8 dataLen)
{
	unsigned int crc;

	if (rData)
	{
		crc = vFCU_ASI__ComputeCRC(rData, dataLen);

		if ( ( (rData[dataLen + 1]) != (crc >> 8) ) || ( (rData[dataLen]) != (crc & 0x00FF) ) ) {
			return -1;
		}
	}
	else
		return -1;

	return 0;
}


/***************************************************************************//**
 * @brief
 * Set variable with response from ASI device
 *
 * @param[in]	pTail		Command being processed in command queue
 */
void vFCU_ASI__SetVar(struct _strASICmd *pTail)
{
	if (pTail && pTail->destVar)
	{
		switch(pTail->eDestVarType)
		{
			case E_INT8:
				*((Lint8*)pTail->destVar) = (Lint8)(pTail->response[4]);
				break;
			case E_UINT8:
				*((Luint8*)pTail->destVar) = (Luint8)(pTail->response[4]);
				break;
			case E_INT16:
				*((Lint16*)pTail->destVar) = (Lint16)(((Luint16)pTail->response[3] << 8) | pTail->response[4]);
				break;
			case E_UINT16:
				*((Luint16*)pTail->destVar) = ((Luint16)pTail->response[3] << 8) | pTail->response[4];
				break;
		}
	}
}


/***************************************************************************//**
 * @brief
 * Process error from ASI device
 *
 * @param[in]	pTail		Command being processed in command queue
 */
void vFCU_ASI__ProcessError(struct _strASICmd *pTail)
{
	if (pTail)
	{
		// TODO: log error
		if (pTail->eErrorType == E_ERROR_RESPONSE)
		{
			// TODO: add exception code: pTail->response[2] to error log
		}
		// set requesting variable to 0 to alert about error
		vFCU_ASI__SetErr(sFCU.sASIComms.qTail);

		//adjust tail pointer
		//pop the command out of the queue because it's done being processed
		sFCU.sASIComms.qTail++;
		if (sFCU.sASIComms.qTail == C_ASI__RW_FRAME_SIZE)
			sFCU.sASIComms.qTail=0;	// rollover
	}

}

/***************************************************************************//**
 * @brief
 * Set variable with appropriate error from ASI device
 *
 * @param[in]	pTail		Command being processed in command queue
 */
void vFCU_ASI__SetErr(struct _strASICmd *pTail)
{
	if (pTail && pTail->destVar)
	{
		switch(pTail->eDestVarType)
		{
			case E_INT8:
				*((Lint8*)pTail->destVar) = 0;
				break;
			case E_UINT8:
				*((Luint8*)pTail->destVar) = 0;
				break;
			case E_INT16:
				*((Lint16*)pTail->destVar) = 0;
				break;
			case E_UINT16:
				*((Luint16*)pTail->destVar) = 0;
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

