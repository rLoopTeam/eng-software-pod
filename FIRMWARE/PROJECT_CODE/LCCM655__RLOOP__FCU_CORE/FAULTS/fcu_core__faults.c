/**
 * @file		FCU_CORE__FAULTS.C
 * @brief		Fault handing interface.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU_CORE__FAULTS
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init the fault processing system
 * 
 * @st_funcMD5		A90C065A837545DA2DDABFF3642666D9
 * @st_funcID		LCCM655R0.FILE.022.FUNC.001
 */
void vFCU_FAULTS__Init(void)
{
	//init the fault tree module.
	vFAULTTREE__Init(&sFCU.sFaults.sTopLevel);

	//accel subsystem
	vFAULTTREE__Init(&sFCU.sFaults.sAccel);

}



/***************************************************************************//**
 * @brief
 * Process any faults
 * 
 * @st_funcMD5		FEA2B8A4105CFE7859CE5B11B1A35CDD
 * @st_funcID		LCCM655R0.FILE.022.FUNC.002
 */
void vFCU_FAULTS__Process(void)
{

	//check the subsystem layers for faults.

	//check the brakes layer




}

/***************************************************************************//**
 * @brief
 * return 1 if we have some sort of a fault, dig into the flags to see what happened
 * 
 * @st_funcMD5		646024F18B39EE4EB1A7E44000184D1B
 * @st_funcID		LCCM655R0.FILE.022.FUNC.003
 */
Luint8 u8FCU_FAULTS__Get_IsFault(void)
{
	//return with the fault flag status
	return sFCU.sFaults.sTopLevel.u8FaultFlag;

}


/***************************************************************************//**
 * @brief
 * Return the top level fault flags.
 * 
 * @st_funcMD5		C6B448B0CA30A17A3C405BB7FEE3C440
 * @st_funcID		LCCM655R0.FILE.022.FUNC.004
 */
Luint32 u32FCU_FAULTS__Get_FaultFlags(void)
{
	return sFCU.sFaults.sTopLevel.u32Flags[0];
}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

