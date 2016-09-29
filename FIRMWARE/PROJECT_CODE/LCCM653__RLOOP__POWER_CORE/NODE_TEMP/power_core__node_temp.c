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

/***************************************************************************//**
 * @brief
 * Init any node temperature based sub systems
 * 
 * @st_funcMD5		A89279621555EEA443A026A35AA628A9
 * @st_funcID		LCCM653R0.FILE.005.FUNC.001
 */
void vPWRNODE_NODETEMP__Init(void)
{

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

}


/***************************************************************************//**
 * @brief
 * Return the most recent node temperature reading in degreesC
 * 
 * @return			The node temperature in DegC
 * @st_funcMD5		C5D2D1750FB5650E4E987E9D4E79D71D
 * @st_funcID		LCCM653R0.FILE.005.FUNC.003
 */
Lfloat32 f32PWRNODE_NODETEMP__Get_Temperature_DegC(void)
{

	return 0.0F;

}




#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

