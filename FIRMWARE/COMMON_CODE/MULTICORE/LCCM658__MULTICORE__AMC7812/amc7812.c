/**
 * @file		AMC7812.C
 * @brief		MAC7812 Core Layer
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__CORE
 * @ingroup AMC7812
 * @{ */

#include "amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * Init the core module
 * 
 * @st_funcMD5		ED56D8E9A5830A1D90727FF6BB2FB08D
 * @st_funcID		LCCM658R0.FILE.000.FUNC.001
 */
void vAMC7812__Init(void)
{
	//init lowlevel
	vAMC7812_LOWLEVEL__Init();
	
	//init I2C
	vAMC7812_I2C__Init();
	
	//Setup any GPIO
	vAMC7812_GPIO__Init();
	
	//setup the DAC
	vAMC7812_DAC__Init();
	
	//Setup the ADC
	vAMC7812_ADC__Init();
	

}

/***************************************************************************//**
 * @brief
 * Process any core tasks.
 * 
 * @st_funcMD5		96394E4CC69E197E228D42A9743AF8BC
 * @st_funcID		LCCM658R0.FILE.000.FUNC.002
 */
void vAMC7812__Process(void)
{


}


#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

