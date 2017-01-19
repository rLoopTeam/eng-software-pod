/**
 * @file		SIM_HYPERLOOP.C
 * @brief		Main Hyperloop simulation file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM666R0.FILE.000
 */
/**
 * @addtogroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP
 * @ingroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP__CORE
 * @ingroup HYPERLOOP
 * @{ */

#include "sim_hyperloop.h"
#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U

struct _strSIMHLOOP sSH;

/***************************************************************************//**
 * @brief
 * Init the hyperloop simulation
 * 
 * @st_funcMD5		2388B5E66EC14301E85A04442BDDFC37
 * @st_funcID		LCCM666R0.FILE.000.FUNC.001
 */
void vSIMHLOOP__Init(void)
{
	Luint32 u32Counter;


	sSH.sControl.u8RunStatus = 0U;

	//init the hardware level
	vSIMHLOOP_LOWLEVEL__Init();

	#if C_LOCALDEF__LCCM666__ENABLE_ETHERNET == 1U
		vSIMHLOOP_ETH__Init();
	#endif

	//set the accel to allow us to capture 10ms of timing on modelsim
	//this means to hit the first optical marker, we need to cover 30.5m in 0.01s
	//g = 62,244.89G
	vSIMHLOOP_LOWLEVEL__Set_Accel_GForce(200.0); //62244.89796F);

	//for this example we have a veloc of 61x10^9)
	//and we would want to change to coast mode AFTER we have passed the second marker.
	vSIMHLOOP_LOWLEVEL__Set_Max_Veloc(71/*61*/);

	//start
#ifdef __SIM__MODELSIM__
		vSIMHLOOP_LOWLEVEL__Run_On();
#endif

}


/***************************************************************************//**
 * @brief
 * Main process loop
 * 
 * @st_funcMD5		87761DE09C090D1B37343156F9916800
 * @st_funcID		LCCM666R0.FILE.000.FUNC.002
 */
void vSIMHLOOP__Process(void)
{

	#if C_LOCALDEF__LCCM666__ENABLE_ETHERNET == 1U
		vSIMHLOOP_ETH__Process();
	#endif

}


void vSIMHLOOP__100MS_Timer(void)
{
	sSH.sEthernet.u8TimerFlag = 1U;
}



#endif //#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

