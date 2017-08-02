/**
 * @file		LGU__TIMERS.C
 * @brief		Timer Functions
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.008
 */



/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup LGU__TIMERS
 * @ingroup LGU
 * @{
*/
#include <LCCM667__RLOOP__LGU/lgu.h>
#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U


/***************************************************************************//**
 * @brief
 * 10ms Interrupt
 * 
 * @st_funcMD5		CA428054251459F03A1D282DC1FC8F41
 * @st_funcID		LCCM667R0.FILE.008.FUNC.001
 */
void vLGU_TIMERS__10MS_ISR(void)
{
	//Tell the ethernet about our tick
	vLGU_ETH__10MS_ISR();
	
}

/***************************************************************************//**
 * @brief
 * 100ms Interrupt
 * 
 * @st_funcMD5		39024340404001C2E5F3176486479F76
 * @st_funcID		LCCM667R0.FILE.008.FUNC.002
 */
void vLGU_TIMERS__100MS_ISR(void)
{
	
	
}


#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

