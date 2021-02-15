/**
 * @file		FCU__LASER_OPTO__FILTERING.C
 * @brief		OptoNCDT laser moving average filtering system
 * @author		Lachlan Grogan, Dean Skoien
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
 * @addtogroup FCU__LASER_OPTO__FILTERING
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_LASEROPTO_FILT__Init(void){
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++){
		sFCU.sLaserOpto.sOptoLaser[u8Counter].sCounters.u8AverageCounter = 0U;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].sCounters.u8AverageCounter_wait = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Apply the laser opto filter
 * 
 * @param[in]		eLaser					The laser index
 * @st_funcMD5		CA2906F50517238CB2385ABEEB847776
 * @st_funcID		LCCM655R0.FILE.057.FUNC.001
 */
void vFCU_LASEROPTO_FILT__FilterPacket(E_FCU__LASER_OPTO__INDEX_T eLaser)
{

	//update
	sFCU.sLaserOpto.sOptoLaser[eLaser].f32PrevDistances_mm[sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter] = sFCU.sLaserOpto.sOptoLaser[eLaser].f32DistanceRAW;

	if(sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter_wait == 9U){
		//enough measurements taken, calculate moving average of distance
		Luint8 u8Counter;
		Lfloat32 f32AvgTemp;
		f32AvgTemp = 0U;
		for(u8Counter = 0U; u8Counter < C_FCU__OPTO_FILTER_WINDOW; u8Counter++){
			f32AvgTemp += sFCU.sLaserOpto.sOptoLaser[eLaser].f32PrevDistances_mm[u8Counter];
			f32AvgTemp /= C_FCU__OPTO_FILTER_WINDOW;
		}

		//done calculating moving average, store it
		sFCU.sLaserOpto.sOptoLaser[eLaser].f32FilteredValue_mm = f32AvgTemp;

	}
	else{
		// need at least ten measurements to compute the moving average, increment waiting counter
		sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter_wait++;
	}

	//increment counter for next data point
	sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter++; 
	if(sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter == 10U){
		sFCU.sLaserOpto.sOptoLaser[eLaser].sCounters.u8AverageCounter = 0U;
	}

}

#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
