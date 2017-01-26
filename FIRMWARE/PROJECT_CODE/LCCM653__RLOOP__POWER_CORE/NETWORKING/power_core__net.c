/**
 * @file		POWER_CORE__NET.C
 * @brief		Power Networking
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__NETWORK
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

extern struct _strPWRNODE sPWRNODE;


/***************************************************************************//**
 * @brief
 * inits the ethernet networking
 * 
 * @st_funcMD5		18E86E7F8D41B538C27751E8FD3A806B
 * @st_funcID		LCCM653R0.FILE.017.FUNC.001
 */
void vPWRNODE_NET__Init(void)
{

	sPWRNODE.sEthernet.u810MS_Timer = 0U;
	sPWRNODE.sEthernet.eMainState = NET_STATE__IDLE;

	//SIL3 OUID
	sPWRNODE.sEthernet.u8MACAddx[0] = 0x00;
	sPWRNODE.sEthernet.u8MACAddx[1] = 0x26;
	sPWRNODE.sEthernet.u8MACAddx[2] = 0x80;

	//PCB MAC
	sPWRNODE.sEthernet.u8MACAddx[3] = 0x01;
	sPWRNODE.sEthernet.u8MACAddx[4] = 0x00;
	if(sPWRNODE.ePersonality == PWRNODE_TYPE__PACK_A)
	{
		sPWRNODE.sEthernet.u8MACAddx[5] = 1U;
	}
	else
	{
		sPWRNODE.sEthernet.u8MACAddx[5] = 2U;
	}

	//IP
	sPWRNODE.sEthernet.u8IPAddx[0] = 192;
	sPWRNODE.sEthernet.u8IPAddx[1] = 168;
	sPWRNODE.sEthernet.u8IPAddx[2] = 0;
	if(sPWRNODE.ePersonality == PWRNODE_TYPE__PACK_A)
	{
		sPWRNODE.sEthernet.u8IPAddx[3] = 110;
	}
	else
	{
		sPWRNODE.sEthernet.u8IPAddx[3] = 111;
	}

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
 * 
 * @st_funcMD5		AE749014AEE93F473972E0F6DDFC391C
 * @st_funcID		LCCM653R0.FILE.017.FUNC.002
 */
void vPWRNODE_NET__Process(void)
{
	Luint8 u8Test;

#ifndef WIN32
	//constantly process the EMAC link as it will take some time to get operational
	vRM4_EMAC_LINK__Process();
#endif

	//process the ethernet layer.
	vETHERNET__Process();


	//hande our state machine for Tx
	switch(sPWRNODE.sEthernet.eMainState)
	{
		case NET_STATE__IDLE:

			sPWRNODE.sEthernet.eMainState = NET_STATE__WAIT_LINK;
			break;

		case NET_STATE__WAIT_LINK:
			u8Test = u8PWRNODE_NET__Is_LinkUp();
			if(u8Test == 1U)
			{

				//link is up
				sPWRNODE.sEthernet.eMainState = NET_STATE__WAIT_TIMER_TICK;
			}
			else
			{

			}

			break;

		case NET_STATE__WAIT_TIMER_TICK:

			if(sPWRNODE.sEthernet.u810MS_Timer == 1U)
			{
				sPWRNODE.sEthernet.eMainState = NET_STATE__RUN;

				sPWRNODE.sEthernet.u810MS_Timer = 0U;
			}
			else
			{

			}

			break;

		case NET_STATE__RUN:

			//do what we need to do

			//wait for the next tick
			sPWRNODE.sEthernet.eMainState = NET_STATE__WAIT_TIMER_TICK;
			break;
		default:
			//fall on
			break;

	}//switch(sPWRNODE.sEthernet.eMainState)


	//process any transmission
	u8Test = u8PWRNODE_NET__Is_LinkUp();
	if(u8Test == 1U)
	{
		vPWRNODE_NET_TX__Process();
	}
	else
	{
		//not ready yet.
	}

}





/***************************************************************************//**
 * @brief
 * Is the EMAC link up
 *
 * @return 			0 = link down\n
 * 					1 = link up.
 * @st_funcMD5		F9B6430A56764B8EFA4ADD7E7755D25E
 * @st_funcID		LCCM653R0.FILE.017.FUNC.003
 */
Luint8 u8PWRNODE_NET__Is_LinkUp(void)
{
#ifndef WIN32
	return u8RM4_EMAC_LINK__Is_LinkUp();
#else
	return 1;
#endif
}


/***************************************************************************//**
 * @brief
 * 10ms ISR from system timer.
 * 
 * @st_funcMD5		19DC91F4363CC4B4FD046C69BB79FBEE
 * @st_funcID		LCCM653R0.FILE.017.FUNC.004
 */
void vPWRNODE_NET__10MS_ISR(void)
{
	sPWRNODE.sEthernet.u810MS_Timer = 1U;

	vPWRNODE_NET_TX__10MS_ISR();
}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */
