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

/***************************************************************************//**
 * @brief
 * Allows us to update the ADC value of the MLP for WIN32 simulation
 * 
 * @param[in]		u16Value			Raw ADC value
 * @param[in]		u8Index				MLP Index
 * @st_funcMD5		B09175E309FF0486A7C33562297A6C7C
 * @st_funcID		LCCM667R0.FILE.003.FUNC.001
 */
void vLGU_WIN32__Update_ADC_Value(Luint8 u8Index, Luint16 u16Value)
{
	sLGU.sWin32[u8Index].u16ADCValue = u16Value;
}

/***************************************************************************//**
 * @brief
 * Updates the limit swtich values
 * 
 * @param[in]		u8RetractLimit			Hit the retract switch?
 * @param[in]		u8ExtendLimit			Hit the extend switch?
 * @param[in]		u8Index					MLP Index
 * @st_funcMD5		B785190C106CB6CCB026AC3C66651A27
 * @st_funcID		LCCM667R0.FILE.003.FUNC.002
 */
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
