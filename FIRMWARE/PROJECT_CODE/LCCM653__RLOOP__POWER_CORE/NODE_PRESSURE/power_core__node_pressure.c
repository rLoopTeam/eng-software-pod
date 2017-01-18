/**
 * @file		POWER_CORE__NODE_PRESSURE.C
 * @brief		Node Baro Pressure Sensor interface layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.006
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__NODE_PRESSURE
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the node pressure layer
 * 
 * @st_funcMD5		431FFDCF30F00FA61A07843EAEF32994
 * @st_funcID		LCCM653R0.FILE.006.FUNC.001
 */
void vPWRNODE_NODEPRESS__Init(void)
{
	#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
		// Init the MS5607 device
		vMS5607__Init();
	#endif
}


/***************************************************************************//**
 * @brief
 * Process the node pressure layer
 * 
 * @st_funcMD5		14FC06472F5A34E8DC409148E0A8E283
 * @st_funcID		LCCM653R0.FILE.006.FUNC.002
 */
void vPWRNODE_NODEPRESS__Process(void)
{
	#if C_LOCALDEF__LCCM648__ENABLE_THIS_MODULE == 1U
		// Process the MS5607 device
		vMS5607__Process();
	#endif

}


/***************************************************************************//**
 * @brief
 * Return the node pressure in Bar
 *
 * @return			The most recent pressure sample.
 * @st_funcMD5		70C54965EA46ECDD79FCC81F477BA2B4
 * @st_funcID		LCCM653R0.FILE.006.FUNC.003
 */
Lfloat32 f32PWRNODE_NODEPRESS__Get_Pressure_Bar(void)
{
	Lfloat32 f32Return;

	//get the pressure in mBar
	f32Return = (Lfloat32)sMS5607__GetPressure();

	//convert to Bar
	f32Return /= 100000.0F;

	return f32Return;

}

#endif //C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

