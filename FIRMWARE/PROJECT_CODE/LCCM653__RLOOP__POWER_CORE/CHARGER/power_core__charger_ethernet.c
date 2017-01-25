/**
 * @file		power_core__charger_ethernet.c
 * @brief		Ethernet UDP diagnostics for current reading
 * @author		Edward Chan
 * @copyright	rLoop Inc.
 */
#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the Eth Portion
 *
 * @st_funcMD5
 * @st_funcID
 */
void vPWR_CHARGER_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Tx an eth packet
 *
 * @param[in]		ePacketType				The packet type.
 * @st_funcMD5
 * @st_funcID
 */
void vPWR_CHARGER_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__PWR_CURRENT__TX_CURRENT_STATUS:
			u16Length = 4U;
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
			case NET_PKT__PWR_CURRENT__TX_CURRENT_STATUS:
				//Current Reading
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sHASS600.f32HASS_CurrentReading);
				pu8Buffer += 4U;
			default:
				//fall on
				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, sPWRNODE.u16EthPort, sPWRNODE.u16EthPort);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

#endif //#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_ETHERNET
	#error
#endif

