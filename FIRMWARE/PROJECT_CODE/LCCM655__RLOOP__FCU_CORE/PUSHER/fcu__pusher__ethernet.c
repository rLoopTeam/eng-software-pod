/**
 * @file		FCU__PUSHER__ETHERNET.C
 * @brief		Pusher Diagnostics
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
 * @addtogroup FCU__PUSHER__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any pusher ethernet issues
 * 
 * @st_funcMD5		7043E37FEECE05A55BE6E1F0ED88BFB3
 * @st_funcID		LCCM655R0.FILE.076.FUNC.001
 */
void vFCU_PUSHER_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Transmit a pusher ethernet packet
 * 
 * @param[in]		ePacketType				The packet type.
 * @st_funcMD5		5E7952DAD1DF74B9D3AFA597A5E4BF9F
 * @st_funcID		LCCM655R0.FILE.076.FUNC.002
 */
void vFCU_PUSHER_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_ASI__TX_PUSHER_DATA:
			u16Length = 4U + 5U + 4U;
			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__FCU_ASI__TX_PUSHER_DATA:

				//top level fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sPusher.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				pu8Buffer[0] = sFCU.sPusher.u8Pusher_Status;
				pu8Buffer[1] = sFCU.sPusher.sSwitches[0].u8EdgeFlag;
				pu8Buffer[2] = sFCU.sPusher.sSwitches[1].u8EdgeFlag;
				pu8Buffer[3] = sFCU.sPusher.sSwitches[0].u8SwitchState;
				pu8Buffer[4] = sFCU.sPusher.sSwitches[1].u8SwitchState;
				pu8Buffer += 5U;

				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sPusher.u32SwtichTimer);
				pu8Buffer += 4U;


				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length,
							C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER,
							C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}



#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_PUSHER
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
