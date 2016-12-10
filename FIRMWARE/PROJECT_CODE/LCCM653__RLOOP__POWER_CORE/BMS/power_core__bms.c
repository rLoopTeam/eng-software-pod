/**
 * @file		POWER_CORE__BMS.C
 * @brief		Battery Management Interface Layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.008
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BMS
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the battery management system
 * 
 * @st_funcMD5		C25517A5352BBA3E0ADB3482CBDE4749
 * @st_funcID		LCCM653R0.FILE.008.FUNC.001
 */
void vPWRNODE_BMS__Init(void)
{
#ifndef WIN32
	//init the ATA6870 driver
	vATA6870__Init();
#endif

}

/***************************************************************************//**
 * @brief
 * Process any battery management system items
 * 
 * @st_funcMD5		9809D5F9775BE5E5A0B9636137B0DA65
 * @st_funcID		LCCM653R0.FILE.008.FUNC.002
 */
void vPWRNODE_BMS__Process(void)
{
#ifndef WIN32
	//process any ATA6870 tasks
	vATA6870__Process();
#endif
}

#endif //C_LOCALDEF__LCCM653__ENABLE_BMS

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

