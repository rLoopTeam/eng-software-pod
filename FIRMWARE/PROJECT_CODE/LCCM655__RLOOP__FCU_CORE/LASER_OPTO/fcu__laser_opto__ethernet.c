/**
 * @file		FCU__LASER_OPTO__ETHERNET.C
 * @brief		Ethernet UDP diagnostics for the OptoNCDT
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
 * @addtogroup FCU__LASER_OPTO__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Transmit the laser opto packet
 * 
 * @param[in]		ePacketType			The packet type
 * @st_funcMD5		D48C04949DAE27BA171F3019620ED2B7
 * @st_funcID		LCCM655R0.FILE.055.FUNC.001
 */
void vFCU_LASEROPTO_ETH__Transmit(E_NET__PACKET_T ePacketType)
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
		case NET_PKT__LASER_OPTO__TX_LASER_DATA:
			u16Length = (C_FCU__NUM_LASERS_OPTONCDT * 24U) + 8U;
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
			case NET_PKT__LASER_OPTO__TX_LASER_DATA:

				//top level fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//spare
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//24
				for(u8Device = 0U; u8Device < C_FCU__NUM_LASERS_OPTONCDT; u8Device++)
				{

					//laser level fault flags
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Device].sFaultFlags.u32Flags[0]);
					pu8Buffer += 4U;

					//Count of number of "error code packets" returned from the laser
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Device].sCounters.u32ErrorCode);
					pu8Buffer += 4U;

					//First packet byte was wrong, may indicate some FIFO errors.
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Device].sCounters.u32Byte1Wrong);
					pu8Buffer += 4U;

					//Most Recent Laser Distance (RAW)
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Device].f32DistanceRAW);
					pu8Buffer += 4U;

					//Filtered laser packet from filtering system
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Device].sFiltered.f32FilteredValue);
					pu8Buffer += 4U;

					//Spare
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;

				}//for(u8Device = 0U; u8Device < C_FCU__NUM_LASERS_OPTONCDT; u8Device++)
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
#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
