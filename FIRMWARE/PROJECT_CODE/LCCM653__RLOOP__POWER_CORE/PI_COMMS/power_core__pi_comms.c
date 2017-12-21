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

#include <LCCM653__RLOOP__POWER_CORE/PI_COMMS/power_core__pi_comms__types.h>

//The PICOMMS RX Callbacks
void vPWRNODE_PICOMMS__recvLuint8(Luint16 u16Index, Luint8 data);
void vPWRNODE_PICOMMS__recvLint8(Luint16 index, Lint8 data);
void vPWRNODE_PICOMMS__recvLuint16(Luint16 index, Luint16 data);
void vPWRNODE_PICOMMS__recvLint16(Luint16 index, Lint16 data);
void vPWRNODE_PICOMMS__recvLuint32(Luint16 u16Index, Luint32 u32Data);
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
	sPWRNODE.sPiComms.u8100MS_Timer = 0U;

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
			//sPWRNODE.sPiComms.eState = PICOM_STATE__SETUP_FRAME;

			if(sPWRNODE.sPiComms.u8100MS_Timer == 1U)
			{
				//only do a new frame the DMA is not busy
				u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
				if(u8Test == 0U)
				{
					sPWRNODE.sPiComms.eState = PICOM_STATE__SETUP_FRAME;

					sPWRNODE.sPiComms.u8100MS_Timer = 0U;
				}
			}
			else
			{

			}

			break;

		case PICOM_STATE__SETUP_FRAME:
			//start a new frame
			PICOMMS_TX_beginFrame();

			//change states
			sPWRNODE.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;
			break;

		case PICOM_STATE__ASSEMBLE_BUFFER:

			//add the node temperature
			vPICOMMS_TX__Add_F32(PI_PACKET__PWRNODE__NODE_TEMP_RETURN, f32PWRNODE_NODETEMP__Get_DegC());

			//node pressure
			vPICOMMS_TX__Add_F32(PI_PACKET__PWRNODE__NODE_PRESS_RETURN, f32PWRNODE_NODEPRESS__Get_Pressure_Bar());


			//add as many more params as you need depending on current tx state.

			sPWRNODE.sPiComms.eState = PICOM_STATE__START_DMA;

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
				//cleanup the DMA interrupts for next time.
				vRM4_SCI_DMA__Cleanup(SCI_CHANNEL__2);

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

//100ms timer tick
void vPWRNODE_PICOMMS__100MS_ISR(void)
{
	//set the flag
	sPWRNODE.sPiComms.u8100MS_Timer = 1U;

}

/***************************************************************************//**
 * @brief
 * Process all the UINT8 parameters sent from the GS.
 *
 */
void vPWRNODE_PICOMMS__recvLuint8(Luint16 u16Index, Luint8 data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{
		case PI_PACKET__PWRNODE__NODE_PRESS_STREAM_CONTROL:

			break;

		case PI_PACKET__PWRNODE__NODE_TEMP_STREAM_CONTROL:

			break;

		case PI_PACKET__PWRNODE__CHG_RELAY_CONTROL:
			#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
			switch(data)
			{
				case 0U:
					vPWRNODE_CHG_RELAY__Off();
					break;
				case 1U:
					vPWRNODE_CHG_RELAY__On();
					break;
				default:
					break;
			}//switch(data)
			#endif
			break;

	}

/*
	switch(index)
	{
		case  10000: sPC.sLp.PICOMMS_LOOP_UINT8 = data;
				break;
	}
*/

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
void vPWRNODE_PICOMMS__recvLuint32(Luint16 u16Index, Luint32 u32Data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{
		case PI_PACKET__PWRNODE__POD_SAFE_UNLOCK_KEY:
			//unlock the pod safe key
			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
				vPWRNODE_DC__Pod_Safe_Unlock(u32Data);
			#endif
			break;

		case PI_PACKET__PWRNODE__POD_SAFE_COMMAND:
			//execute pod safe.
			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
				vPWRNODE_DC__Pod_Safe_Go();
			#endif
			break;

		default:
			//do nothing.
			break;

	}//switch((E_PICOMMS__PACKET_TYPES_T)index)

	/*
	switch(u16Index)
	{
		case  10004: sPC.sLp.PICOMMS_LOOP_UINT32 = data;
				break;
	}
	*/
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

#else
void vPICOMMS_RX__Receive_Bytes(Luint8 *data, Luint16 length)
{
	//do nothing.
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

