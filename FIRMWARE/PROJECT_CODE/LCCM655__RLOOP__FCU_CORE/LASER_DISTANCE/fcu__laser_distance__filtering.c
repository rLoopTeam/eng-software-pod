/**
 * @file		FCU__LASER_DISTANCE__FILTERING.C
 * @brief		Forward looking laser distance filter functions
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
 * @st_funcMD5		38C7623C4FC5D0B6B921DD0530075411
 * @st_funcID		LCCM655R0.FILE.059.FUNC.001
 */
void vFCU_LASERDIST_FILT__Init(void)
{
	//init
	//sFCU.sLaserDist.f32DistanceFiltered = 0.0F;
}

/***************************************************************************//**
 * @brief
 * Process the laser distance filtering
 * 
 * @st_funcMD5		92EC61151561130CB9760891453F9F56
 * @st_funcID		LCCM655R0.FILE.059.FUNC.002
 */
void vFCU_LASERDIST_FILT__Process(void)
{

#if 0
	//input value
	//sFCU.sLaserDist.f32DistanceRAW
	Luint32 arraysFCUsLaserDistf32DistanceRAW[10];
	Luint8 u8Counter;

	for (u8Counter = 0; u8Counter < 11; ++u8Counter)
	{
		arraysFCUsLaserDistf32DistanceRAW[u8Counter] = sFCU.sLaserDist.f32DistanceRAW;
		//make sure the next value of the sensor is ready; I am not sure there is a while(flag) in the sampling
	}
	

	//todo: filtering
	//Results: -2.496310179882773e-18; -0.0079; 0.0402; -0.1033; 0.1708; 0.8005; 0.1708; -0.1033; 0.0402; -0.0079; -2.496310179882773e-18;
	//order of the filter = 10; Fsampling = 50 Hz; Transition band = 10 Hz; delay = 0.14 s; FIR;
	//for each output value we should have the last 11 values of the input because of the order of the filter;
	sFCU.sLaserDist.s32Distance_mm = -0.0079 * arraysFCUsLaserDistf32DistanceRAW[9] + 0.0402 * arraysFCUsLaserDistf32DistanceRAW[8] - 0.1033 * arraysFCUsLaserDistf32DistanceRAW[7] + 0.1708 * arraysFCUsLaserDistf32DistanceRAW[6] + 0.8005 * arraysFCUsLaserDistf32DistanceRAW[5] + 0.1708 * arraysFCUsLaserDistf32DistanceRAW[4] - 0.1033 * arraysFCUsLaserDistf32DistanceRAW[3] + 0.0402 * arraysFCUsLaserDistf32DistanceRAW[2] - 0.0079 * arraysFCUsLaserDistf32DistanceRAW[1];

	//output at
	//todo:
	sFCU.sLaserDist.f32DistanceFiltered = sFCU.sLaserDist.s32Distance_mm;

#endif //0

}



#endif
/** @} */
/** @} */
/** @} */

