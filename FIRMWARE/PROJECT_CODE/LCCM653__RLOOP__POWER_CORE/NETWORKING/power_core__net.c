//networking Rx

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

extern struct _strPWRNODE sPWRNODE;

//inits the ethernet networking
void vPWRNODE_NET__Init(void)
{
	//SIL3 OUID
	sPWRNODE.sEthernet.u8MACAddx[0] = 0x00;
	sPWRNODE.sEthernet.u8MACAddx[1] = 0x26;
	sPWRNODE.sEthernet.u8MACAddx[2] = 0x80;

	//PCB MAC
	sPWRNODE.sEthernet.u8MACAddx[3] = 0x01;
	sPWRNODE.sEthernet.u8MACAddx[4] = 0x00;
	sPWRNODE.sEthernet.u8MACAddx[5] = 0x00;

	//IP
	sPWRNODE.sEthernet.u8IPAddx[0] = 192;
	sPWRNODE.sEthernet.u8IPAddx[1] = 168;
	sPWRNODE.sEthernet.u8IPAddx[2] = 0;
	sPWRNODE.sEthernet.u8IPAddx[3] = 110;

#ifndef WIN32
	//init the EMAC via its link setup routine.
	vRM4_EMAC_LINK__Init(&sPWRNODE.sEthernet.u8MACAddx[0], &sPWRNODE.sEthernet.u8IPAddx[0]);
#endif

	//init the ethernet layer
	vETHERNET__Init(&sPWRNODE.sEthernet.u8MACAddx[0], &sPWRNODE.sEthernet.u8IPAddx[0]);

}

/***************************************************************************//**
 * @brief
 * Process the EMAC link
 *
 * @note
 * This should be called from main program loop after power is stable
 * This also calls the EMAC link state machine which processes the EMAC link
 * and handles bringing the EMAC on line.
 */
void vPWRNODE_NET__Process(void)
{
#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vETHERNET__Process();
}

/***************************************************************************//**
 * @brief
 * Is the EMAC link up
 *
 * @return 			0 = link down\n
 * 					1 = link up.
 */
Luint8 u8PWRNODE_NET__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
