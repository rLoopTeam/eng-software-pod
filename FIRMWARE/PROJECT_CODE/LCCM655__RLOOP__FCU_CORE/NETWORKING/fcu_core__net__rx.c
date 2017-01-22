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
 * @st_funcMD5		E00D3EC11B8F5D177569A25E9C9C882D
 * @st_funcID		LCCM655R0.FILE.018.FUNC.002
 */
void vFCU_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];
	Lfloat32 f32Block[4];
	Lint32 s32Block[4];

	//make sure we are rx'ing on our port number
	if(u16DestPort == C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		f32Block[0] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		f32Block[1] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		f32Block[2] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		f32Block[3] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		s32Block[0] = s32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		s32Block[1] = s32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		s32Block[2] = s32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		s32Block[3] = s32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);


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

			case NET_PKT__FCU_GEN__DAQ_ENABLE:
				#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
					if(u32Block[0] == 1U)
					{
						vDAQ__Streaming_On();
					}
					else
					{
						//switch off the DAQ
						vDAQ__Streaming_Off();

						//flush out whats left
						vDAQ__ForceFlush();
					}
				#endif
				break;

			case NET_PKT__FCU_GEN__DAQ_FLUSH:
				//tell the DAQ to flush.
				#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
					vDAQ__ForceFlush();
				#endif
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

			case NET_PKT__LASER_DIST__ENABLE_EMULATION_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
					//switch on emu mode
					vFCU_LASERDIST_ETH__Enable_EmulationMode(u32Block[0], u32Block[1]);
				#endif
				break;

			case NET_PKT__LASER_DIST__RAW_EMULATION_VALUE:
				#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
					vFCU_LASERDIST_ETH__Emulation_Injection(f32Block[0]);
				#endif
				break;

			case NET_PKT__LASER_CONT__REQUEST_LASER_DATA:
				//transmit the laser contrast sub system
				switch(u32Block[0])
				{
					case 0:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_0;
						break;
					case 1:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_1;
						break;
					case 2:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_2;
						break;

					default:
						break;
				}
				break;

			case NET_PKT__FCU_BRAKES__ENABLE_DEV_MODE:
				//set the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__Enable_DevMode(u32Block[0], 0xABCD0987U);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW:
				//move the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MoveMotor_RAW(u32Block[0], u32Block[1]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MOVE_IBEAM:
				//move the brakes ref to the I-Bream
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MoveMotor_IBeam(f32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM:

				//Block 0 = Parameter Type
				//Block 1 = Channel 0, 1
				//Block 2 = Setting
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				switch(u32Block[0])
				{

					case 0U:
						//Max Acecl
						vSTEPDRIVE_MEM__Set_MaxAngularAccel(u32Block[1], s32Block[2]);
						break;

					case 1U:
						//microns/rev
						vSTEPDRIVE_MEM__Set_PicoMeters_PerRev(u32Block[1], s32Block[2]);
						break;

					case 2U:
						//maxRPM
						vSTEPDRIVE_MEM__Set_MaxRPM(u32Block[1], s32Block[2]);
						break;

					case 3U:
						//set microstep resolution
						vSTEPDRIVE_MEM__Set_MicroStepResolution(u32Block[1], u32Block[2]);
						break;

					default:
						//fall on
						break;

				}//switch(u32Block[0])

				//once these have been updated, re-transmit
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM;

				#endif
				break;

			case NET_PKT__FCU_BRAKES__REQ_MOTOR_PARAM:
				//transmit the motor data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM;
				break;

			case NET_PKT__FCU_BRAKES__START_CAL_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_CAL__BeginCal(u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__INIT:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES__Begin_Init(u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MLP_ZEROSPAN:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MLP_ZeroSpan(u32Block[0], u32Block[1], u32Block[2]);
				#endif
				break;


			case NET_PKT__FCU_THROTTLE__ENABLE_DEV_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
					vFCU_THROTTLE_ETH__Enable_DevMode(u32Block[0], 0x77558833U);
				#endif
				break;

			case NET_PKT__FCU_THROTTLE__SET_RAW_THROTTLE:
				#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
					vFCU_THROTTLE_ETH__Set_Throttle((Luint8)u32Block[0], (Luint16)u32Block[1], (E_THROTTLE_CTRL_T)u32Block[2]);
				#endif
				break;

			case NET_PKT__FCU_THROTTLE__REQUEST_DATA:
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_THROTTLE__TX_DATA;
				break;

			case NET_PKT__FCU_ASI__REQUEST_PUSHER_DATA:
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_ASI__TX_PUSHER_DATA;
				break;

			case NET_PKT__FCU_FLT__TX_TRACK_DB_CHUNK:
				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
				//Host to send a chunk to us

				//inc to the block3's start
				pu8Payload += 12U;

				//upload the chunk
				vFCU_FCTL_TRACKDB_MEM__UploadChunk(u32Block[0], u32Block[1], u32Block[2], pu8Payload);

				#endif
				break;

			case NET_PKT__FCU_FLT__SELECT_TRACK_DB:
				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
					vFCU_FCTL_TRACKDB__Set_CurrentDB(u32Block[0], u32Block[1]);
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


