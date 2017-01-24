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
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLING_STATE__WAITING;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__EDDY_OFF;
	}

}

void vPWR_COOLING_EDDY__Process(void)
{
	//Cooling System Status
	Luint8 u8Counter;

	/**
	 * There are two steppers motors
	 * To get any idea of the cooling of the brake stepper motors we really need to have some data on temperature of them in a vacuum during holding with the controllers we have.
	 * If no data, it is a wild guess and either an extreme waste of CO2 which may compromise the HE's or burning up the steppers.
	 * The steppers are fully enclosed motors so the only real thing that can be done is to cool the outside frame, which has the circuit board mounted just above it.
	 * If we just spray dry ice on the stepper, the circuit board will likely drop to -80 deg C in a short time when we are stopped due to dry ice covering the circuit board

	 * If NO TEST WILL BE DONE IN VACUUM
	 * Lets use the same values as the HE's CO2 duty cycle and cutoff.
	 */
	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_EDDYBRAKES; u8Counter++)
	{
		switch(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState)
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
			//TODO Need to confirm the action is to APPLY BRAKES?
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

