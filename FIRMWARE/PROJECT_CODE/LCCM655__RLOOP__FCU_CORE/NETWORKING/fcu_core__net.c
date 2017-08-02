/**
 * @file		FCU_CORE__NET.C
 * @brief		Netoworking Module
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
 * @addtogroup FCU__CORE_NET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Inits the ethernet networking
 * Sets our IP and MAC addresses for this hardware and starts up ethernet
 * 
 * @st_funcMD5		13A035336C96D72DBAFD7A5F41412935
 * @st_funcID		LCCM655R0.FILE.016.FUNC.001
 */
void vFCU_NET__Init(void)
{
	//SIL3 OUID
	sFCU.sEthernet.u8MACAddx[0] = 0x00U;
	sFCU.sEthernet.u8MACAddx[1] = 0x26U;
	sFCU.sEthernet.u8MACAddx[2] = 0x80U;

	//PCB MAC
	sFCU.sEthernet.u8MACAddx[3] = 0x01U;
	sFCU.sEthernet.u8MACAddx[4] = 0x00U;
	sFCU.sEthernet.u8MACAddx[5] = C_RLOOP_NET_IP__FCU;

	//IP
	sFCU.sEthernet.u8IPAddx[0] = 192U;
	sFCU.sEthernet.u8IPAddx[1] = 168U;
	sFCU.sEthernet.u8IPAddx[2] = C_RLOOP_NET_IP__SUBNET;
	sFCU.sEthernet.u8IPAddx[3] = C_RLOOP_NET_IP__FCU;

	//init the safety UDP layer
	vSIL3_SAFEUDP__Init();

	//init our systems
	vFCU_NET_TX__Init();


#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sFCU.sEthernet.u8MACAddx[0], &sFCU.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vSIL3_ETH__Init(&sFCU.sEthernet.u8MACAddx[0], &sFCU.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * Process the EMAC link
 *
 * @note
 * This should be called from main program loop after power is stable
 * This also calls the EMAC link state machine which processes the EMAC link
 * and handles bringing the EMAC on line.
 * 
 * @st_funcMD5		7B2AF3925C7CFC0E6ABD265C1AAC7F6B
 * @st_funcID		LCCM655R0.FILE.016.FUNC.002
 */
void vFCU_NET__Process(void)
{
	Luint8 u8Test;

	//process any safety UDP items
	vSIL3_SAFEUDP__Process();

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vSIL3_ETH__Process();

	u8Test = u8FCU_NET__Is_LinkUp();
	if(u8Test == 1U)
	{

		//process anything that needs to be transmitted
		vFCU_NET_TX__Process();

	}
	else
	{
		//not ready for ethernet yet
	}



}


/***************************************************************************//**
 * Is the EMAC link up
 *
 * @return 			0 = link down\n
 * 					1 = link up.
 * @st_funcMD5		7992142A1C21AA07872803587554E851
 * @st_funcID		LCCM655R0.FILE.016.FUNC.003
 */
Luint8 u8FCU_NET__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}

//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#ifndef C_LOCALDEF__LCCM655__ENABLE_ETHERNET
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
/** @} */
/** @} */
/** @} */

