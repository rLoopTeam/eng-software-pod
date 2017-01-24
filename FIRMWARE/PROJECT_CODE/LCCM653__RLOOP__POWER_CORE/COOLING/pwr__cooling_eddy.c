/*
 * pwr__cooling_eddy.c
 *
 *  Created on: Jan 23, 2017
 *      Author: edward.chan
 */

#include "../power_core.h"

extern struct _strPWRNODE sPWRNODE;

#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U

void vPWR_COOLING_EDDY__Init(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_EDDYBRAKES; u8Counter++)
	{
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature = 0.0F;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__NORMAL;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__EDDY_OFF;
	}

}

void vPWR_COOLING_EDDY__Process(void)
{

}
#endif //C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
#ifndef C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS
	#error
#endif

