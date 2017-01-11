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
 * @st_funcMD5		CE3CF555446926C5FEC7670E78072FCA
 * @st_funcID		LCCM655R0.FILE.069.FUNC.001
 */
void vFCU_BRAKES_WDT__Init(void)
{

	//SPI3:NCS3
	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3);

}


/***************************************************************************//**
 * @brief
 * Start of the petting process
 * 
 * @st_funcMD5		06EC541EE114671B78787568B6D30E01
 * @st_funcID		LCCM655R0.FILE.069.FUNC.002
 */
void vFCU_BRAKES_WDT__Pet_Start(void)
{

	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3, 0x01U);

}

/***************************************************************************//**
 * @brief
 * End the petting process.
 * 
 * @st_funcMD5		B3C341631B7A1B6B14A4AFCAF4D56A35
 * @st_funcID		LCCM655R0.FILE.069.FUNC.003
 */
void vFCU_BRAKES_WDT__Pet_End(void)
{

	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS3, 0x00U);

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
