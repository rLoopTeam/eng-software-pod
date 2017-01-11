/**
 * @file		FCU__BRAKES__WATCHDOG.C
 * @brief		Watchdog
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__BRAKES__WDT
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U


/***************************************************************************//**
 * @brief
 * Init the watchdog pin
 * 
 * @st_funcMD5		C60A4D2832D296DE3D697E6008F6532D
 * @st_funcID		LCCM655R0.FILE.069.FUNC.001
 */
void vFCU_BRAKES_WDT__Init(void)
{
#ifndef WIN32
	//SPI3:NCS3
	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3);
#endif

}


/***************************************************************************//**
 * @brief
 * Start of the petting process
 * 
 * @st_funcMD5		A4903EF69EFB23039E39E2A01AE2604E
 * @st_funcID		LCCM655R0.FILE.069.FUNC.002
 */
void vFCU_BRAKES_WDT__Pet_Start(void)
{
#ifndef WIN32
	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3, 0x01U);
#endif
}

/***************************************************************************//**
 * @brief
 * End the petting process.
 * 
 * @st_funcMD5		2ACFE93C017C08196F693ADB4A665736
 * @st_funcID		LCCM655R0.FILE.069.FUNC.003
 */
void vFCU_BRAKES_WDT__Pet_End(void)
{
#ifndef WIN32
	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3, 0x00U);
#endif
}



#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
