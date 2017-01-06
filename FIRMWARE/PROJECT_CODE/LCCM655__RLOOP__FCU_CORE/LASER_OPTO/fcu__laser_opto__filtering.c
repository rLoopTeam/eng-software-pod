/**
 * @file		FCU__LASER_OPTO__FILTERING.C
 * @brief		OptoNCDT laser filtering system
 * @author		Lachlan Grogan, Marek Gutt-Mostowy
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

void vFCU_LASEROPTO_FILT__FilterPacket(E_FCU__LASER_OPTO__INDEX_T eLaser)
{

Lfloat32 f32FilterAlpha = 0.008F;
Lfloat32 f32NewSampleInfluence = 0.0F;
Lfloat32 f32OldSampleInfluence = 0.0F
Lfloat32 f32MaxRange = 50.0F;

	//exponential moving average filter

	//reject values above 50 as this is what sensor indicates in case out of range
	if (sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance < f32MaxRange) {

	//  @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer

	//Calculate the old sample influence
	f32NewSampleInfluence = f32FilterAlpha * sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance;
	//Calculatre the new sample influence
	f32OldSampleInfluence = (1 - f32FilterAlpha) * sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue;
	//Update the current value
	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue = f32OldSampleInfluence + f32NewSampleInfluence;

	// Store old sample 
 	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance;
	
	}

	else

	// assign unfiltered value in case it's above 50
	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance;

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
