#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the pressure vessel repress system
 * 
 * @st_funcMD5		DA61463302D1706E2EFE0AD5D80540B0
 * @st_funcID		LCCM653R0.FILE.035.FUNC.001
 */
void vPWR_PVPRESS__Init(void)
{
	//initial state
	sPWRNODE.sRePress.eState = REPRESS_STATE__RESET;
	sPWRNODE.sRePress.u32100MS_Count = 0U;
	sPWRNODE.sRePress.eSolState = REPRESS_SOL_STATE__OFF;
	sPWRNODE.sRePress.f32Press = 0.0F;

	#ifndef WIN32
	#if C_LOCALDEF__BMS_REVISION == 1U
		//configure N2HET PIN
		vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 0U);

		//set its state
		vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, 0U);
	#elif C_LOCALDEF__BMS_REVISION == 2U
		//configure N2HET PIN
		vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 4U);

		//set its state
		vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 4U, 0U);
	#else
		#error
	#endif
	#endif

}

/***************************************************************************//**
 * @brief
 * Process the pv repress system
 * 
 * @st_funcMD5		4BDFBA2F957461A134F3C2F8E3B49BE2
 * @st_funcID		LCCM653R0.FILE.035.FUNC.002
 */
void vPWR_PVPRESS__Process(void)
{
	Luint8 u8Test;

	//main state machine
	switch(sPWRNODE.sRePress.eState)
	{
		case REPRESS_STATE__RESET:
			//do nothing here.
			break;

		case REPRESS_STATE__IDLE:
			//in this state we are only getting to here once we have been enabled
			sPWRNODE.sRePress.eState = REPRESS_STATE__CHECK_PRESS_SNSR;
			break;


		case REPRESS_STATE__CHECK_PRESS_SNSR:

			//check that the pressure sensor is working
#ifndef WIN32
			u8Test = u8MS5607__Get_IsFault();
#else
			u8Test = 0U;
#endif
			if(u8Test == 1U)
			{
				//do not use the sensor, stay here
				sPWRNODE.sRePress.eState = REPRESS_STATE__FAULT;
			}
			else
			{
				//ok use the sensor, all good
				//but we need to make sure we have valid pressure
				sPWRNODE.sRePress.f32Press = f32PWRNODE_NODEPRESS__Get_Pressure_Bar();

				//process our pressure
				sPWRNODE.sRePress.eState = REPRESS_STATE__PROCESS_PRESS;
			}
			break;

		case REPRESS_STATE__PROCESS_PRESS:
			//ok work out what to do:
			if(sPWRNODE.sRePress.f32Press < 0.6F)
			{
				//less than 0.6bar, repress.
				sPWRNODE.sRePress.eSolState = REPRESS_SOL_STATE__ON;
			}
			else
			{
				//above 0.6 bar + hyster, if we are already on then we need off
				if(sPWRNODE.sRePress.f32Press > 0.9F)
				{
					//done off
					sPWRNODE.sRePress.eSolState = REPRESS_SOL_STATE__OFF;
				}
				else
				{
					//keep on
					sPWRNODE.sRePress.eSolState = REPRESS_SOL_STATE__ON;
				}
			}

			//back to idle state
			sPWRNODE.sRePress.eState = REPRESS_STATE__IDLE;
			break;

		case REPRESS_STATE__FAULT:
			//stay here in fault
			sPWRNODE.sRePress.eSolState = REPRESS_SOL_STATE__OFF;
			break;

		default:
			//do nothing.
			break;

	}//switch(sPWRNODE.sRePress.eState)

	//handle the actual solenoid state.
#ifndef WIN32
	#if C_LOCALDEF__BMS_REVISION == 1U
		if(sPWRNODE.sRePress.eSolState == REPRESS_SOL_STATE__OFF)
		{
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, 0U);
		}
		else
		{
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, 1U);
		}
	#elif C_LOCALDEF__BMS_REVISION == 2U
		if(sPWRNODE.sRePress.eSolState == REPRESS_SOL_STATE__OFF)
		{
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 4U, 0U);
		}
		else
		{
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 4U, 1U);
		}
	#else
		#error
	#endif
#else
	//update WIN32
	if (sPWRNODE.sRePress.eSolState == REPRESS_SOL_STATE__OFF)
	{
		sPWRNODE.sWIN32.u8RepressSol = 0U;
	}
	else
	{
		sPWRNODE.sWIN32.u8RepressSol = 1U;
	}
	
#endif
}

/***************************************************************************//**
 * @brief
 * To be called from GS to enable the repress system as its dangerous
 * 
 * @param[in]		u32Value			1 = Enable
 * @st_funcMD5		F3BF77523E1E4FDE210AE4F5C4CAC9E9
 * @st_funcID		LCCM653R0.FILE.035.FUNC.003
 */
void vPWR_PVPRESS__Enable(Luint32 u32Value)
{
	if(u32Value == 1U)
	{
		//go from reset to idle.
		sPWRNODE.sRePress.eState = REPRESS_STATE__IDLE;
	}
	else
	{
		//off
		sPWRNODE.sRePress.eState = REPRESS_STATE__RESET;
	}

}

/***************************************************************************//**
 * @brief
 * 100ms interrupt
 * 
 * @st_funcMD5		1D6024B6A44D7FB132FF6F6F7D4C319A
 * @st_funcID		LCCM653R0.FILE.035.FUNC.004
 */
void vPWR_PVPRESS__100MS_ISR(void)
{
	sPWRNODE.sRePress.u32100MS_Count++;
}


#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif
