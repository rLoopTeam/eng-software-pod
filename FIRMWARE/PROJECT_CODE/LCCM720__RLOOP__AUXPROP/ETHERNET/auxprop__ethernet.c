/**
 * @file		AUXPROP__ETHERNET.C
 * @brief		Ethernet interface
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.011
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP__ETHERNET
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_APU__MAIN sAPU;

//locals
void vAPU_ETH__Transmit(E_NET__PACKET_T ePacketType);

/***************************************************************************//**
 * @brief
 * Init the enthernet
 * 
 * @st_funcMD5		245D6374D9C6798FA045BF18B64D19D1
 * @st_funcID		LCCM720R0.FILE.011.FUNC.001
 */
void vAPU_ETH__Init(void)
{
	//SIL3 OUID
	sAPU.sEthernet.u8MACAddx[0] = 0x00U;
	sAPU.sEthernet.u8MACAddx[1] = 0x26U;
	sAPU.sEthernet.u8MACAddx[2] = 0x80U;

	//PCB MAC
	sAPU.sEthernet.u8MACAddx[3] = 0x01U;
	sAPU.sEthernet.u8MACAddx[4] = 0x00U;
	sAPU.sEthernet.u8MACAddx[5] = C_RLOOP_NET_IP__APU;

	//IP
	sAPU.sEthernet.u8IPAddx[0] = 192U;
	sAPU.sEthernet.u8IPAddx[1] = 168U;
	sAPU.sEthernet.u8IPAddx[2] = C_RLOOP_NET_IP__SUBNET;
	sAPU.sEthernet.u8IPAddx[3] = C_RLOOP_NET_IP__APU;

	sAPU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
	sAPU.sUDPDiag.u8250MS_Flag = 0U;
	sAPU.sUDPDiag.u810MS_Flag = 0U;


#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sAPU.sEthernet.u8MACAddx[0], &sAPU.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sAPU.sEthernet.u8MACAddx[0], &sAPU.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * Process any ethernet tasks
 * 
 * @st_funcMD5		B1C72E9D3E451E3D44C39A83C5681A7A
 * @st_funcID		LCCM720R0.FILE.011.FUNC.002
 */
void vAPU_ETH__Process(void)
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

	u8Test = u8APU_ETH__Is_LinkUp();
	if(u8Test == 1U)
	{

		//every 250ms broadcast our status
		if(sAPU.sUDPDiag.u8250MS_Flag > 25U)
		{
			//send the LGU status
			vAPU_ETH__Transmit(NET_PKT__APU__STATUS_PACKET);

			//clear now
			sAPU.sUDPDiag.u8250MS_Flag = 0U;

		}
		else
		{

			//do we have a timer flag?
			if(sAPU.sUDPDiag.u810MS_Flag == 1U)
			{
				if(sAPU.sUDPDiag.eTxStreamingType != NET_PKT__NONE)
				{
					//send it
					vAPU_ETH__Transmit(sAPU.sUDPDiag.eTxStreamingType);

				}
				else
				{
					//no packet type.
				}

				//clear the flag now
				sAPU.sUDPDiag.u810MS_Flag = 0U;
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
 * Is the eth link avail?
 * 
 * @st_funcMD5		2D30B22DD544C659949B2EBCA8601D11
 * @st_funcID		LCCM720R0.FILE.011.FUNC.003
 */
Luint8 u8APU_ETH__Is_LinkUp(void)
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
 * @st_funcMD5		B846CEA87A9BE58828F4027FF8D670A6
 * @st_funcID		LCCM720R0.FILE.011.FUNC.004
 */
void vAPU_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}


/***************************************************************************//**
 * @brief
 * Transmit an eth packet
 * 
 * @param[in]		ePacketType				Eth packet type
 * @st_funcMD5		B198479C8F088A04FF82D4215B4935DB
 * @st_funcID		LCCM720R0.FILE.011.FUNC.006
 */
void vAPU_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 *pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Counter;
	Luint8 *pu8Temp;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__APU__STATUS_PACKET:
			u16Length = 4U;
			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__APU__STATUS_PACKET:

				//top level fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;


				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__APU, C_RLOOP_NET_PORT__APU);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

/***************************************************************************//**
 * @brief
 * Rx a safety udp packet.
 * 
 * @param[in]		u16Fault			Fault types
 * @param[in]		u16DestPort			Target port
 * @param[in]		ePacketType			Packet type
 * @param[in]		u16PayloadLength		Length of payload
 * @param[in]		*pu8Payload			Pointer to payload
 * @st_funcMD5		B80AFD376EA9B85ACF09A7A5C9EEE278
 * @st_funcID		LCCM720R0.FILE.011.FUNC.005
 */
void vAPU_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{
	Luint32 u32Block[4];
	
	if(u16DestPort == C_RLOOP_NET_PORT__APU)
	{
		//split up into easy to use blocks
		u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet
		switch(ePacketType)
		{
			case NET_PKT__APU_CLUTCH__MANUAL:

				//check for the key
				if(u32Block[0] == 0x11223344U)
				{

					if(u32Block[2] == 1U)
					{
						vAPU_CLUTCH__Engage();
					}
					else
					{
						vAPU_CLUTCH__Disengage();
					}

				}
				else
				{
					//todo
					//wrong key
				}
				break;

			case NET_PKT__APU_MOTOR__ENABLE_MANUAL:
				//check for the key
				if(u32Block[0] == 0x11223377U)
				{

					if(u32Block[2] == 1U)
					{
						vAPU_THROTTLE__Enable();
					}
					else
					{
						vAPU_THROTTLE__Disable();
					}

				}
				else
				{
					//todo
					//wrong key
				}
				break;


			case NET_PKT__APU_MOTOR__DIRECTION_MANUAL:
				//check for the key
				if(u32Block[0] == 0x11223388U)
				{
					if(u32Block[2] == 1U)
					{
						vAPU_THROTTLE__Forward();
					}
					else
					{
						vAPU_THROTTLE__Reverse();
					}
				}
				else
				{
					//todo
					//wrong key
				}
				break;

			case NET_PKT__APU_MOTOR__SPEED_MANUAL:
				if(u32Block[0] == 0x11223399U)
				{
					vAPU_THROTTLE__Set_Velocity_mms(u32Block[1]);
				}
				else
				{

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
 * 10ms timer for the ethernet
 * 
 * @st_funcMD5		E5AFAA1E421A61627136E6014A02626F
 * @st_funcID		LCCM720R0.FILE.011.FUNC.007
 */
void vAPU_ETH__10MS_ISR(void)
{
	sAPU.sUDPDiag.u810MS_Flag = 1U;
	sAPU.sUDPDiag.u8250MS_Flag++;
}


#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif

/** @} */
/** @} */
/** @} */

