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
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eState = COOLING_STATE__NORMAL;
		sPWRNODE.sCooling.sHoverEngineCoolingSystem[u8Counter].eHoverSolenoidState = POWER_COOLING__HOVER_OFF;
	}
}

void vPWR_COOLING_HOVER__Process(void)
{

}


#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif

