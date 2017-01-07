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
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Inits the ethernet networking
 * Sets our IP and MAC addresses for this hardware and starts up ethernet
 * 
 * @st_funcMD5		5B484F3455ED00A8B47E5F93BFBEC80E
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
	sFCU.sEthernet.u8MACAddx[5] = 100U;

	//IP
	sFCU.sEthernet.u8IPAddx[0] = 192U;
	sFCU.sEthernet.u8IPAddx[1] = 168U;
#ifdef __LACHLANS__PC__
	sFCU.sEthernet.u8IPAddx[2] = 1U;
#else
	sFCU.sEthernet.u8IPAddx[2] = 0U;
#endif
	sFCU.sEthernet.u8IPAddx[3] = 100U;

	//init our systems
	vFCU_NET_TX__Init();

#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sFCU.sEthernet.u8MACAddx[0], &sFCU.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vETHERNET__Init(&sFCU.sEthernet.u8MACAddx[0], &sFCU.sEthernet.u8IPAddx[0]);

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
 * @st_funcMD5		BBC84C1B1C55F122903F8D7CABFCFD50
 * @st_funcID		LCCM655R0.FILE.016.FUNC.002
 */
void vFCU_NET__Process(void)
{
	Luint8 u8Test;

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vETHERNET__Process();

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
/** @} */
/** @} */
/** @} */

