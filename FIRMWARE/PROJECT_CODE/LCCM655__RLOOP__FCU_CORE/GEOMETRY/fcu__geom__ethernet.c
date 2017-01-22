/**
 * @file		FCU__GEOM__ETHERNET.C
 * @brief		Geometry interface over ethernet.
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
 * @addtogroup FCU__GEOM__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;


void vFCU_GEOM_ETH__Init(void)
{

}

void vFCU_GEOM_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_FLT__TX_GEOM_DATA:
			u16Length = 4U;
			u16Length += (C_FCU__GEOM__NUM_ITEMS_F32 * 3U);
			u16Length += (C_FCU__GEOM__NUM_ITEMS_S32 * 3U);
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
			case NET_PKT__FCU_FLT__TX_GEOM_DATA:


				//fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_F32; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32X);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32Y);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32Z);
					pu8Buffer += 4U;
				}

				for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_S32; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32X);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32Y);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32Z);
					pu8Buffer += 4U;
				}

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
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
