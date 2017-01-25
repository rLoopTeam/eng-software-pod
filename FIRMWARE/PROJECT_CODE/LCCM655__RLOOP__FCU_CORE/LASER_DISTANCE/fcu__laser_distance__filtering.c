/**
 * @file		FCU__LASER_DISTANCE__FILTERING.C
 * @brief		Forward looking laser distance filter fuinctions
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
 * @addtogroup FCU__LASER_DISTANCE__FILTERING
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init any filtering for laser distance
 * 
 * @st_funcMD5		A9035D9E0A160B126DCF645E6D1D9272
 * @st_funcID		LCCM655R0.FILE.059.FUNC.001
 */
void vFCU_LASERDIST_FILT__Init(void)
{
	//init
	//sFCU.sLaserDist.f32DistanceFiltered = 0.0F;
}

/***************************************************************************//**
 * @brief
 * Process teh laser distance filtering
 * 
 * @st_funcMD5		77401928E10A4DDF6B7AC0FF4CEBFBEF
 * @st_funcID		LCCM655R0.FILE.059.FUNC.002
 */
void vFCU_LASERDIST_FILT__Process(void)
{

	//input value
	//sFCU.sLaserDist.f32DistanceRAW


	//todo: filtering

	//output at
	//todo:
	//sFCU.sLaserDist.f32DistanceFiltered = sFCU.sLaserDist.s32Distance_mm;

}



#endif
/** @} */
/** @} */
/** @} */

