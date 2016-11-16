/**
 * @file		POWER_CORE__PI_COMMS__MSG.C
 * @brief		Message passing interface
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__PI_COMMS__MSG
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U

extern struct _strPWRNODE sPWRNODE;

//set the unlock key on the pod safe command
//send this first to unlock the pod safe command
void vPWRNODE_PICOMMS_MSG__PodSafe__UnlockKey(Luint32 u32Key)
{
	#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
		vPWRNODE_DC__Pod_Safe_Unlock(u32Key);
	#endif
}


//execute the pod safe command after the key has been entered in a previous message
void vPWRNODE_PICOMMS_MSG__PodSafe__Execute(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
		vPWRNODE_DC__Pod_Safe_Go();
	#endif
}

//returns the counter in 100ms increments for the wdt, up to a max value as
//compiled into hardware
Luint32 u32PWRNODE_PICOMMS_MSG__PodSafe__Get_Watchdog_Value(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
		return u32PWRNODE_DC__Get_TimerCount();
	#else
		return 0;
	#endif
}


//get the most recent temperature in degrees C
Lfloat32 f32PWRNODE_PICOMMS_MSG__NodeTemp__Get_DegC(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
		return f32PWRNODE_NODETEMP__Get_DegC();
	#else
		return 0.0F;
	#endif
}

//return the fault indication status from the node temp sensor
Luint32 u32PWRNODE_PICOMMS_MSG__NodeTemp__Get_FaulFlags(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
		return u32PWRNODE_NODETEMP__Get_FaultFlags();
	#else
		return 0U;
	#endif

}





#endif //C_LOCALDEF__LCCM653__ENABLE_PI_COMMS
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

