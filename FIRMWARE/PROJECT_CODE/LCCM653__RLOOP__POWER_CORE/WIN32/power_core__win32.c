
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__WIN32
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

extern struct _strPWRNODE sPWRNODE;

//Init anything we need here.
void vPWRNODE_WIN32__Init(void)
{
	sPWRNODE.sWIN32.f32NodeTemperature = 0.0F;
}

//Set the DS18B20 temperature sensor value by an index
void vPWRNODE_WIN32__Set_DS18B20_Temp_ByIndex(Luint32 u32Index, Lfloat32 f32Temperature)
{

}


//Allows us to set the temperature reading from the TSYS01 temp sensor
void vPWRNODE_WIN32__Set_NodeTemperature(Lfloat32 f32Temperature)
{
	sPWRNODE.sWIN32.f32NodeTemperature = f32Temperature;
}


#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

