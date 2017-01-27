/*
 * pwr__cooling_hover.c
 *
 *  Created on: Jan 23, 2017
 *      Author: edward.chan
 */

#include "../power_core.h"

extern struct _strPWRNODE sPWRNODE;

#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U

void vPWR_COOLING_HOVER__Init(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_HOVERENG; u8Counter++)
	{
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].f32Temperature = 0.0F;
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__WAITING;
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eHoverSolenoidState = POWER_COOLING__HOVER_OFF;
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count = 0U;
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_STARTCOOLING;
	}
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[0].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE0_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[1].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE1_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[2].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE2_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[3].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE3_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[4].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE4_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[5].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE5_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[6].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE6_N2HET_PIN_NUMBER;
	sPWRNODE.sCooling.sHoverEngineCoolingSystem[7].u8N2HETPinNumber = C_PWRCORE_HOVERENGINE7_N2HET_PIN_NUMBER;

}

void vPWR_COOLING_HOVER__Process(void)
{
	//Cooling System Status
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_HOVERENG; u8Counter++)
	{
		switch(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState)
		{
		case COOLINGSUB_STARTCOOLING:
			switch(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState)
			{
			case COOLING_STATE__WAITING:
				//do nothing
				break;
			case COOLING_STATE__NORMAL:
				//NORMAL COOLING @ Valve duty cycle: 0.5s ON / 1.5 s OFF for T < T warning -> delivered mass flow rate/HE 1-1.5 g/s
				//Turn on for 0.5s/ Turn off at 2s/ Do nothing

				//Set counter
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count = 0U;
				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Transit to next state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__WARNING:
				//WARNING @ Valve duty cycle 1.0 s ON/ 1.0 s OFF for T > T warning -> delivered mass flow rate/HE 2 - 3 g/s
				//Turn on at 1s/ Turn off at 2s/ Do Nothing

				//Set counter
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count = 0U;
				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Transit to next state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__CRITICAL:
				//Valve OPEN completely for T > T critical -> delivered mass flow rate/HE maximum at around 4.5 g/s

				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Transit to next state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__EMERGENCY:
				//TODO ENGINE SHUT DOWN
				//Transit to next state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_WAITING;
				break;
			default:
				//do nothing
				break;

			}
			break; //case: COOLINGSUB_STARTCOOLING
		case COOLINGSUB_WAITING:
			switch(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState)
			{
			case COOLING_STATE__WAITING:
				//do nothing
				break;
			case COOLING_STATE__NORMAL:
				//NORMAL COOLING @ Valve duty cycle: 0.5s ON / 1.5 s OFF for T < T warning -> delivered mass flow rate/HE 1-1.5 g/s
				//Stay on for 0.5s/ Turn off between 0.5s and 2s/ Transit back to cooling state after 2s

				if(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count <  5)
				{
					//Do nothing since solenoid was turned on during last state
				}
				else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count >  5 && sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count < 20)
				{
					//Turn off Solenoid here
					vPWR_COOLING__Solennoid_TurnOff(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8N2HETPinNumber);
				}
				else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count > 20)
				{
					//Transit back to cooling state
					sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_STARTCOOLING;
				}
				else
				{
					//handle fault
				}
				break;
			case COOLING_STATE__WARNING:
				//WARNING @ Valve duty cycle 1.0 s ON/ 1.0 s OFF for T > T warning -> delivered mass flow rate/HE 2 - 3 g/s
				//Stay on for 1s/ Turn off between 1s and 2s/ Transit back to cooling state after 2s

				if(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count <  10)
				{
					//Do nothing since solenoid was turned on during last state
				}
				else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count >  10 && sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count < 20)
				{
					//Turn off Solenoid here
					vPWR_COOLING__Solennoid_TurnOff(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u8N2HETPinNumber);
				}
				else if (sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count > 20)
				{
					//Transit back to cooling state
					sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_STARTCOOLING;
				}
				else
				{
					//handle fault
				}
				break;
			case COOLING_STATE__CRITICAL:
				//Valve OPEN completely for T > T critical -> delivered mass flow rate/HE maximum at around 4.5 g/s
				//Do nothing, solenoid will stay ON

				//Transit back to cooling state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_STARTCOOLING;
				break;
			case COOLING_STATE__EMERGENCY:
				//TODO ENGINE SHUT DOWN

				//Transit back to cooling state
				sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eSubState = COOLINGSUB_STARTCOOLING;
				break;
			default:
				//do nothing
				break;

			}

			break; //case: COOLINGSUB_WAITING
		default:
			//do nothing
			break;
		}

	}



}

//100ms interrupt
void vPWR_COOLING_HOVER__100MS_ISR(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_HOVERENG; u8Counter++)
	{
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].u32100MS_Count++;
	}
}


#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif

