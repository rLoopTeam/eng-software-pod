/**
 * @file		FCU__ASI_RS485.C
 * @brief		Modbus/RS485 interface to ASI controller
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

	// TODO: lower level SC16 and MCP23 init
	// TODO: set baud rate
	// 3.5CharTimer and 1.5CharTimer depend on baud rate (see pg 13 of Modbus over serial line spec)
	// assume we will set baud rate > 19200 Bps
	// TODO: get information on micro second timer counter
	// TODO: implement 1.5CharTimer to detect incomplete frames
	// assuming we have a global micro second counter that we can get with getCurMicroSecTimer()
	// assuming we have vSC16_USER__Tx_Byte(), vSC16_USER__RxIsReady() and vSC16_USER__Rx_Byte()
	sFCU.sASIComms.timeout_3_5_char = 1750; // in microsec
	sFCU.sASIComms.timeout_1_5_char = 750; // in microsec
	sFCU.sASIComms.timeout_response = 3000;  // this is application specific; TODO: check this value

	// ensure first frame starts with silence interval
	sFCU.sASIComms.timer_3_5_char_start =  getCurMicroSecTimer();

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
	Luint8 byteIndex;
	Luint8 bSent=0;
	Luint8 bProcessedReply=0;

	// modbus over serial line state machine
	switch(sFCU.sASIComms.eMbState)
	{
		case ASI_COMM_STATE__INITIAL:
			// wait for 3.5 char worth of silence time
			if ((getCurMicroSecTimer() - sFCU.sASIComms.timer_3_5_char_start) > sFCU.sASIComms.timeout_3_5_char)
			{
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			break;

		case ASI_COMM_STATE__IDLE:
			// see if we have a command to transmit in the queue
			if (sFCU.sASIComms.qHead != sFCU.sASIComms.qTail)
			{
				if (sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].slaveAddress == 0)
				{
					// we have a broadcast command
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__BROADCAST_EMISSION;
				}
				else
				{
					// we have a unicast command
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__UNICAST_EMISSION;
				}
			}
			break;

		case ASI_COMM_STATE__BROADCAST_EMISSION:
			if (bSent && (getCurMicroSecTimer() - sFCU.sASIComms.timer_turnaround_start) > sFCU.sASIComms.timeout_turnaround)
			{
				bSent=0;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			else if (!bSent)
			{
				// start transmitting
				Luint8* pByte = sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].framedCmd;
				for (byteIndex=0; byteIndex < C_ASI__RW_FRAME_SIZE; byteIndex++)
				{
					vFCU_ASI__RTU_Tx_Byte(pByte++);
				}
				bSent=1;
				// done sending all bytes, start turn around timer
				sFCU.sASIComms.timer_turnaround_start  = getCurMicroSecTimer();
			}
			else
			{
				// stay in this state until turnaround delay passes
			}

			break;

		case ASI_COMM_STATE__UNICAST_EMISSION:
			if (bSent && (getCurMicroSecTimer() - sFCU.sASIComms.timer_3_5_char_start) > sFCU.sASIComms.timeout_3_5_char)
			{
				bSent=0;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__RECEPTION;
			}
			else if (!bSent)
			{
				// start transmitting
				Luint8* pByte = sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].framedCmd;
				for (byteIndex=0; byteIndex < C_ASI__RW_FRAME_SIZE; byteIndex++)
				{
					vFCU_ASI__RTU_Tx_Byte(pByte++);
				}
				bSent=1;
				// done sending all bytes, start 3.5 char worth silence interval and response timer
				sFCU.sASIComms.timer_3_5_char_start =  sFCU.sASIComms.timer_response_start  = getCurMicroSecTimer();
			}
			else
			{
				// stay in this state until silence interval passes
			}

			break;

		case ASI_COMM_STATE__RECEPTION:
			if ((getCurMicroSecTimer() - sFCU.sASIComms.timer_response_start) > sFCU.sASIComms.timeout_response)
			{
				// timed out waiting for response, message is left in queue, try sending again
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			else if (vFCU_ASI__RTU_RxIsReady())
			{
				// start receiveing
				Luint8* pByte = sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail].response;
				for (byteIndex=0; byteIndex < C_ASI__RW_FRAME_SIZE; byteIndex++)
				{
					vFCU_ASI__RTU_Rx_Byte(pByte++);
				}
				// done getting all bytes, start 3.5 silence interval
				sFCU.sASIComms.timer_3_5_char_start =  getCurMicroSecTimer();
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__CONTROL_AND_WAIT;
			}
			break;

		case ASI_COMM_STATE__CONTROL_AND_WAIT:
			if (bProcessedReply && (getCurMicroSecTimer() - sFCU.sASIComms.timer_3_5_char_start) > sFCU.sASIComms.timeout_3_5_char)
			{
				bProcessedReply=0;
				sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
			}
			else if (!bProcessedReply)
			{
				if (vFCU_ASI__ProcessReply())
				{
					// there was an error
					sFCU.sASIComms.eMbState = ASI_COMM_STATE__IDLE;
				}
				else
				{
					bProcessedReply=1;
				}
			}
			else
			{
				// stay in this state until silence interval passes
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
		sCmdParams->framedCmd[0]=sCmdParams->slaveAddress;
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
		for (byteIndex = 0; byteIndex < dataLen - 2; byteIndex++) {
			tempLSB = 0x00FF & crc;

			crc = tempLSB ^ data[byteIndex];

			for (bitIndex= 0; bitIndex < 8; bitIndex++) {
				tempCRC = crc;
				flag = tempCRC & 0x0001;
				crc = crc >> 1;

				if (flag)
					crc = crc ^ 0xA001;
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
 * @param[in]	sCmdParams		Command structure with read params
 * @return			-1 = crc error
 * 					0 = success
 */
Lint8 vFCU_ASI__ProcessReply(void)
{
	struct _strASICmd *pTail = &sFCU.sASIComms.cmdQueue[sFCU.sASIComms.qTail];

	if (vFCU_ASI__CheckCRC(pTail->response, C_ASI__RW_FRAME_SIZE)) {
		return -1;
	}
	// check function code in response, if it's error reply, process error
	if (pTail->response[2] & 0x80)
	{
		vFCU_ASI__ProcessError(pTail);
	}
	else
	{
		vFCU_ASI__SetVar(pTail);
	}
	// TODO: check return slave address vs sent slave address, they should match

	//adjust tail pointer
	//pop the command out of the queue because it's done being processed
	sFCU.sASIComms.qTail++;
	if (sFCU.sASIComms.qTail == C_ASI__RW_FRAME_SIZE)
		sFCU.sASIComms.qTail=0;	// rollover

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
		// TODO: log exception code: pTail->response[2];
	}
}


/***************************************************************************//**
 * @brief
 * Build RTU packet for each byte and transmit using lower level driver
 *
 * @param[in]	pByte		Byte to transmit
 */
void vFCU_ASI__RTU_Tx_Byte(Luint8* pByte)
{
	// TODO
	// need to format byte as in p12 of Modbus over serial line documentation
	// 11 bits per byte: add parity checking bit, start bit and stop bit
	// start, 1, 2, 3, 4, 5, 6, 7, 8, parity, stop
	// then call lower level driver function to transmit each bit
	//
}

/***************************************************************************//**
 * @brief
 * Receive RTU packet using lower level drive extract data byte
 *
 * @param[in]	pByte		Byte to receive
 */
void vFCU_ASI__RTU_Rx_Byte(Luint8* pByte)
{
	// TODO
	// call lower level driver function to receive rtu packet
	// need to extract byte as in p12 of Modbus over serial line documentation
	// 11 bits in packet: remove parity checking bit, start bit and stop bit
	// start, 1, 2, 3, 4, 5, 6, 7, 8, parity, stop

}

/***************************************************************************//**
 * @brief
 * Check and see if we have a rtu packet to receive from a slave
 *
 * @return			1 = yes
 * 					0 = no
 */
Luint8 vFCU_ASI__RTU_RxIsReady(void)
{
	Luint8 isReady=0;

	// TODO
	// call lower level driver function to figure this out

	return isReady;
}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

