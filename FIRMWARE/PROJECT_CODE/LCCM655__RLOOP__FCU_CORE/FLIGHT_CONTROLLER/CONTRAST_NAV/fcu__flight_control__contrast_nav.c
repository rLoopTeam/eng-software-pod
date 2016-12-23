/**
 * @file		FCU__FLIGHT_CONTROL__CONTRAST_NAV.C
 * @brief		Contrast sensor navigation
 * 				This module is the fusion of all contrast sensor nav theories
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
 * @addtogroup FCU__FLIGHT_CTL__CONSTAST_NAV
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U

//the structure
extern struct _strFCU sFCU;

//init contrast sensor navigation
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		14CBEEAA431417A502AD910A69B1485D
 * @st_funcID		LCCM655R0.FILE.043.FUNC.001
 */
void vFCU_FLIGHTCTL_CONTRASTNAV__Init(void)
{


}

//process nav tasks
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		F684FDABB832922904872564B152B586
 * @st_funcID		LCCM655R0.FILE.043.FUNC.002
 */
void vFCU_FLIGHTCTL_CONTRASTNAV__Process(void)
{

}


//returns our current pod position in mm
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		6D13439034F249C54D595BA6B2528867
 * @st_funcID		LCCM655R0.FILE.043.FUNC.003
 */
Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_Position_mm(void)
{
	return 0;
}

//immediate return of a fault condition in the nav.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		FFDC1C0AEC3456B65DEF4913151FBFAE
 * @st_funcID		LCCM655R0.FILE.043.FUNC.004
 */
Luint8 u8FCU_FLIGHTCTL_CONTRASTNAV__Get_IsFault(void)
{
	return 0;
}

//return the list of fault flag conditions.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		9AA4367164F368C40B7DF9881F7347A7
 * @st_funcID		LCCM655R0.FILE.043.FUNC.005
 */
Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_FaultFlags(void)
{
	return 0;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

