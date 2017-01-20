/**
 * @file		FCU__FAULTS__ETHERNET.C
 * @brief		Fault Eth Interface
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
 * @addtogroup FCU__FAULTS__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init eth portion of fault flags transmit
 * 
 * @st_funcMD5		4806FF242973B11F8CD8DECBD90C9BD0
 * @st_funcID		LCCM655R0.FILE.078.FUNC.001
 */
void vFCU_FAULTS_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Transmit a faults eth packet
 * 
 * @param[in]		ePacketType				Type
 * @st_funcMD5		ED9883E4B933BF58ADB435687B8D8D5F
 * @st_funcID		LCCM655R0.FILE.078.FUNC.002
 */
void vFCU_FAULTS_ETH__Transmit(E_NET__PACKET_T ePacketType)
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
		case NET_PKT__FCU_GEN__TX_ALL_FAULT_FLAGS:
			u16Length = ((23U + C_LOCALDEF__LCCM487__NUM_DEVICES + C_FCU__NUM_LASERS_OPTONCDT) * 4U);
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
			case NET_PKT__FCU_GEN__TX_ALL_FAULT_FLAGS:

				//top level fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32FCU_FAULTS__Get_FaultFlags());
				pu8Buffer += 4U;

				//accel
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sAccel.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//MMA0:1
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32MMA8451__Get_FaultFlags(0U));
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32MMA8451__Get_FaultFlags(1U));
				pu8Buffer += 4U;

				//SC16 System
				for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32SC16__Get_FaultFlags(u8Counter));
					pu8Buffer += 4U;

				}

				//ASI
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sASI.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//Brakes
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sBrakesGlobal.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//DAQ
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//laser contrast sensors
				//Top Level
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//each sensor
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sSensors[0].sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sSensors[1].sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sContrast.sSensors[2].sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//laser distance
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//optos, top level
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserOpto.sOptoLaser[u8Counter].sFaultFlags.u32Flags[0]);
					pu8Buffer += 4U;

				}

				//10
				//networking
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//pusher
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sPusher.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//AMC7812
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32AMC7812__Get_FaultFlags());
				pu8Buffer += 4U;

				//Throttle Subsystem
				#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sThrottle.sFaultFlags.u32Flags[0]);
					pu8Buffer += 4U;
				#else
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
				#endif

				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;


				//Flight control system
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sFlightControl.sTrackDB.sFaultFlags.u32Flags[0]);
					pu8Buffer += 4U;
				#else
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
				#endif




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
