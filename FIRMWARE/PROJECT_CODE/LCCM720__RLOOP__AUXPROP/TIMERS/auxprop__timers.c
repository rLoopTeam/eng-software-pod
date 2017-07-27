/**
 * @file		AUXPROP__TIMERS.C
 * @brief		Timer Functions
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.005
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP__TIMERS
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U


/***************************************************************************//**
 * @brief
 * 10ms Interrupt
 * 
 * @st_funcMD5		FB0972FF8C48F231FDDD869643D57A03
 * @st_funcID		LCCM720R0.FILE.005.FUNC.001
 */
void vAPU_TIMERS__10MS_ISR(void)
{
	//Tell eth about it.
	vAPU_ETH__10MS_ISR();
	
}

/***************************************************************************//**
 * @brief
 * 100ms Interrupt
 * 
 * @st_funcMD5		6B5DA6EA0F0F7AD8E97F77B619440054
 * @st_funcID		LCCM720R0.FILE.005.FUNC.002
 */
void vAPU_TIMERS__100MS_ISR(void)
{
	
	
}





#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

