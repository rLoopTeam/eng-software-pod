/**
 * @file		FCU__LASER_CONT__TRACK_DATABASE.C
 * @brief		Maintain a track / contrast sensor database
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
 * @addtogroup FCU__LASER_CONTRAST__TRACK_DATABASE
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Create the database
 *
 */
void vFCU_LASERCONT_TRKDB__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Process track database systems
 *
 */
void vFCU_LASERCONT__TRKDB__Process(void)
{

}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
