/**
 * @file		FCU_CORE__NET__RX.C
 * @brief		Network Rx portion
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__CORE_NET_RX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Rx a normal UDP packet
 * 
 * @param[in]		u16DestPort				The dest port on the UDP frame
 * @param[in]		u16Length				Length of UDP payload
 * @param[in]		*pu8Buffer				Pointer to UDP payload
 * @st_funcMD5		0B2659AA6A5FE97E7C312A615612AAD9
 * @st_funcID		LCCM655R0.FILE.018.FUNC.001
 */
void vFCU_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//Todo
	//We can interpretate messages here,

	//pass to safety udp processor
	vSAFE_UDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}

/***************************************************************************//**
 * @brief
 * Rx a SafetyUDP
 * 
 * @param[in]		u16Fault				Any fault flags with the Tx.
 * @param[in]		u16DestPort				UDP Destination Port
 * @param[in]		ePacketType				SafeUDP packet Type
 * @param[in]		u16PayloadLength		Length of only the SafeUDP payload
 * @param[in]		*pu8Payload				Pointer to the payload bytes
 * @st_funcMD5		B60C07200ADBE561C1A9CD55076889FB
 * @st_funcID		LCCM655R0.FILE.018.FUNC.002
 */
void vFCU_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];

	//make sure we are rx'ing on our port number
	if(u16DestPort == C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet that came in
		switch((E_NET__PACKET_T)ePacketType)
		{


			case NET_PKT__FCU_GEN__POD_STOP_COMMAND:
				if(u32Block[0] == 0x1234ABCDU)
				{
					//transition to the pod stop phase.

					/*9.2.2. Execute Pod-Safe Command from GS
					 * The following requirements describe how the Pod-Safe Command from Ground Station should be implemented.
					 * The Pod-Safe Command from the Ground Station shall be executed in two steps, so as to prevent operator
					 * from triggering it by mistake.
					 * Upon reception of the Authorize Pod-Safe Command from the Ground Station,
					 * the FCU shall set pod safe command authorized to true.
					 */
				}
				else
				{
					//maybe should log this error.
				}
				break;

			case NET_PKT__FCU_GEN__POD_EMULATION_CONTROL:

				break;

			case NET_PKT__FCU_GEN__STREAMING_CONTROL:
				//if the host wants to stream data packets.
				if(u32Block[0] == 1U)
				{
					//streaming on
					sFCU.sUDPDiag.eTxStreamingType = (E_NET__PACKET_T)u32Block[1];
				}
				else
				{
					//streaming off
					sFCU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
				}

				break;


			case NET_PKT__FCU_ACCEL__REQUEST_CAL_DATA:
				//Host wants us to transmit the calibration data for the accelerometers system
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_ACCEL__TX_CAL_DATA;
				break;

			case NET_PKT__FCU_ACCEL__REQUEST_FULL_DATA:
				//transmit a full data packet including g-force, etc
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_ACCEL__TX_FULL_DATA;
				break;

			case NET_PKT__FCU_ACCEL__AUTO_CALIBRATE:
				#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
					//enter auto calibration mode
					//block 0 = device
					vMMA8451_ZERO__AutoZero((Luint8)u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT:
				#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
					//Fine Zero adjustment on a particular axis
					//block 0 = device
					//block 1 = axis
					vMMA8451_ZERO__Set_FineZero((Luint8)u32Block[0], (MMA8451__AXIS_E)u32Block[1]);
				#endif
				break;


			case NET_PKT__LASER_OPTO__REQUEST_LASER_DATA:
				//transmit the laser opto's data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_OPTO__TX_LASER_DATA;
				break;

			case NET_PKT__LASER_DIST__REQUEST_LASER_DATA:
				//transmit the laser distance data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_DIST__TX_LASER_DATA;
				break;

			case NET_PKT__LASER_CONT__REQUEST_LASER_DATA:
				//transmit the laser contrast sub system
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_0;
				break;

			case NET_PKT__FCU_BRAKES__ENABLE_DEV_MODE:
				//set the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES__Enable_DevMode(u32Block[0], 0xABCD0987U);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW:
				//move the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES__Dev_MoveMotor(u32Block[0], u32Block[1]);
				#endif
				break;

			default:
				//do nothing
				break;

		}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)
	}
	else
	{
		//not for us
	}
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */


