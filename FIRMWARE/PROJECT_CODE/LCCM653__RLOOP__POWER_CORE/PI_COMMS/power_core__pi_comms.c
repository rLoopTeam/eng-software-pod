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

//the structure
struct _strPWRNODE sPWRNODE;

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
			rI2CTX_beginFrame();

			//change states
			sPWRNODE.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;
			break;

		case PICOM_STATE__ASSEMBLE_BUFFER:

			//add 0xAA as param 1
			rI2CTX_addParameter_uint8(0x0001U, 0xAA);

			//add as many more params as you need depending on current tx state.

			sPWRNODE.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;

			break;

		case PICOM_STATE__START_DMA:
			//end the frame
			u32Length = (Luint32)rI2CTX_endFrame();

			//get the buffer pointer
			pu8Buffer = pu8I2CTx__Get_BufferPointer();

			//todo, probably should check transaction is not running

			//start the transaction.
			vRM4_SCI_DMA__Begin_Tx(SCI_CHANNEL__2, pu8Buffer, u32Length);

			//change state
			sPWRNODE.sPiComms.eState = PICOM_STATE__WAIT_DMA;
			break;

		case PICOM_STATE__WAIT_DMA:

			//test if the DMA is running
			u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
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


#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

