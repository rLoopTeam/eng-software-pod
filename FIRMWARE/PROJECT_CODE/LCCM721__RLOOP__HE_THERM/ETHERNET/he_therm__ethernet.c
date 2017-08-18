/**
 * @file		HE_THERM__ETHERNET.C
 * @brief		Ethernet Interface
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.008
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__ETHERNET
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_HET__MAIN sHET;

//locals
void vHETHERM_ETH__Transmit(E_NET__PACKET_T ePacketType);

/***************************************************************************//**
 * @brief
 * Configure the ethernet
 * 
 * @st_funcMD5		356CC0ED787767665FCA45C57EA6C650
 * @st_funcID		LCCM721R0.FILE.008.FUNC.001
 */
void vHETHERM_ETH__Init(void)
{
	//SIL3 OUID
	sHET.sEthernet.u8MACAddx[0] = 0x00U;
	sHET.sEthernet.u8MACAddx[1] = 0x26U;
	sHET.sEthernet.u8MACAddx[2] = 0x80U;

	//PCB MAC
	sHET.sEthernet.u8MACAddx[3] = 0x01U;
	sHET.sEthernet.u8MACAddx[4] = 0x00U;
	sHET.sEthernet.u8MACAddx[5] = C_RLOOP_NET_IP__HETHERM;

	//IP
	sHET.sEthernet.u8IPAddx[0] = 192U;
	sHET.sEthernet.u8IPAddx[1] = 168U;
	sHET.sEthernet.u8IPAddx[2] = C_RLOOP_NET_IP__SUBNET;
	sHET.sEthernet.u8IPAddx[3] = C_RLOOP_NET_IP__HETHERM;

	sHET.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
	sHET.sUDPDiag.u81000MS_Flag = 0U;
	sHET.sUDPDiag.u8500MS_Flag = 0U;
	sHET.sUDPDiag.u8250MS_Flag = 0U;
	sHET.sUDPDiag.u810MS_Flag = 0U;

#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * Process any ethernet tasks
 * 
 * @st_funcMD5		A84E095D906D5A68D00AB43BCE650174
 * @st_funcID		LCCM721R0.FILE.008.FUNC.002
 */
void vHETHERM_ETH__Process(void)
{
	Luint8 u8Test;
	// Luint8 u8Flag;
	// E_NET__PACKET_T eType;

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vSIL3_ETH__Process();

	u8Test = u8HETHERM_ETH__Is_LinkUp();
	if(u8Test == 1U)
	{

		//every 250ms broadcast our status
		if(sHET.sUDPDiag.u8250MS_Flag > 25U)
		{
			//send the LGU status
			vHETHERM_ETH__Transmit(NET_PKT__HET__SEND_THERM_PACKET);

			//clear now
			sHET.sUDPDiag.u8250MS_Flag = 0U;

		}
		else
		{

			//do we have a timer flag?
			if(sHET.sUDPDiag.u810MS_Flag == 1U)
			{
				if(sHET.sUDPDiag.eTxStreamingType != NET_PKT__NONE)
				{
					//send it
					vHETHERM_ETH__Transmit(sHET.sUDPDiag.eTxStreamingType);

				}
				else
				{
					//no packet type.
				}

				//clear the flag now
				sHET.sUDPDiag.u810MS_Flag = 0U;
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
 * Do we have an ethernet Link?
 * 
 * @st_funcMD5		4474B73CA898BC1EBD8846EDF0AFD603
 * @st_funcID		LCCM721R0.FILE.008.FUNC.003
 */
Luint8 u8HETHERM_ETH__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}

/***************************************************************************//**
 * @brief
 * Transmit an eth packet
 * 
 * @param[in]		ePacketType				Packet type
 * @st_funcMD5		97C946B3B25E3E39512A42F8D3619F4E
 * @st_funcID		LCCM721R0.FILE.008.FUNC.006
 */
void vHETHERM_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 *pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Counter;
	// Luint8 *pu8Temp;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__HET__SEND_THERM_PACKET:
			u16Length = 16U + 4U + 1U + ((4U + 8U) * C_LOCALDEF__LCCM644__MAX_DEVICES) + 6U + 12U + 12U + 3U;
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
			case NET_PKT__HET__SEND_THERM_PACKET:

				//top level fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//Solenoid Faults (should be 0)
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//DS2482:0 Faults
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32DS2482S__Get_FaultFlags(0U));
				pu8Buffer += 4U;

				//DS2482:1 Faults
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32DS2482S__Get_FaultFlags(1U));
				pu8Buffer += 4U;

				//DS18B20 flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				//number of enumerated sensors on the bus
				pu8Buffer[0] = u16DS18B20__Get_NumEnum_Sensors();
				pu8Buffer += 1U;

				//list out all the temperatures up to max 32?
				for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM644__MAX_DEVICES; u8Counter++)
				{

					//send out the temperature
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32DS18B20__Get_Temperature_DegC(u8Counter));
					pu8Buffer += 4U;

					//do the rom ID
					vDS18B20__Get_ROMID(u8Counter, pu8Buffer);
					pu8Buffer += 8U;

				}


				//now do each control side
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sHET.sMotorTemp.sLeftHE.u16HighestSensorIndex);
				pu8Buffer += 2U;
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sHET.sMotorTemp.sRightHE.u16HighestSensorIndex);
				pu8Buffer += 2U;
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sHET.sMotorTemp.sBrakeMotor.u16HighestSensorIndex);
				pu8Buffer += 2U;

				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sLeftHE.f32HighestTemp);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sRightHE.f32HighestTemp);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sBrakeMotor.f32HighestTemp);
				pu8Buffer += 4U;

				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sLeftHE.f32AverageTemp);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sRightHE.f32AverageTemp);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sHET.sMotorTemp.sBrakeMotor.f32AverageTemp);
				pu8Buffer += 4U;

				//overtemp states
				pu8Buffer[0] = sHET.sSol.sLeft.u8ChannelOverTemp_State;
				pu8Buffer[1] = sHET.sSol.sRight.u8ChannelOverTemp_State;
				pu8Buffer[2] = sHET.sSol.sBrake.u8ChannelOverTemp_State;
				pu8Buffer += 3U;

				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__HETHERM, C_RLOOP_NET_PORT__HETHERM);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

/***************************************************************************//**
 * @brief
 * RX a UDP packet from the eth
 * 
 * @param[in]		u16DestPort				Destination port addx.
 * @param[in]		u16Length				Packet Length
 * @param[in]		*pu8Buffer				Pointer to data
 * @st_funcMD5		5141B6243B3AFF96ACBA45D78D544C21
 * @st_funcID		LCCM721R0.FILE.008.FUNC.004
 */
void vHETHERM_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}

/***************************************************************************//**
 * @brief
 * Rx a processed safety UDP packet
 * 
 * @param[in]		u16Fault				Faults during packet processing?
 * @param[in]		u16DestPort				Destination port
 * @param[in]		ePacketType				Type of packet
 * @param[in]		u16PayloadLength		Total payload length
 * @param[in]		*pu8Payload				Pointer to the payload
 * @st_funcMD5		195DB0CCCB84AC31FBE01D64C6E1D265
 * @st_funcID		LCCM721R0.FILE.008.FUNC.005
 */
void vHETHERM_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{
	Luint32 u32Block[4];

	if(u16DestPort == C_RLOOP_NET_PORT__HETHERM)
	{
		//split up into easy to use blocks
		u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet
		switch(ePacketType)
		{

			/** Manual control of the solenoids */
			case NET_PKT__HET__MANUAL_CONTROL:

				//check our key
				if(u32Block[0U] == 0xAA117788U)
				{

					//index
					switch(u32Block[1U])
					{
						case 0U:

							if(u32Block[2U] == 1U)
							{
								vHETHERM_SOL__Open(0U);
							}
							else
							{
								vHETHERM_SOL__Close(0U);
							}

							break;

						case 1U:
							if(u32Block[2U] == 1U)
							{
								vHETHERM_SOL__Open(1U);
							}
							else
							{
								vHETHERM_SOL__Close(1U);
							}
							break;

						case 2U:
							if(u32Block[2U] == 1U)
							{
								vHETHERM_SOL__Open(2U);
							}
							else
							{
								vHETHERM_SOL__Close(2U);
							}
							break;

						case 3U:
							if(u32Block[2U] == 1U)
							{
								vHETHERM_SOL__Open(3U);
							}
							else
							{
								vHETHERM_SOL__Close(3U);
							}
							break;
							
						default:
							//do nothing.
							break;
							
					}//switch(u32Block[1U])
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
 * ToDo
 * 
 * @st_funcMD5		099C8D3267F59EF7222870AFF99AF776
 * @st_funcID		LCCM721R0.FILE.008.FUNC.007
 */
void vHETHERM_ETH__10MS_ISR(void)
{
	sHET.sUDPDiag.u810MS_Flag = 1U;
	sHET.sUDPDiag.u8250MS_Flag++;
	sHET.sUDPDiag.u8500MS_Flag++;
	sHET.sUDPDiag.u81000MS_Flag++;

}

#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

