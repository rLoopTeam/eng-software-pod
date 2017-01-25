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
 * @st_funcMD5		5CF11A5E121D877F3D2EE0529551224C
 * @st_funcID		LCCM655R0.FILE.022.FUNC.001
 */
void vFCU_FAULTS__Init(void)
{
	//init the fault tree module.
	vFAULTTREE__Init(&sFCU.sFaults.sTopLevel);

	//any eth stuff we need
	vFCU_FAULTS_ETH__Init();
}



/***************************************************************************//**
 * @brief
 * Process any faults
 * 
 * @st_funcMD5		BF2420870949587CB67641D07D3954DC
 * @st_funcID		LCCM655R0.FILE.022.FUNC.002
 */
void vFCU_FAULTS__Process(void)
{

	//check the subsystem layers for faults.

	//accel subsystem
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
	if(sFCU.sAccel.sFaultFlags.u8FaultFlag == 1U)
	{
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__00);
	}
	else
	{
		//fall on
	}
#endif

	//ASI Subsystem
	if(sFCU.sASI.sFaultFlags.u8FaultFlag == 1U)
	{
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}

	//brakes
	if(sFCU.sBrakesGlobal.sFaultFlags.u8FaultFlag == 1U)
	{
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__02);
	}
	else
	{
		//fall on
	}

	//daq
	if(0)
	{
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__03);
	}
	else
	{
		//fall on
	}

	//flight controller
	if(0)
	{
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__04);
	}
	else
	{
		//fall on
	}

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

