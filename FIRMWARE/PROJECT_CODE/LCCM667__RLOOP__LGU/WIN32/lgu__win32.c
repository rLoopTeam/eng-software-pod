/**
 * @file		LGU__WIN32.C
 * @brief		WIN32 emulation layer
 * @author		Lachlan Grogan
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.003
 */

/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup LGU__WIN32
 * @ingroup LGU
 * @{ */
 
 
#include "../lgu.h"
#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#ifdef WIN32
extern TS_LGU__MAIN sLGU;

//Allows us to update the ADC value of the MLP for WIN32 simulation
void vLGU_WIN32__Update_ADC_Value(Luint8 u8Index, Luint16 u16Value)
{
	sLGU.sWin32[u8Index].u16ADCValue = u16Value;
}

void vLGU_WIN32__Update_Limit_Switches(Luint8 u8Index, Luint8 u8ExtendLimit, Luint8 u8RetractLimit)
{

}


#endif //WIN32
#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
