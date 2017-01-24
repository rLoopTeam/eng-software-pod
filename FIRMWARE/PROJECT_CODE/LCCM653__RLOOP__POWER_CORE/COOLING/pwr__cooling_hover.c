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
	}
}

void vPWR_COOLING_HOVER__Process(void)
{
	//Cooling System Status
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_HOVERENG; u8Counter++)
	{
		switch(sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState)
		{
		case COOLING_STATE__WAITING:
			//do nothing
			break;
		case COOLING_STATE__NORMAL:
			//NORMAL COOLING @ Valve duty cycle: 0.5s ON / 1.5 s OFF for T < T warning -> delivered mass flow rate/HE 1-1.5 g/s
			break;
		case COOLING_STATE__WARNING:
			//WARNING @ Valve duty cycle 1.0 s ON/ 1.0 s OFF for T > T warning -> delivered mass flow rate/HE 2 - 3 g/s
			break;
		case COOLING_STATE__CRITICAL:
			//Valve OPEN completely for T > T critical -> delivered mass flow rate/HE maximum at around 4.5 g/s
			break;
		case COOLING_STATE__EMERGENCY:
			//ENGINE SHUT DOWN
			break;
		default:
			//do nothing
			break;

		}
	}



}


#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif

