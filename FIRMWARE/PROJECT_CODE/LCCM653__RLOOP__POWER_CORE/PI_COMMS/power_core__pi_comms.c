/**
 * @file		POWER_CORE__PI_COMMS.C
 * @brief		Power Core to PiComms interface layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__PI_COMMS
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U

//The PICOMMS RX Callbacks
void vPWRNODE_PICOMMS__recvLuint8(Luint16 index, Luint8 data);
void vPWRNODE_PICOMMS__recvLint8(Luint16 index, Lint8 data);
void vPWRNODE_PICOMMS__recvLuint16(Luint16 index, Luint16 data);
void vPWRNODE_PICOMMS__recvLint16(Luint16 index, Lint16 data);
void vPWRNODE_PICOMMS__recvLuint32(Luint16 index, Luint32 data);
void vPWRNODE_PICOMMS__recvLint32(Luint16 index, Lint32 data);
void vPWRNODE_PICOMMS__recvLuint64(Luint16 index, Luint64 data);
void vPWRNODE_PICOMMS__recvLint64(Luint16 index, Lint64 data);
void vPWRNODE_PICOMMS__recvLfloat32(Luint16 index, Lfloat32 data);
void vPWRNODE_PICOMMS__recvLfloat64(Luint16 index, Lfloat64 data);

//the structure
extern struct _strPWRNODE sPWRNODE;

//the main structure
extern struct _strPICOMMS sPC;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vPWRNODE_PICOMMS__Init(void)
{

	//default or variables
	sPWRNODE.sPiComms.eState = PICOM_STATE__IDLE;

	//init pi comms
	vPICOMMS__Init();

	//Attach all the callbacks
	PICOMMS_RX_recvLuint8 = &vPWRNODE_PICOMMS__recvLuint8;
	PICOMMS_RX_recvLint8 = &vPWRNODE_PICOMMS__recvLint8;
	PICOMMS_RX_recvLuint16 = &vPWRNODE_PICOMMS__recvLuint16;
	PICOMMS_RX_recvLint16 = &vPWRNODE_PICOMMS__recvLint16;
	PICOMMS_RX_recvLuint32 = &vPWRNODE_PICOMMS__recvLuint32;
	PICOMMS_RX_recvLint32 = &vPWRNODE_PICOMMS__recvLint32;
	PICOMMS_RX_recvLuint64 = &vPWRNODE_PICOMMS__recvLuint64;
	PICOMMS_RX_recvLint64 = &vPWRNODE_PICOMMS__recvLint64;
	PICOMMS_RX_recvLfloat32 = &vPWRNODE_PICOMMS__recvLfloat32;
	PICOMMS_RX_recvLfloat64 = &vPWRNODE_PICOMMS__recvLfloat64;

	//switch on notifications now we are ready
	#if C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS == 1U
		vRM4_SCI_INT__Enable_Notification(SCI_CHANNEL__2, SCI_RX_INT);
	#endif
}


/***************************************************************************//**
 * @brief
 * Process any PiComms tasks
 * 
 */
void vPWRNODE_PICOMMS__Process(void)
{
	Luint32 u32Length;
	Luint8 * pu8Buffer;
	Luint8 u8Test;

	//process our state machine
	switch(sPWRNODE.sPiComms.eState)
	{

		case PICOM_STATE__IDLE:

			//todo, just for now.
			sPWRNODE.sPiComms.eState = PICOM_STATE__SETUP_FRAME;
			break;

		case PICOM_STATE__SETUP_FRAME:
			//start a new frame
			PICOMMS_TX_beginFrame();

			//change states
			sPWRNODE.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;
			break;

		case PICOM_STATE__ASSEMBLE_BUFFER:

			//add 0xAA as param 1
			PICOMMS_TX_addParameter_uint8(0x0001U, 0xAA);

			PICOMMS_TX_addParameter_uint8(10000U, sPC.sLp.PICOMMS_LOOP_UINT8);
			PICOMMS_TX_addParameter_uint8(10001U, sPC.sLp.PICOMMS_LOOP_INT8);
			PICOMMS_TX_addParameter_uint8(10002U, sPC.sLp.PICOMMS_LOOP_UINT16);
			PICOMMS_TX_addParameter_uint8(10003U, sPC.sLp.PICOMMS_LOOP_INT16);
			PICOMMS_TX_addParameter_uint8(10004U, sPC.sLp.PICOMMS_LOOP_UINT32);
			PICOMMS_TX_addParameter_uint8(10005U, sPC.sLp.PICOMMS_LOOP_INT32);
			PICOMMS_TX_addParameter_uint8(10006U, sPC.sLp.PICOMMS_LOOP_UINT64);
			PICOMMS_TX_addParameter_uint8(10007U, sPC.sLp.PICOMMS_LOOP_INT64);
			PICOMMS_TX_addParameter_uint8(10008U, sPC.sLp.PICOMMS_LOOP_FLOAT32);
			PICOMMS_TX_addParameter_uint8(10009U, sPC.sLp.PICOMMS_LOOP_FLOAT64);

			//add as many more params as you need depending on current tx state.

			sPWRNODE.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;

			break;

		case PICOM_STATE__START_DMA:
			//end the frame
			u32Length = (Luint32)PICOMMS_TX_endFrame();

			//get the buffer pointer
			pu8Buffer = pu8I2CTx__Get_BufferPointer();

			//todo, probably should check transaction is not running

			//start the transaction.
			#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
				vRM4_SCI_DMA__Begin_Tx(SCI_CHANNEL__2, pu8Buffer, u32Length);
			#endif

			//change state
			sPWRNODE.sPiComms.eState = PICOM_STATE__WAIT_DMA;
			break;

		case PICOM_STATE__WAIT_DMA:

			//test if the DMA is running
			#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
				u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
			#else
				u8Test = 0U;
			#endif
			if(u8Test == 0U)
			{
				//todo, for now go back to start.
				sPWRNODE.sPiComms.eState = PICOM_STATE__IDLE;
			}
			else
			{
				//stay in state
			}

			break;

	}

}

/***************************************************************************//**
 * @brief
 * Process all the UINT8 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLuint8(Luint16 index, Luint8 data)
{
	switch(index)
	{
		case  10000: sPC.sLp.PICOMMS_LOOP_UINT8 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT8 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLint8(Luint16 index, Lint8 data)
{
	switch(index)
	{
		case  10001: sPC.sLp.PICOMMS_LOOP_INT8 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the UINT16 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLuint16(Luint16 index, Luint16 data)
{
	switch(index)
	{
		case  10002: sPC.sLp.PICOMMS_LOOP_UINT16 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT16 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLint16(Luint16 index, Lint16 data)
{
	switch(index)
	{
		case  10003: sPC.sLp.PICOMMS_LOOP_INT16 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the UINT32 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLuint32(Luint16 index, Luint32 data)
{
	switch(index)
	{
		case  10004: sPC.sLp.PICOMMS_LOOP_UINT32 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT32 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLint32(Luint16 index, Lint32 data)
{
	switch(index)
	{
		case  10005: sPC.sLp.PICOMMS_LOOP_INT32 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the UINT64 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLuint64(Luint16 index, Luint64 data)
{
	switch(index)
	{
		case  10006: sPC.sLp.PICOMMS_LOOP_UINT64 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT64 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLint64(Luint16 index, Lint64 data)
{
	switch(index)
	{
		case  10007: sPC.sLp.PICOMMS_LOOP_INT64 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the FLOAT32 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLfloat32(Luint16 index, Lfloat32 data)
{
	switch(index)
	{
		case  10008: sPC.sLp.PICOMMS_LOOP_FLOAT32 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the FLOAT64 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLfloat64(Luint16 index, Lfloat64 data)
{
	switch(index)
	{
		case  10009: sPC.sLp.PICOMMS_LOOP_FLOAT64 = data;
				break;
	}
}

#endif//C_LOCALDEF__LCCM653__ENABLE_PI_COMMS

#ifndef C_LOCALDEF__LCCM653__ENABLE_PI_COMMS
	#error
#endif

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

