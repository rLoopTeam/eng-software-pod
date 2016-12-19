/**
 * @file		FCU__NET__SPACEX_TX.C
 * @brief		SpaceX specific network transmission
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
 * @addtogroup FCU__CORE_NET_SPACEX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

//init the spaceX timed network transmission process
void vFCU_NET_SPACEX_TX__Init(void)
{
	//Clear the timer flag
	sFCU.sSpaceX.u8100MS_Flag = 0U;

}


//do the transmission
void vFCU_NET_SPACEX_TX__Process(void)
{
	Luint8 u8Test;
	Luint16 u16PacketLength;
	Lint16 s16Return;
	Luint32 u32Buffer;
	Luint8 *pu8Return;

	//do we have a timer flag?
	if(sFCU.sSpaceX.u8100MS_Flag == 1U)
	{
		//send the UDP stream
		//see if we have space to transmit
		u8Test = u8ETHERNET_FIFO__Is_Empty();
		if(u8Test == 1U)
		{

			//add space for the network packet
			u16PacketLength = 32U;
			s16Return = s16ETHERNET_FIFO__Push(u16PacketLength);
			if(s16Return >= 0)
			{

				//get a pointer to the buffer
				u32Buffer = u32ETHERNET_BUFFERDESC__Get_TxBufferPointer((Luint8)s16Return);
				pu8Return = (Luint8 *)u32Buffer;

				//append some data
				//Todo:
				vNUMERICAL_CONVERT__Array_U32(pu8Return, 0U);
				pu8Return += 4U;

				//send it
				vETHERNET_UDP__Transmit(u16PacketLength, 3000, 3000);

				//clear the flag only after a send because im sure SpX want the data
				//on the 100ms mark.
				sFCU.sSpaceX.u8100MS_Flag = 0U;

			}//if(s16Return >= 0)
			else
			{
				//FIFO error

			}//else if(s16Return >= 0)

		}//if(u8Test == 1U)
		else
		{
			//mo more space

		}//else if(u8Test == 1U)



	}
	else
	{
		//check later
	}


}


/***************************************************************************//**
 * @brief
 * To be called from the 10ms timer routine
 * Sets a flag to allow this module to determine that 10ms has elapsed
 *
 * @st_funcMD5		3A00D72EA0E8E8896C26BBDFA0E4F006
 * @st_funcID		LCCM655R0.FILE.019.FUNC.003
 */
void vFCU_NET_SPACEX_TX__100MS_ISR(void)
{
	sFCU.sSpaceX.u8100MS_Flag = 1U;
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */

