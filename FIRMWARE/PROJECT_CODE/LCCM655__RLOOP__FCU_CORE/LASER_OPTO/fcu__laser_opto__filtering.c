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

Lfloat32 f32FilterAlpha = 0.01F;
Lfloat32 f32NewSampleInfluence = 0.0F;
Lfloat32 f32OldSampleInfluence = 0.0F

	//exponential moving average filter

	//reject current value which differ by more than 5 mm from the previous value
	if abs(sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance - sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue) < 5
	{
	//  @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer

	//Calculate the old sample influence
	f32NewSampleInfluence = f32FilterAlpha * sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32Distance;
	//Calculatre the new sample influence
	f32OldSampleInfluence = (1 - f32FilterAlpha) * sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue;
	//Update the current value
	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue = f32OldSampleInfluence + f32NewSampleInfluence;

	// Remember the current value for next iteration
 	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue;
	
	}

	else
	{
	// set current filtered value to the previous filtered value in case the differential is higher than 5
	sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32PreviousValue;
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
