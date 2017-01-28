/*
 * pwr__cooling_eddy.c
 *
 *  Created on: Jan 23, 2017
 *      Author: edward.chan
 */

#include "../power_core.h"

extern struct _strPWRNODE sPWRNODE;

#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U

void vPWR_COOLING_EDDY__Init(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_EDDYBRAKES; u8Counter++)
	{
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].f32Temperature = 0.0F;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eCoolingState = COOLING_STATE__WAITING;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_OFF;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count = 0U;
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_STARTCOOLING;
	}

	sPWRNODE.sCooling.sEddyBrakeCoolingSystem[0].u8N2HETPinNumber = C_PWRCORE_EDDYBRAKE0_N2HET_PIN_NUMBER;


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
		case COOLINGSUB_STARTCOOLING:
			switch(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eCoolingState)
			{
			case COOLING_STATE__WAITING:
				//do nothing
				break;
			case COOLING_STATE__NORMAL:
				//NORMAL COOLING @ Valve duty cycle: 0.5s ON / 1.5 s OFF for T < T warning -> delivered mass flow rate/HE 1-1.5 g/s
				//Turn on for 0.5s/ Turn off at 2s/ Do nothing

				//Set counter
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count = 0;
				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Update Solenoid State
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_ON;
				//Transit to next state
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__WARNING:
				//WARNING @ Valve duty cycle 1.0 s ON/ 1.0 s OFF for T > T warning -> delivered mass flow rate/HE 2 - 3 g/s
				//Turn on at 1s/ Turn off at 2s/ Do Nothing

				//Set counter
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count = 0;
				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Update Solenoid State
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_ON;
				//Transit to next state
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__CRITICAL:
				//Valve OPEN completely for T > T critical -> delivered mass flow rate/HE maximum at around 4.5 g/s

				//Turn on Solenoid here
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Update Solenoid State
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_ON;
				//Transit to next state
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_WAITING;
				break;
			case COOLING_STATE__EMERGENCY:
				//TODO ENGINE SHUT DOWN instead of cooling
				vPWR_COOLING__Solennoid_TurnOn(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
				//Update Solenoid State
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_ON;
				//Transit to next state
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_WAITING;
				break;
			default:
				//do nothing
				break;

			}
			break; //case: COOLINGSUB_STARTCOOLING
		case COOLINGSUB_WAITING:
			switch(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eCoolingState)
			{
			case COOLING_STATE__WAITING:
				//do nothing
				break;
			case COOLING_STATE__NORMAL:
				//NORMAL COOLING @ Valve duty cycle: 0.5s ON / 1.5 s OFF for T < T warning -> delivered mass flow rate/HE 1-1.5 g/s
				//Stay on for 0.5s/ Turn off between 0.5s and 2s/ Transit back to cooling state after 2s

				if(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count <  5)
				{
					//Do nothing since solenoid was turned on during last state
				}
				else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count >  5 && sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count < 20)
				{
					//Turn off Solenoid here
					vPWR_COOLING__Solennoid_TurnOff(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
					//Update Solenoid State
					sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_OFF;
				}
				else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count > 20)
				{
					//Transit back to cooling state
					sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_STARTCOOLING;
				}
				else
				{
					//handle fault
				}
				break;
			case COOLING_STATE__WARNING:
				//WARNING @ Valve duty cycle 1.0 s ON/ 1.0 s OFF for T > T warning -> delivered mass flow rate/HE 2 - 3 g/s
				//Stay on for 1s/ Turn off between 1s and 2s/ Transit back to cooling state after 2s

				if(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count <  10)
				{
					//Do nothing since solenoid was turned on during last state
				}
				else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count >  10 && sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count < 20)
				{
					//Turn off Solenoid here
					vPWR_COOLING__Solennoid_TurnOff(sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u8N2HETPinNumber);
					//Update Solenoid State
					sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eEddySolenoidState = POWER_COOLING__SOLENOID_OFF;
				}
				else if (sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count > 20)
				{
					//Transit back to cooling state
					sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_STARTCOOLING;
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
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_STARTCOOLING;
				break;
			case COOLING_STATE__EMERGENCY:
				//TODO ENGINE SHUT DOWN

				//Transit back to cooling state
				sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].eState = COOLINGSUB_STARTCOOLING;
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
void vPWR_COOLING_EDDY__100MS_ISR(void)
{
	Luint8 u8Counter;

	for(u8Counter = 0U; u8Counter < (Luint8)POWER_COOLING__MAX_EDDYBRAKES; u8Counter++)
	{
		sPWRNODE.sCooling.sEddyBrakeCoolingSystem[u8Counter].u32100MS_Count++;
	}
}
#endif //C_LOCALDEF__LCCM653__ENABLE_COOLING
#ifndef C_LOCALDEF__LCCM653__ENABLE_COOLING
	#error
#endif

