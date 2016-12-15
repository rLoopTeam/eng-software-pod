/**
 * @file		FCU__LASER_CONTRAST.C
 * @brief		Contrast laser interface
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
 * @addtogroup FCU__LASER_CONTRAST
 * @ingroup FCU
 * @{ */


#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

/***************************************************************************//**
 * @brief
 * Init the contrast laser system
 * 
 * @st_funcMD5		C1848D993533270D8CBF0F5AA80195D4
 * @st_funcID		LCCM655R0.FILE.034.FUNC.001
 */
void vFCU_LASERCONT__Init(void)
{

	//at the entry point here the N2HET should have created 3 programs for either
	//edge capture, or HTU.

}

/***************************************************************************//**
 * @brief
 * Process the laser contrast system
 * 
 * @st_funcMD5		08341218BBDD8E9287DAF96DC79A35CD
 * @st_funcID		LCCM655R0.FILE.034.FUNC.002
 */
void vFCU_LASERCONT__Process(void)
{

	//laser contrast will have a few states.
	//we can't really start timing until we are moving.
	//moving should be notified, and confirmed on the first marker.

}

/***************************************************************************//**
 * @brief
 * Interrupt from the RM4 notification system
 * 
 * @param[in]		eLaser		## Desc ##
 * @st_funcMD5		04E149EFEE2CED7AD1BDC4735B418677
 * @st_funcID		LCCM655R0.FILE.034.FUNC.003
 */
void vFCU_LASERCONT__ISR(E_FCU__LASER_CONT_INDEX_T eLaser)
{

}


#endif
