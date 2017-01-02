/**
 * @file		FCU__GEOM.C
 * @brief		Geometry Calculations
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
 * @addtogroup FCU__GEOM
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

//http://confluence.rloop.org/display/SD/System+Parameters

//http://confluence.rloop.org/display/SD/2.3.+Determine+Pod+Front+and+Rear+x+Position%2C+Speed+and+Acceleration+in+tube

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_GEOM__Init(void)
{

}



void vFCU_GEOM__Process(void)
{

}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

