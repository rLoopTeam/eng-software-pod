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
 * @st_funcMD5		315FD5AA53A663D44B912BC2D889CAFE
 * @st_funcID		LCCM655R0.FILE.022.FUNC.001
 */
void vFCU_FAULTS__Init(void)
{
	//init the fault tree module.
	vSIL3_FAULTTREE__Init(&sFCU.sFaults.sTopLevel);

	//any eth stuff we need
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET_FAULTS == 1U
	vFCU_FAULTS_ETH__Init();
#endif
}



/***************************************************************************//**
 * @brief
 * Process any faults
 * 
 * @st_funcMD5		1D0A75C89FE59DD22542A26E24BDB613
 * @st_funcID		LCCM655R0.FILE.022.FUNC.002
 */
void vFCU_FAULTS__Process(void)
{

	//check the subsystem layers for faults.

	//accel subsystem
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
	if(sFCU.sAccel.sFaultFlags.u8FaultFlag == 1U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__00);
	}
	else
	{
		//fall on
	}
#endif

	//ASI Subsystem
	#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
	if(sFCU.sASI.sFaultFlags.u8FaultFlag == 1U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}
	#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE

	//brakes
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
	if(sFCU.sBrakesGlobal.sFaultFlags.u8FaultFlag == 1U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__02);
	}
	else
	{
		//fall on
	}
#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES

	//daq
	if(0)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__03);
	}
	else
	{
		//fall on
	}

	//flight controller
	if(0)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__04);
	}
	else
	{
		//fall on
	}

	//laser contrast

	//laser distance
	#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
	if(sFCU.sLaserDist.sFaultFlags.u8FaultFlag == 1U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__FAULTS__FAULT_INDEX__06);
	}
	else
	{
		//fall on
	}
	#endif

	//laser optoNCDT

	//networking

	//pusher

	//throttle

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

