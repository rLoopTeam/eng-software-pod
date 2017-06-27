/**
 * @file		AUXPROP__WIN32.C
 * @brief		Win32 Emulation Functions
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.004
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
 * @addtogroup AUXPROP__WIN32
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

//Main structure
extern TS_APU__MAIN sAPU;

//update data function
pAPU_WIN32__UpdateData_Callback_FuncType pUpdateDataFunc = 0;

/***************************************************************************//**
 * @brief
 * Set the callback
 * 
 * @param[in]		pFunc		Pointer to callback
 * @st_funcMD5		C85BC8668B4FF2D57C05E8697E934B67
 * @st_funcID		LCCM720R0.FILE.004.FUNC.001
 */
void vAPU_WIN32__SetCallback_UpdateData(pAPU_WIN32__UpdateData_Callback_FuncType pFunc)
{
	pUpdateDataFunc = pFunc;
}

/***************************************************************************//**
 * @brief
 * Update the data through the callback
 * 
 * @param[in]		u32FreqR			Right side PWM freq
 * @param[in]		u32FreqL			Left side PWM freq
 * @param[in]		u8DirR				Right side Direction signal
 * @param[in]		u8DirL				Left side direction
 * @param[in]		u8ClutchR			Right side clutch control
 * @param[in]		u8ClutchL			Left side clutch control
 * @st_funcMD5		DCA74B27E683ABB72F24A5CD8D2E4813
 * @st_funcID		LCCM720R0.FILE.004.FUNC.002
 */
void vAPU_WIN32__UpdateData(Luint8 u8ClutchL, Luint8 u8ClutchR, Luint8 u8DirL, Luint8 u8DirR, Luint32 u32FreqL, Luint32 u32FreqR)
{
	if(pUpdateDataFunc != 0)
	{
		pUpdateDataFunc(u8ClutchL, u8ClutchR, u8DirL, u8DirR, u32FreqL, u32FreqR);
	}
}


/***************************************************************************//**
 * @brief
 * Send an update through the callback.
 * 
 * @st_funcMD5		35D3131C6555CA55496F75533C7EB769
 * @st_funcID		LCCM720R0.FILE.004.FUNC.003
 */
void vAPU_WIN32__Send_Generic_Update(void)
{
	vAPU_WIN32__UpdateData(sAPU.sClutch[AUXPROP_SIDE__LEFT].u8State,
							   sAPU.sClutch[AUXPROP_SIDE__RIGHT].u8State,
							   sAPU.sThrottle[AUXPROP_SIDE__LEFT].u8Direction, 
							   sAPU.sThrottle[AUXPROP_SIDE__RIGHT].u8Direction, 
							   4, 5);
							   
		
}


#endif //WIN32
#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

