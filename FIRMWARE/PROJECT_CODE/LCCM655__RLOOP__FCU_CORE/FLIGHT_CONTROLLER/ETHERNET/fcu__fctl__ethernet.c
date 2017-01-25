/**
 * @file		FCU__FCTL__ETHERNET.C
 * @brief		Fligth controller ethernet interface
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
 * @addtogroup FCU__FCTL__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init Eth
 * 
 * @st_funcMD5		28391E45A0FE140F795717C331017DDF
 * @st_funcID		LCCM655R0.FILE.077.FUNC.001
 */
void vFCU_FCTL_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Process FCU Eth
 * 
 * @param[in]		ePacketType				Packet Type
 * @st_funcMD5		602081C434EB3CDBD00C0ED2BFE3232D
 * @st_funcID		LCCM655R0.FILE.077.FUNC.002
 */
void vFCU_FCTL_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_GEN__TX_MISSION_DATA:
			u16Length = 11U;
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
			case NET_PKT__FCU_GEN__TX_MISSION_DATA:

				//top level fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32FCU_FAULTS__Get_FaultFlags());
				pu8Buffer += 4U;

				//mission state
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, (Luint16)sFCU.eMissionPhase);
				pu8Buffer += 2U;

				//current track database
				pu8Buffer[0] = (Luint8)sFCU.sFlightControl.sTrackDB.u32CurrentDB;
				pu8Buffer += 1U;

				//pod health
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sPodHealth.sHealthFlags.u32Flags[0]);
				pu8Buffer += 4U;


				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length,
				C_RLOOP_NET__FCU__PORT,
							C_RLOOP_NET__FCU__PORT);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}



#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
