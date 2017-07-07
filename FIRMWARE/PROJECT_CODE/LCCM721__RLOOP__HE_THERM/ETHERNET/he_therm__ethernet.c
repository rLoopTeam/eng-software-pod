/**
 * @file		HE_THERM__ETHERNET.C
 * @brief		
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM721R0.FILE.008
 */
/**
 * @addtogroup PROJECT_NAME
 * @{
 */
/**
 * @addtogroup PROJECT_NAME
 * @ingroup MODULE_NAME
 * @{
 */
/**
 * @addtogroup MODULE_NAME__CORE
 * @ingroup MODULE_NAME
 * @{
 */
/** @} */
/** @} */
/** @} */


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

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		3FC6307551D9D631FCEC483FB3FEA72D
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


#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sHET.sEthernet.u8MACAddx[0], &sHET.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		365DC081E00133EE258F04C1335A9801
 * @st_funcID		LCCM721R0.FILE.008.FUNC.002
 */
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

/***************************************************************************//**
 * @brief
 * ToDo
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
 * ToDo
 * 
 * @param[in]		Luint16		## Desc ##
 * @param[in]		Luint16		## Desc ##
 * @param[in]		*pu8Buffer		## Desc ##
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
 * ToDo
 * 
 * @param[in]		Luint16		## Desc ##
 * @param[in]		Luint16		## Desc ##
 * @param[in]		Luint16		## Desc ##
 * @param[in]		Luint16		## Desc ##
 * @param[in]		*pu8Payload		## Desc ##
 * @st_funcMD5		B4986282DECA2553370B69F1F283CA82
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

