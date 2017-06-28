
/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__TIMERS
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_HET__MAIN sHET;

/***************************************************************************//**
 * @brief
 * 10ms Interrupt
 * 
 */
void vHETHERM_TIMERS__10MS_ISR(void)
{
	
	
}

/***************************************************************************//**
 * @brief
 * 100ms Interrupt
 */
void vHETHERM_TIMERS__100MS_ISR(void)
{
	
	
}





#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

