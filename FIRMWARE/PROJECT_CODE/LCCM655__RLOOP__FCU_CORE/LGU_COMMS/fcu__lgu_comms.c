/**
 * @file		FCU__LGU_COMMS.C
 * @brief		Landing Gear communication interface
 *
 * @note:
 * Messaging Format
 * Header: 0x55
 * U16: Command
 * U32/F32/S32 Value
 * u8CRC
 * u8Footer 0xAA
 *
 *
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
 * @addtogroup FCU__LGU
 * @ingroup FCU
 * @{ */


#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any LGU comms variables
 * 
 * @st_funcMD5		A93FE719DA5923B4B04B785B755724C5
 * @st_funcID		LCCM655R0.FILE.080.FUNC.001
 */
void vFCU_LGU__Init(void)
{

	//int our variables
	sFCU.sLGU.eCommsState = LGU_COMMS_STATE__IDLE;
	sFCU.sLGU.u8TxRequest = 0U;
	sFCU.sLGU.u8RxCounter = 0U;
	sFCU.sLGU.u8RxAvail = 0U;


}


/***************************************************************************//**
 * @brief
 * Process the LGU comms
 * 
 * @st_funcMD5		1893F9E9F9E79EEC289C564DE5CB757A
 * @st_funcID		LCCM655R0.FILE.080.FUNC.002
 */
void vFCU_LGU__Process(void)
{
	Luint8 * pu8Buffer;
	Luint8 u8Test;
	E_FCU_LGU_COMM_TYPES_T eType;

	//handle the state machine
	switch(sFCU.sLGU.eCommsState)
	{
		case LGU_COMMS_STATE__IDLE:
			//do nothing

			//do we need to tx?
			if(sFCU.sLGU.u8TxRequest == 1U)
			{
				//move to being a new transmission
				sFCU.sLGU.eCommsState = LGU_COMMS_STATE__TX_BEGIN;
			}
			else
			{
				if(sFCU.sLGU.u8RxAvail == 1U)
				{
					sFCU.sLGU.eCommsState = LGU_COMMS_STATE__PROCESS_RX;
				}
				else
				{
					//stay here
				}
			}


			break;

		case LGU_COMMS_STATE__TX_BEGIN:
			//begin a transmission
			sFCU.sLGU.u8TxCounter = 0U;
#ifndef WIN32
			u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
#else
			u8Test = 0U;
#endif
			if(u8Test == 0U)
			{
				//dma is not busy, move onto processing the tx
				sFCU.sLGU.eCommsState = LGU_COMMS_STATE__TX_PROCESS;
			}
			else
			{
				//wait here as DMA is busy
			}

			break;

		case LGU_COMMS_STATE__TX_PROCESS:

			//buffer pointer
			pu8Buffer = &sFCU.sLGU.sTxMessage.u8Header;

#ifndef WIN32
			//start the transaction.
			#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
				vRM4_SCI_DMA__Begin_Tx(SCI_CHANNEL__2, pu8Buffer, 9U);
			#endif
#else
			//win32 fake the transaction
#endif

			//clear the request
			sFCU.sLGU.u8TxRequest = 0U;

			//back to idle
			sFCU.sLGU.eCommsState = LGU_COMMS_STATE__IDLE;
			break;

		case LGU_COMMS_STATE__PROCESS_RX:

			//check our CRC
			u8Test = u8SWCRC__CRC8((const Luint8*)&sFCU.sLGU.sRxMessage.u8Header, 7U);
			if(u8Test == sFCU.sLGU.sRxMessage.u8CRC)
			{
				//match
				eType = (E_FCU_LGU_COMM_TYPES_T)sFCU.sLGU.sRxMessage.unCommand.u16;
				switch(eType)
				{

					case LGU_COM__LGU_FCU__TX_STATUS:
						//LGU updating its status
						break;

				}//switch(eType)
			}
			else
			{
				//todo: error counter
			}

			//back to idle
			sFCU.sLGU.eCommsState = LGU_COMMS_STATE__IDLE;
			break;

		default:
			//do nothing
			break;

	}//switch(sFCU.sLGU.eCommsState)

}

//send a u32 value
Lint16 s16FCU_LGU__Tx_MessageU32(E_FCU_LGU_COMM_TYPES_T eType, Luint32 u32Value)
{
	Lint16 s16Return;

	//make sure we are not already in progress
	if(sFCU.sLGU.u8TxRequest == 1U)
	{
		s16Return = -1;
	}
	else
	{
		//format the message
		sFCU.sLGU.sTxMessage.u8Header = 0x55;
		sFCU.sLGU.sTxMessage.unCommand.u16 = (Luint16)eType;
		sFCU.sLGU.sTxMessage.unValue.u32 = u32Value;
		sFCU.sLGU.sTxMessage.u8CRC = u8SWCRC__CRC8((const Luint8*)&sFCU.sLGU.sTxMessage.u8Header, 7U);
		sFCU.sLGU.sTxMessage.u8Footer = 0xAA;

		s16Return = 0;
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Rx a byte from the network
 * 
 * @param[in]		u8Value				The value from the UART
 * @st_funcMD5		E3739ED00B54EFF5AA8A0A4EC64ED32E
 * @st_funcID		LCCM655R0.FILE.080.FUNC.003
 */
void vFCU_LGU__Rx_Byte(Luint8 u8Value)
{
	if(sFCU.sLGU.u8RxAvail == 0U)
	{
		switch(sFCU.sLGU.u8RxCounter)
		{
			case 0:
				if(u8Value == 0x55)
				{
					sFCU.sLGU.sRxMessage.u8Header = u8Value;
					sFCU.sLGU.u8RxCounter++;
				}
				else
				{
					//wrong header, do nothing.
				}
				break;

			case 1:
				sFCU.sLGU.sRxMessage.unCommand.u8[0] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 2:
				sFCU.sLGU.sRxMessage.unCommand.u8[1] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 3:
				sFCU.sLGU.sRxMessage.unValue.u8[0] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 4:
				sFCU.sLGU.sRxMessage.unValue.u8[1] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 5:
				sFCU.sLGU.sRxMessage.unValue.u8[2] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 6:
				sFCU.sLGU.sRxMessage.unValue.u8[3] = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 7:
				sFCU.sLGU.sRxMessage.u8CRC = u8Value;
				sFCU.sLGU.u8RxCounter++;
				break;

			case 8:
				if(u8Value == 0xAAU)
				{
					sFCU.sLGU.sRxMessage.u8Footer = u8Value;
					sFCU.sLGU.u8RxCounter++;
					sFCU.sLGU.u8RxAvail = 1U;
				}
				else
				{
					sFCU.sLGU.u8RxCounter = 0U;
					sFCU.sLGU.u8RxAvail = 0U;
					//bad message
				}
				break;

			default:
				break;
		}//switch(sFCU.sLGU.u8RxCounter)
	}
	else
	{
		//error, have not finsihed processing last unit
	}


}

#endif //C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM
#ifndef C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM
	#error
#endif

/** @} */
/** @} */
/** @} */

