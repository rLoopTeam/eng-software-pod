/**
 * @file		POWER_CORE__NODE_TEMP.C
 * @brief		Node temperature interface layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.005
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__NODE_TEMPERATURE
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init any node temperature based sub systems
 * 
 * @st_funcMD5		A89279621555EEA443A026A35AA628A9
 * @st_funcID		LCCM653R0.FILE.005.FUNC.001
 */
void vPWRNODE_NODETEMP__Init(void)
{
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
		// init TSYS01 ambient PV Temperature Sensor
		vTSYS01__Init();
	#endif

}

/***************************************************************************//**
 * @brief
 * Process anything related to the node temperature
 * 
 * @st_funcMD5		F462FB8C7D44A9FA6D84C5E1D66304F1
 * @st_funcID		LCCM653R0.FILE.005.FUNC.002
 */
void vPWRNODE_NODETEMP__Process(void)
{
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
		//process the digital temp sensor
		vTSYS01__Process();
	#endif
}


/***************************************************************************//**
 * @brief
 * Return the most recent node temperature reading in degreesC
 * 
 * @return			The node temperature in DegC
 * @st_funcMD5		C5D2D1750FB5650E4E987E9D4E79D71D
 * @st_funcID		LCCM653R0.FILE.005.FUNC.003
 */
Lfloat32 f32PWRNODE_NODETEMP__Get_DegC(void)
{
	#ifdef WIN32
		return sPWRNODE.sWIN32.f32NodeTemperature;
	#else
		//get from hardware
		return f32TSYS01__Get_TempDegC();
	#endif
}

Luint32 u32PWRNODE_NODETEMP__Get_FaultFlags(void)
{
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
		return u32TSYS01__Get_FaultFlags();
	#else
		return 0xFFFFFFFFU;
	#endif

}

#endif //C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP
#ifndef C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP
	#error
#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

