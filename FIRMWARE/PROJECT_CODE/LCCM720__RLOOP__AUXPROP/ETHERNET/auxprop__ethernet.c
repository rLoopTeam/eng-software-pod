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

/***************************************************************************//**
 * @brief
 * Init the enthernet
 * 
 * @st_funcMD5		B5DD5E3BC7F927B6202535D7DFBF6EEB
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
 * @st_funcMD5		83DB00DD8C46F5A1B6E271D4B7B93B65
 * @st_funcID		LCCM720R0.FILE.011.FUNC.002
 */
void vAPU_ETH__Process(void)
{
	Luint8 u8Test;

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vSIL3_ETH__Process();

	u8Test = u8APU_ETH__Is_LinkUp();
	if(u8Test == 1U)
	{

		//process anything that needs to be transmitted


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
 * Rx a safety udp packet.
 * 
 * @param[in]		u16Fault			Fault types
 * @param[in]		u16DestPort			Target port
 * @param[in]		ePacketType			Packet type
 * @param[in]		u16PayloadLength		Length of payload
 * @param[in]		*pu8Payload			Pointer to payload
 * @st_funcMD5		EDF79701C7EB5FCD738F880E00FCB4D7
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

					//determine the side
					switch((TE_RLOOP_AUXPROP__SIDE)u32Block[1])
					{
						case AUXPROP_SIDE__LEFT:

							//engage if 1, else all other cases are disengage
							if(u32Block[2] == 1U)
							{
								vAPU_CLUTCH__Engage(AUXPROP_SIDE__LEFT);
							}
							else
							{
								vAPU_CLUTCH__Disengage(AUXPROP_SIDE__LEFT);
							}
							break;

						case AUXPROP_SIDE__RIGHT:
							//engage if 1, else all other cases are disengage
							if(u32Block[2] == 1U)
							{
								vAPU_CLUTCH__Engage(AUXPROP_SIDE__RIGHT);
							}
							else
							{
								vAPU_CLUTCH__Disengage(AUXPROP_SIDE__RIGHT);
							}
							break;

						default:
							//not for us
							break;
					}//switch((TE_RLOOP_AUXPROP__SIDE)u32Block[1])
				}
				else
				{
					//todo
					//wrong key
				}
				break;


			case NET_PKT__APU_MOTOR__DIRECTION_MANUAL:
				//check for the key
				if(u32Block[0] == 0x11223377U)
				{

					//determine the side
					switch((TE_RLOOP_AUXPROP__SIDE)u32Block[1])
					{
						case AUXPROP_SIDE__LEFT:

							//engage if 1, else all other cases are disengage
							if(u32Block[2] == 1U)
							{
								vAPU_THROTTLE__Forward(AUXPROP_SIDE__LEFT);
							}
							else
							{
								vAPU_THROTTLE__Reverse(AUXPROP_SIDE__LEFT);
							}
							break;

						case AUXPROP_SIDE__RIGHT:
							//engage if 1, else all other cases are disengage
							if(u32Block[2] == 1U)
							{
								vAPU_THROTTLE__Forward(AUXPROP_SIDE__RIGHT);
							}
							else
							{
								vAPU_THROTTLE__Reverse(AUXPROP_SIDE__RIGHT);
							}
							break;

						default:
							//not for us
							break;
					}//switch((TE_RLOOP_AUXPROP__SIDE)u32Block[1])
				}
				else
				{
					//todo
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


#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif

/** @} */
/** @} */
/** @} */

