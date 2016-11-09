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


void vFCU_FAULTS__Init(void)
{
	//init the fault tree module.
	vFAULTTREE__Init(&sFCU.sFaults.sTopLevel);
}



void vFCU_FAULTS__Process(void)
{

	//check the subsystem layers for faults.

	//check the brakes layer




}

//return 1 if we have some sort of a fault, dig into the flags to see what happened
Luint8 u8FCU_FAULTS__Get_IsFault(void)
{
	//return with the fault flag status
	return sFCU.sFaults.sTopLevel.u8FaultFlag;

}


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

