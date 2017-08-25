/**
 * @file		LGU__ETHERNET.C
 * @brief		Ethernet interface
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.009
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup LGU__ETHERNET
 * @ingroup LGU
 * @{
*/
#include <LCCM667__RLOOP__LGU/lgu.h>
#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_LGU__MAIN sLGU;

//locals
void vLGU_ETH__Transmit(E_NET__PACKET_T ePacketType);

/***************************************************************************//**
 * @brief
 * Init the Eth subsystem
 * 
 * @st_funcMD5		C3B4CC3A5109238CBBFF035E96BE38B9
 * @st_funcID		LCCM667R0.FILE.009.FUNC.001
 */
void vLGU_ETH__Init(void)
{

	//reset our data
	sLGU.sUDPDiag.eTxPacketType = NET_PKT__NONE;
	sLGU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
	sLGU.sUDPDiag.u810MS_Flag = 0U;
	sLGU.sUDPDiag.u8250MS_Flag = 0U;


	//SIL3 OUID
	sLGU.sEthernet.u8MACAddx[0] = 0x00U;
	sLGU.sEthernet.u8MACAddx[1] = 0x26U;
	sLGU.sEthernet.u8MACAddx[2] = 0x80U;

	//PCB MAC
	sLGU.sEthernet.u8MACAddx[3] = 0x01U;
	sLGU.sEthernet.u8MACAddx[4] = 0x00U;
	sLGU.sEthernet.u8MACAddx[5] = C_RLOOP_NET_IP__LGU;

	//IP
	sLGU.sEthernet.u8IPAddx[0] = 192U;
	sLGU.sEthernet.u8IPAddx[1] = 168U;
	sLGU.sEthernet.u8IPAddx[2] = C_RLOOP_NET_IP__SUBNET;
	sLGU.sEthernet.u8IPAddx[3] = C_RLOOP_NET_IP__LGU;


#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sLGU.sEthernet.u8MACAddx[0], &sLGU.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sLGU.sEthernet.u8MACAddx[0], &sLGU.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * Process any ethernet tasks
 * 
 * @st_funcMD5		9E5A0DA7B9FA07D662950116C2EDEE30
 * @st_funcID		LCCM667R0.FILE.009.FUNC.002
 */
void vLGU_ETH__Process(void)
{
	Luint8 u8Test;
	Luint8 u8Flag;
	E_NET__PACKET_T eType;


#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vSIL3_ETH__Process();

	u8Test = u8LGU_ETH__Is_LinkUp();
	if(u8Test == 1U)
	{

		//every 250ms broadcast our status
		if(sLGU.sUDPDiag.u8250MS_Flag > 25U)
		{
			//send the LGU status
			vLGU_ETH__Transmit(NET_PKT__LGU__TX_STATUS_PACKET);

			//clear now
			sLGU.sUDPDiag.u8250MS_Flag = 0U;

		}
		else
		{

			//do we have a timer flag?
			if(sLGU.sUDPDiag.u810MS_Flag == 1U)
			{
				if(sLGU.sUDPDiag.eTxStreamingType != NET_PKT__NONE)
				{
					//send it
					vLGU_ETH__Transmit(sLGU.sUDPDiag.eTxStreamingType);

				}
				else
				{
					//no packet type.
				}

				//clear the flag now
				sLGU.sUDPDiag.u810MS_Flag = 0U;
			}
			else
			{
				//nope
				//eType = NET_PKT__NONE;
			}

		}

	}
	else
	{
		//not ready for ethernet yet
	}
}


/***************************************************************************//**
 * @brief
 * Transmit an ethernet packet
 * 
 * @param[in]		ePacketType				The packet type
 * @st_funcMD5		CC9DE3848062E90EC70C3EBD67FDEF34
 * @st_funcID		LCCM667R0.FILE.009.FUNC.006
 */
void vLGU_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 *pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		/** Transmit the LGU status packet over the network */
		case NET_PKT__LGU__TX_STATUS_PACKET:

			u16Length = 4U + ((4U + 2U + 4U + 4U + 2U + 16U) * C_LGU__NUM_ACTUATORS);
			break;
		case NET_PKT__LGU__TX_ADC_CAL_PACKET:
			u16Length = ((2U + 2U + 4U + 4U + 2U + 16U) * C_LGU__NUM_ACTUATORS);
			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (Luint16)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__LGU__TX_STATUS_PACKET:

				//top level fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				for(u8Counter = 0U; u8Counter < C_LGU__NUM_ACTUATORS; u8Counter++)
				{
					//fault flags for each actuator
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0xAAAABBBBU);
					pu8Buffer += 4U;

					//Raw ADC value
					vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, 0x1122U);
					pu8Buffer += 2U;

					//Actual extension
					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, -123);
					pu8Buffer += 4U;

					//Computed height
					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, 234);
					pu8Buffer += 4U;

					//Limit switch extend
					pu8Buffer[0] = 0U;

					//Limit switch retract
					pu8Buffer[1] = 1U;
					pu8Buffer += 2U;

					//spares
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;

				}//for(u8Counter = 0U; u8Counter < C_LGU__NUM_ACTUATORS; u8Counter++)
				break;

			case NET_PKT__LGU__TX_ADC_CAL_PACKET:

				for(u8Counter = 0U; u8Counter < C_LGU__NUM_ACTUATORS; u8Counter++)
				{

					//Raw ADC value
					vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, 0x1122U);
					pu8Buffer += 2U;

					//ADC Zero
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, -1);
					pu8Buffer += 2U;

					//ADC Span
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, -123);
					pu8Buffer += 4U;

					//Actual extension
					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, -123);
					pu8Buffer += 4U;

										//Limit switch extend
					pu8Buffer[0] = 0U;

					//Limit switch retract
					pu8Buffer[1] = 1U;
					pu8Buffer += 2U;

					//spares
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;

				}//for(u8Counter = 0U; u8Counter < C_LGU__NUM_ACTUATORS; u8Counter++)
				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__LGU, C_RLOOP_NET_PORT__LGU);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

/***************************************************************************//**
 * @brief
 * Is the eth link avail?
 * 
 * @st_funcMD5		540F753DE45DBA722D86226C6D08E788
 * @st_funcID		LCCM667R0.FILE.009.FUNC.003
 */
Luint8 u8LGU_ETH__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}

/***************************************************************************//**
 * @brief
 * RX a UDP packet off the ethernet stack
 * 
 * @param[in]		u16DestPort				Target port
 * @param[in]		u16Length				Payload length
 * @param[in]		*pu8Buffer				Pointer to the payload
 * @st_funcMD5		FBE43A0B12873DFDADE49E96A32D80E6
 * @st_funcID		LCCM667R0.FILE.009.FUNC.004
 */
void vLGU_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}

/***************************************************************************//**
 * @brief
 * Rx a safety udp packet.
 * 
 * @param[in]		u16Fault				Fault types
 * @param[in]		u16DestPort				Target port
 * @param[in]		ePacketType				Packet type
 * @param[in]		u16PayloadLength		Length of payload
 * @param[in]		*pu8Payload				Pointer to payload
 * @st_funcMD5		364C34B3EF4080FBC3AAD1C371F7F1C3
 * @st_funcID		LCCM667R0.FILE.009.FUNC.005
 */
void vLGU_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{
	Luint32 u32Block[4];
	Lfloat32 f32Block3;
	
	if(u16DestPort == C_RLOOP_NET_PORT__LGU)
	{
		//split up into easy to use blocks
		u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);
		f32Block3 = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet
		switch(ePacketType)
		{
			/** Permit network based streaming control */
			case NET_PKT__LGU__STREAMING_CONTROL:

				//if the host wants to stream data packets.
				if(u32Block[0] == 1U)
				{
					//streaming on
					sLGU.sUDPDiag.eTxStreamingType = (E_NET__PACKET_T)u32Block[1];
				}
				else
				{
					//streaming off
					sLGU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
				}

				break;

			case NET_PKT__LGU__MANUAL_MODE:

				//make sure we are safe
				if(u32Block[0] == 0xABAB1122U)
				{

					//block 1 is the index

					//block 2 is the direction
					vLGU_LIFT__Set_Direction((Luint8)u32Block[1], (TE_LGU__LIFT_DIRECTIONS)u32Block[2]);

					//block 3 is the speed
					vLGU_LIFT__Set_Speed((Luint8)u32Block[1], f32Block3);

				}
				else
				{
					//wrong key
				}
				break;

			default:
				//not for us
				break;

		}//switch(ePacketType)
	}
	else
	{
		//not for us
	}
	
}

/***************************************************************************//**
 * @brief
 * 10ms Interrupt
 * 
 * @st_funcMD5		4FA4E1AC352E516A4F7E399CF5EFE075
 * @st_funcID		LCCM667R0.FILE.009.FUNC.007
 */
void vLGU_ETH__10MS_ISR(void)
{
	sLGU.sUDPDiag.u810MS_Flag = 1U;
	sLGU.sUDPDiag.u8250MS_Flag++;
}

#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif

/** @} */
/** @} */
/** @} */

