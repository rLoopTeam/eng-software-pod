/**
 * @file		HE_THERM__TIMERS.C
 * @brief		System Timers
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.005
 */

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
 * @st_funcMD5		9194AE58300B8D7BC779D57D78E5810B
 * @st_funcID		LCCM721R0.FILE.005.FUNC.001
 */
void vHETHERM_TIMERS__10MS_ISR(void)
{
	#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 1U
		vDS18B20__10MS_ISR();
	#endif
	
	//handle the timed ethernet process
	vHETHERM_ETH__10MS_ISR();

}


/***************************************************************************//**
 * @brief
 * 100ms Interrupt
 * 
 * @st_funcMD5		F5C37117A8C7616CA55CB884860D0E7D
 * @st_funcID		LCCM721R0.FILE.005.FUNC.002
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

