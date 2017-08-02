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
 * @param[in]		u32Freq				PWM freq
 * @param[in]		u8Dir				Direction signal
 * @param[in]		u8Enable			Motor enable signal
 * @param[in]		u8Clutch			Clutch control
 * @st_funcMD5		558BEA73C823A18FDF86C34763726BF4
 * @st_funcID		LCCM720R0.FILE.004.FUNC.002
 */
void vAPU_WIN32__UpdateData(Luint8 u8Clutch, Luint8 u8Dir, Luint8 u8Enable, Luint32 u32Freq)
{
	if(pUpdateDataFunc != 0)
	{
		pUpdateDataFunc(u8Clutch, u8Dir, u8Enable, u32Freq);
	}
}


/***************************************************************************//**
 * @brief
 * Send an update through the callback.
 * 
 * @st_funcMD5		76168547ED18F32F210EA0DD912D00EF
 * @st_funcID		LCCM720R0.FILE.004.FUNC.003
 */
void vAPU_WIN32__Send_Generic_Update(void)
{
	vAPU_WIN32__UpdateData(sAPU.sClutch.u8State,
							   (Luint8)sAPU.sThrottle.eDirection,
							   (Luint8)sAPU.sThrottle.eEnable, 
								sAPU.sThrottle.u32Frequency);
							   
		
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

