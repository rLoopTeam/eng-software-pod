/**
 * @file		HETHERM__WIN32.C
 * @brief		HE Thermal WIN32 simulation
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.004
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
 * @addtogroup HE_THERM__WIN32
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

//Main structure
extern TS_HET__MAIN sHET;

//update data function
pHETHERM_WIN32__UpdateData_Callback_FuncType pUpdateDataFunc = 0;


/***************************************************************************//**
 * @brief
 * Set the callback
 *
 * @param[in]		pFunc		Pointer to callback
 * @st_funcMD5		C94E225F61F1CE8DCFE5D40F0CE2B374
 * @st_funcID		LCCM721R0.FILE.004.FUNC.001
 */
void vHETHERM_WIN32__SetCallback_UpdateData(pHETHERM_WIN32__UpdateData_Callback_FuncType pFunc)
{
	pUpdateDataFunc = pFunc;
}

/***************************************************************************//**
 * @brief
 * Update the data through the callback
 *
 * @param[in]		u8SolR				Right side solenoid
 * @param[in]		u8SolL				Left side solenoid
 * @st_funcMD5		703DAF7B208211B4A9935C7D26ED708F
 * @st_funcID		LCCM721R0.FILE.004.FUNC.002
 */
void vHETHERM_WIN32__UpdateData(Luint8 u8SolL, Luint8 u8SolR)
{
	if(pUpdateDataFunc != 0)
	{
		pUpdateDataFunc(u8SolL, u8SolR);
	}
}


#endif //WIN32
#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

