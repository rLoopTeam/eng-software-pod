
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


#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);

}

void vHETHERM_ETH__Process(void)
{
	Luint8 u8Test;

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vSIL3_ETH__Process();

	u8Test = u8HETHERM_ETH__Is_LinkUp();
	if(u8Test == 1U)
	{

		//process anything that needs to be transmitted


	}
	else
	{
		//not ready for ethernet yet
	}
}

Luint8 u8HETHERM_ETH__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}

void vHETHERM_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}

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


#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

