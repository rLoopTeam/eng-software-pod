/**
 * @file		FCU__LASER_CONT__ETHERNET.C
 * @brief		Ethernet UDP diagnostics for the contrast laser system
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
 * @addtogroup FCU__LASER_CONT__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Transmit a laser contrast eth packet
 * 
 * @param[in]		ePacketType				The packet type
 * @st_funcMD5		6B791D3EC4933B7A613646E3053E1F47
 * @st_funcID		LCCM655R0.FILE.060.FUNC.001
 */
void vFCU_LASERCONT_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;
	Luint8 u8Counter2;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__LASER_CONT__TX_LASER_DATA_0:
			u16Length = 24U + 6U;
			u16Length += (C_FCU__LASER_CONTRAST__MAX_STRIPES * 16U);
			u8Device = 0U;
			break;

		case NET_PKT__LASER_CONT__TX_LASER_DATA_1:
			u16Length = 24U + 6U;
			u16Length += (C_FCU__LASER_CONTRAST__MAX_STRIPES * 16U);
			u8Device = 1U;
			break;

		case NET_PKT__LASER_CONT__TX_LASER_DATA_2:
			u16Length = 24U + 6U;
			u16Length += (C_FCU__LASER_CONTRAST__MAX_STRIPES * 16U);
			u8Device = 2U;
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
			case NET_PKT__LASER_CONT__TX_LASER_DATA_0:
			case NET_PKT__LASER_CONT__TX_LASER_DATA_1:
			case NET_PKT__LASER_CONT__TX_LASER_DATA_2:


				//fault flags from the upper level system
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//spare 1:4
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//send the fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sSensors[u8Device].sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;


				//Rising Edge Count
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sContrast.sTimingList[u8Device].u16RisingCount);
				pu8Buffer+=2;

				//Falling edge count
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sContrast.sTimingList[u8Device].u16FallingCount);
				pu8Buffer+=2;

				//max stripes
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, C_FCU__LASER_CONTRAST__MAX_STRIPES);
				pu8Buffer+=2;


				//send the timing list, rising
				for(u8Counter2 = 0U; u8Counter2 < C_FCU__LASER_CONTRAST__MAX_STRIPES; u8Counter2++)
				{

					vNUMERICAL_CONVERT__Array_U64(pu8Buffer, sFCU.sContrast.sTimingList[u8Device].u64RisingList[u8Counter2]);
					pu8Buffer+=8;

				}//for(u8Counter2 = 0U; u8Counter2 < C_FCU__LASER_CONTRAST__MAX_STRIPES; u8Counter2++)

				//send the timing list, falling
				for(u8Counter2 = 0U; u8Counter2 < C_FCU__LASER_CONTRAST__MAX_STRIPES; u8Counter2++)
				{

					vNUMERICAL_CONVERT__Array_U64(pu8Buffer, sFCU.sContrast.sTimingList[u8Device].u64FallingList[u8Counter2]);
					pu8Buffer+=8;

				}//for(u8Counter2 = 0U; u8Counter2 < C_FCU__LASER_CONTRAST__MAX_STRIPES; u8Counter2++)


				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET__FCU__PORT, C_RLOOP_NET__FCU__PORT);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
