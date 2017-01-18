/**
 * @file		POWER_CORE__DC_CONVERTER.C
 * @brief		Fault handing subsystem
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
 * @addtogroup POWER_NODE__DC_CONVERTER
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U

extern struct _strPWRNODE sPWRNODE;

//locals
static void vPWRNODE_DC__Power_Off(void);


/***************************************************************************//**
 * @brief
 * Init the DC/DC Converter system
 * 
 * @st_funcMD5		620C799234B5B3567ADDF656945DDB19
 * @st_funcID		LCCM653R0.FILE.021.FUNC.001
 */
void vPWRNODE_DC__Init(void)
{

	//configure our states
	sPWRNODE.sDC.eState = DC_STATE__RESET;
	sPWRNODE.sDC.u8Unlock = 0U;
	sPWRNODE.sDC.u8PodSafeCommand = 0U;
	sPWRNODE.sDC.u8100MS_Tick = 0U;
	sPWRNODE.sDC.u32100MS_TimerCount = 0U;

#ifndef WIN32
	//Setup the hardware pins (DC_WATCHDOG Signal)
	//GPIOA0
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 0U, GIO_DIRECTION__OUTPUT);

	//set to OFF
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);
#endif
}

/***************************************************************************//**
 * @brief
 * Process the DC/DC converter control
 * 
 * @st_funcMD5		0EFE25E73A8AE12AE86AD3975F0A8D52
 * @st_funcID		LCCM653R0.FILE.021.FUNC.002
 */
void vPWRNODE_DC__Process(void)
{
	//todo, process the watchdog, etc.

	switch(sPWRNODE.sDC.eState)
	{

		case DC_STATE__RESET:
			//just come out of reset


			break;

		case DC_STATE__LATCH_COMMAND:
			// we must not do anything yet until the GS has latched us

			//now we can set to on
			vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 1U);

			sPWRNODE.sDC.eState = DC_STATE__CHECK_WDT_PET;
			break;

		case DC_STATE__CHECK_WDT_PET:
			//do we need to pet the WDT in its current window?

			//check if we need to safe the pod.
			sPWRNODE.sDC.eState = DC_STATE__CHECK_POD_SAFE;
			break;

		case DC_STATE__CHECK_POD_SAFE:
			//do we need to implement the Pod safe command?
			if((sPWRNODE.sDC.u8Unlock == 1U) && (sPWRNODE.sDC.u8PodSafeCommand == 1U))
			{
				//kill the power immediate
				//no going back now
				vPWRNODE_DC__Power_Off();

				//stay here until powered off
			}
			else
			{
				//move state
				sPWRNODE.sDC.eState = DC_STATE__CHECK_WDT_TIMER;
			}
			break;

		case DC_STATE__CHECK_WDT_TIMER:

			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER__HEART_TIMEOUT == 1U
				//check if we have seen the flag
				if(sPWRNODE.sDC.u8100MS_Tick == 1U)
				{

					//clear the timer tick for next time
					sPWRNODE.sDC.u8100MS_Tick = 0U;

					//inc the counter
					sPWRNODE.sDC.u32100MS_TimerCount++;

					//check if the counter is greater than our required time.
					if(sPWRNODE.sDC.u32100MS_TimerCount > C_LOCALDEF__LCCM653__DC_CONVERTER__HEART_TIMER_MAX)
					{
						//if so kill the power
						vPWRNODE_DC__Power_Off();
					}
					else
					{
						//less than our timeout, keep going
					}

				}
				else
				{
					// do nothing.
				}
			#else
				//fall on
			#endif
			//loop back around
			sPWRNODE.sDC.eState = DC_STATE__CHECK_WDT_PET;
			break;


		default:
			//do nothing.
			break;

	}//switch(sPWRNODE.sDC.eState)

}

void vPWRNODE_DC__Latch(Luint32 u32Key)
{

	if(u32Key == 0xABAB1122U)
	{
		if(sPWRNODE.sDC.eState == DC_STATE__RESET)
		{
			sPWRNODE.sDC.eState = DC_STATE__LATCH_COMMAND;
		}
		else
		{
			//wrong state, don't latch
		}
	}
	else
	{
		//wrong key
	}

}

/***************************************************************************//**
 * @brief
 * To implement pod safe, first we need to unlock the function with a separate command
 * This will provent spurious safes.
 *
 * @param[in]		u32UnlockKey			The key, should be ABCD1298
 * @st_funcMD5		13855F3831AD134B745053EB8442E3B7
 * @st_funcID		LCCM653R0.FILE.021.FUNC.003
 */
void vPWRNODE_DC__Pod_Safe_Unlock(Luint32 u32UnlockKey)
{
	if(u32UnlockKey == 0xABCD1298U)
	{
		//OK to unlock
		sPWRNODE.sDC.u8Unlock = 1U;
	}
	else
	{
		//error, wrong unlock command

		//hold unlock key off
		sPWRNODE.sDC.u8Unlock = 0U;
	}

}

/***************************************************************************//**
 * @brief
 * Pet the DC/DC conveters timeout watchdog based on GS messages.
 *
 * @param[in]		u32Key			0x1234ABCD
 * @st_funcMD5		57D147559750E935DEE4C30BC7AB0CB6
 * @st_funcID		LCCM653R0.FILE.021.FUNC.004
 */
void vPWRNODE_DC__Pet_GS_Message(Luint32 u32Key)
{
	if(u32Key == 0x1234ABCD)
	{
		//reset the timer count
		sPWRNODE.sDC.u32100MS_TimerCount = 0U;
	}
	else
	{
		//do nothing, wrong key
	}
}

/***************************************************************************//**
 * @brief
 * Get the DC/DC converter's timer count
 * 
 * @st_funcMD5		04BE188F4A4B4B9C88B952F3C988059E
 * @st_funcID		LCCM653R0.FILE.021.FUNC.005
 */
Luint32 u32PWRNODE_DC__Get_TimerCount(void)
{
	return sPWRNODE.sDC.u32100MS_TimerCount;
}


/***************************************************************************//**
 * @brief
 * Switch the power off
 * 
 * @st_funcMD5		0B2C9EBE29F946E9B0F7A68EAEA09B99
 * @st_funcID		LCCM653R0.FILE.021.FUNC.006
 */
void vPWRNODE_DC__Power_Off(void)
{
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);
}


/***************************************************************************//**
 * @brief
 * Execute pod safe
 * 
 * @st_funcMD5		DABA4496931CC78AF6D1DAB36C684991
 * @st_funcID		LCCM653R0.FILE.021.FUNC.007
 */
void vPWRNODE_DC__Pod_Safe_Go(void)
{
	sPWRNODE.sDC.u8PodSafeCommand = 1U;
}


/***************************************************************************//**
 * @brief
 * 100ms timer tick
 * 
 * @st_funcMD5		6B09D957DBEA0F8BE72657B22AE106B6
 * @st_funcID		LCCM653R0.FILE.021.FUNC.008
 */
void vPWRNODE_DC__100MS_ISR(void)
{
	//set the flag
	sPWRNODE.sDC.u8100MS_Tick = 1U;
}


//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER__HEART_TIMEOUT
	#error
#endif
#ifndef C_LOCALDEF__LCCM653__DC_CONVERTER__HEART_TIMER_MAX
	#error
#endif

#endif //C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

