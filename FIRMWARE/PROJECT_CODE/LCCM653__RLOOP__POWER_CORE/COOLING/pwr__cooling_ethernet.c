/**
 * @file		pwr__cooling_ethernet.c
 * @brief		Ethernet UDP diagnostics for cooling system
 * @author		Edward Chan
 * @copyright	rLoop Inc.
 */

#include "../power_core.h"

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
void vPWR_COOLING_ETH__Init(void)
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

void vPWR_COOLING_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__PWR_COOLING__TX_COOLING_STATUS:
			u16Length = 5U;
			u16Length += POWER_COOLING__MAX_HOVERENG * 6U;
			u16Length += POWER_COOLING__MAX_EDDYBRAKES * 6U;

			//TODO
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
			case NET_PKT__PWR_COOLING__TX_COOLING_STATUS:
				//Cooling System State
				pu8Buffer[0] = (Luint8) sPWRNODE.sCooling.eMainState;
				pu8Buffer += 1U;

				//100ms counters
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sPWRNODE.sCooling.u32100MS_Count);
				pu8Buffer += 4U;

				//Hover Engine Cooling Subsystem
				for(u8Device = 0; u8Device < POWER_COOLING__MAX_HOVERENG; u8Device++)
				{
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Device].f32Temperature);
					pu8Buffer += 4U;

					pu8Buffer[0] = (Luint8) sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Device].eState;
					pu8Buffer += 1U;

					pu8Buffer[0] = (Luint8) sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Device].eHoverSolenoidState;
					pu8Buffer += 1U;
				}

				//Eddy Brake Cooling Subsystem
				for(u8Device = 0; u8Device < POWER_COOLING__MAX_EDDYBRAKES; u8Device++)
				{
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Device].f32Temperature);
					pu8Buffer += 4U;

					pu8Buffer[0] = (Luint8) sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Device].eState;
					pu8Buffer += 1U;

					pu8Buffer[0] = (Luint8) sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Device].eEddySolenoidState;
					pu8Buffer += 1U;
				}


				break;

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


