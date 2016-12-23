/**
 * @file		FCU__LASER_CONT__VELOC.C
 * @brief		Velocity Calculator
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
 * @addtogroup FCU__LASER_CONTRAST__VELOC
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;


void vFCU_LASERCONT_VELOC__Init(void)
{

	sFCU.sContrast.sVeloc.u32CurrentVeloc_mms = 0U;;

}



void vFCU_LASERCONT_VELOC__Process(void)
{


}



#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
