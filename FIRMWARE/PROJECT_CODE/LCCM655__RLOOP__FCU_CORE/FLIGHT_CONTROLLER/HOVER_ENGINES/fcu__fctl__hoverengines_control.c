/**
* @file       FCU_FCTRL_HOVERENGINES_CONTROL.C
* @brief      Hover Engines Control
* @author	  Alessandro Caratelli, Marek Gutt-Mostowy
* @copyright  rLoop Inc.
*/



 //Hoverengines handle
 //   void    vFCU_FCTL_HOVERENGINES__Init(void);
 //   void    vFCU_FCTL_HOVERENGINES__Process(void);
 //   void    vFCU_FCTL_HOVERENGINES__Start(void);
 //   void    vFCU_FCTL_HOVERENGINES__Stop(void);
 //   Luint16 u16FCU_FCTL_HOVERENGINES__Get_State(void)




// TO DO:
// - Verification


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL == 1U

extern struct _strFCU sFCU;

// TODO: need the following functions:
// vFCU_COOLING__Set_Valve(ValveNumber, TimeOn, TimeOff);
// u32FCU_FCTL_NAV__PodSpeed();

void vFCU_FCTL_HOVERENGINES__Init(void)
{

	sFCU.sHoverEngines.sIntParams.u8Enable = 0U; // temporary variable to be used inside of the functions
	sFCU.sHoverEngines.sIntParams.u8SpeedState = 0U; //TO BE LOOKED UP AGAIN
	sFCU.sHoverEngines.sIntParams.u8RunAuto = 0U; // Flag to initiate flight mode
	sFCU.sHoverEngines.sIntParams.u8TempVar = 0U; // Tempo variable used inside of the functions

	sFCU.sHoverEngines.eGSCommands = 0U; // Set the commands from the ground station to DO_NOTHING at startup

	sFCU.sHoverEngines.eState = HOVERENGINES_STATE__IDLE; // set the first state of the hover engines control state machine to IDLE

	vFCU_THROTTLE__Enable_Run(); // Enable the throttles state machine
}



void vFCU_FCTL_HOVERENGINES__Process(void)
{
	Luint32 u32PodSpeed; // SHOULD COME FROM THE NAVIGATION FUNCTIONS
	Luint8 u8Status;
	Luint8 u8Counter;
	Luint16 u16Rpm;


	//vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(); // Call the function with manual commands handling

	switch(sFCU.sHoverEngines.eState)
	{

		case HOVERENGINES_STATE__IDLE:
			// if is received the "Enable hover engines" command or if is active the autonomous behaviour set by the POD_DRIVE FSM
			if((sFCU.sHoverEngines.eGSCommands == START_STATIC_HOVERING) || (sFCU.sHoverEngines.sIntParams.u8Enable == 1U && sFCU.sHoverEngines.sIntParams.u8RunAuto == 1U))
			{
				// fetch the pod speed
				u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
				// if the pod speed is lower than the pod standby speed and the pod is lifted
				if((u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY) && (sFCU.sStateMachine.sOpStates.u8Lifted != 0U))
				{
					// go to HOVERENGINES_STATE__ENABLED state
					sFCU.sHoverEngines.sIntParams.u8TempVar = 0U;
					sFCU.sHoverEngines.eState = HOVERENGINES_STATE__ENABLE_1ST_GROUP;
				}
			}
			break;


		case HOVERENGINES_STATE__ENABLE_1ST_GROUP:

			// this state enable the 1st group of Hover Engines

			//Check if this is the first iteration of the loop. In case we have already been here, skip the startup command procedure
			if(sFCU.sHoverEngines.sIntParams.u8TempVar < 1U)
			{
				//Set up the for loop for all of the Hover Engines
				for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
				{
					//Choose the subset of Hover Engines with indices 0,1,4,5
					if(u8Counter == 1U || u8Counter == 2U || u8Counter == 5U || u8Counter == 6U)
					{
						// linearly set the 1st group of Hover Engine RPM from 0 to hover engine nominal RPM
						vFCU_THROTTLE__Set_Throttle(u8Counter-1U, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__STEP);
						//sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = C_FCU__HE_STATIC_HOVER_RPM;
					}
				}
				//Set a flag indicating we just commanded a start up of the first group of the engines, so that we do not repeat it in the next cycle
				sFCU.sHoverEngines.sIntParams.u8TempVar = 1U;
			}
			else
			{
				//do nothing ???
			}

			//Check whether the Hover Engines RPMs from the first group are within the range
			//Set up a guard flag to 1 which will be set to 0 if any of the engines is not within the range
			u8Status = 1U;
			//Set up a for loop for all of the Hover Engines. Indices 0-7
			for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
			{
				//Choose only Hover Engines with Index 0,1,4,5
				if(u8Counter == 1U || u8Counter == 2U || u8Counter == 5U || u8Counter == 6U)
				{
					//Read the current RPM value for one of the Hover Engines from the subset
					u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter-1U);
					//Check if the Hover Engine RPM is below our Range
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						//if the Hover Engine Current RPM is below our range set the flag to zero, so that we cannot transition to the next state
						u8Status = 0U;
				}
			}

			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8Status == 1U)
			{
				// go to the state HOVERENGINES_STATE__HOVERING
				sFCU.sHoverEngines.eState = HOVERENGINES_STATE__ENABLE_2ND_GROUP;
			}
			else
			{
				//stay in the same state and check if the hover engines have started
				sFCU.sHoverEngines.eState = HOVERENGINES_STATE__ENABLE_1ST_GROUP;
			}
			break;


		case HOVERENGINES_STATE__ENABLE_2ND_GROUP:
			// this state enable the 2th group of Hover Engines

			//Check whether we have alredy been here. In case we were skip and go straight to checking the Hover Engines Current RPM
			if(sFCU.sHoverEngines.sIntParams.u8TempVar < 2U)
			{
				//Set up a for loop to cycle through all of the hover engines
				for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
				{
					//Choose the second group of the hover engines with the indices of 2, 3, 6, 8
					if(u8Counter == 3U || u8Counter == 4U || u8Counter == 7U || u8Counter == 8U)
					{

						//Set the 2nd group of Hover Engine RPM from 0 to hover engine nominal RPM
						vFCU_THROTTLE__Set_Throttle(u8Counter-1U, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__STEP);
						//sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = C_FCU__HE_STATIC_HOVER_RPM;
					}
				}
				//Set a temporary variable to 2 so that when we enter the state next time we do not try to command the hover engines again.
				sFCU.sHoverEngines.sIntParams.u8TempVar = 2U;
			}

			//Check whether the Hover Engines RPMs from the second group are within the range
			//Set up a guard flag to 1 which will be set to 0 if any of the engines is not within the range
			u8Status = 1U;
			//Set up a for loop for all of the Hover Engines. Indices 0-7
			for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
			{
				//Choose only Hover Engines with Index 2,3,6,7
				if(u8Counter == 3U || u8Counter == 4U || u8Counter == 7U || u8Counter == 8U)
				{
					//Read the current RPM value for one of the Hover Engines from the subset
					u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter-1U);
					//Check if the Hover Engine RPM is below our Range
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						//if the Hover Engine Current RPM is below our range set the flag to zero, so that we cannot transition to the next state
						u8Status = 0U;
				}
			}


			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8Status > 0U)
			{
				// go to state HOVERENGINES_STATE__HOVERING
				sFCU.sHoverEngines.eState = HOVERENGINES_STATE__HOVERING;
				sFCU.sHoverEngines.sIntParams.u8Enable = 1U;
			}
			break;

		// State HOVERENGINES_STATE__HOVERING: In this state all Hover Engines are running at the STATIC_HOVER_RPM.
		case HOVERENGINES_STATE__HOVERING:

			// If running in Autonomous behavior mode during flight
			if(sFCU.sHoverEngines.sIntParams.u8RunAuto == 1U) //Manage HE RPM during flight
			{
				for(u8Counter = 1U; u8Counter <= 8U; u8Counter++) // VERIFY PARAMETERS
				{
					// RPM, Temperature and Current are monitored,
					// a fault is reported if those values goes out of the safety range.
					Luint16 u16Rpm = 0U;
					Lfloat32  f32Current = 0U;
					//Luint16 u16Voltage = 0;
					Lfloat32 f32Temp = 0U;
					Luint8  u8ErrorFlag = 0U;

					//read hover engine RPM
					//u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter-1U);
					//TODO: CHECK s16FCU_ASI_CTRL__ReadMotorRpm(u8Counter, &u16Rpm);

					//read hover engine Current
					f32Current = f32FCU_ASI__ReadMotorCurrent(u8Counter-1U);
					//s16FCU_ASI_CTRL__ReadMotorCurrent(u8Counter-1, &f32Current);

					//read hover engine Voltage
					//s16FCU_ASI_CTRL__ReadMotorVoltage(u8Counter-1, &u16Voltage);

					//read hover engine Temperature
					f32Temp = f32FCU_ASI__ReadControllerTemperature(u8Counter-1U);
					//s16FCU_ASI_CTRL__ReadControllerTemperature(u8Counter-1, &f32Temp);

					// verify Current range
					u8ErrorFlag = (f32Current > C_FCU__HE_MAX_CURRENT) ? 1U : 0U;
					u8ErrorFlag = (f32Current < C_FCU__HE_MIN_CURRENT) ? 1U : u8ErrorFlag;
					// verify voltage range
					//u8ErrorFlag = (u16Voltage > C_FCU__HE_MAX_VOLTAGE) ? 1U : u8ErrorFlag;
					//u8ErrorFlag = (u16Voltage < C_FCU__HE_MIN_VOLTAGE) ? 1U : u8ErrorFlag;
					// verify max temperature
					u8ErrorFlag = (f32Temp > C_FCU__HE_MAX_TEMPERATURE) ? 1U : u8ErrorFlag;
					// verify RPM value

					//Checking if the Current RPM is higher than the Static Hover RPM + the Tolerance
					if (sFCU.sASI.sHolding[u8Counter - 1U].u16RPM > C_FCU__HE_STATIC_HOVER_RPM + C_FCU__HE_RPM_TOLERANCE)
					{
						//Set the error flag to 1 if true
						u8ErrorFlag = 1U;
					}
					else
					{
						//Current Rpm below the max allowable RPM
						u8ErrorFlag = 0U;
					}

					if (sFCU.sASI.sHolding[u8Counter - 1U].u16RPM < C_FCU__HE_STATIC_HOVER_RPM + C_FCU__HE_RPM_TOLERANCE)
										{
					 = (sFCU.sASI.sHolding[u8Counter - 1U].u16RPM < (sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue - C_FCU__HE_RPM_TOLERANCE)) ? 1U : u8ErrorFlag;

					 u8ErrorFlag

					if(u8ErrorFlag == 1U)
					{
						// set hover engine X RPM command and hover engine Y RPM command to 0,
						// where HEY is the hover engine symmetrically opposite to HEX with respect to pod center
						Luint8 u8SimmetricalIndex;
						u8SimmetricalIndex = (u8Counter < 5U) ?  (u8Counter + 4U) :  (u8Counter - 4U);
						vFCU_THROTTLE__Set_Throttle(u8Counter-1, 0U, THROTTLE_TYPE__STEP);
						vFCU_THROTTLE__Set_Throttle(u8SimmetricalIndex-1U, 0U, THROTTLE_TYPE__STEP);
						sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = 0U;
						sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8SimmetricalIndex-1U] = 0U;
					}
				}
				// get pod speed
				u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
				// If the pod speed goes higher than the max speed to stabilize pod
				if((u32PodSpeed > C_FCU__NAV_PODSPEED_MAX_SPEED_TO_STABILIZE) && (sFCU.sHoverEngines.sIntParams.u8SpeedState == 0U))
				{
					// avoid continusly send the command
					if(sFCU.sHoverEngines.sIntParams.u8SpeedState == 0U)
					{
						for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
						{
							//the HE RPM is reduced to hover engine cruise RPM
							sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = C_FCU__HE_CRUISE_RPM;
							vFCU_THROTTLE__Set_Throttle(u8Counter-1U, C_FCU__HE_CRUISE_RPM, THROTTLE_TYPE__STEP);
						}
						sFCU.sHoverEngines.sIntParams.u8SpeedState = 1U;
					}
				}
				// If the pod speed goes lower than the max speed to stabilize pod
				else
				{
					// avoid continusly send the command
					if(sFCU.sHoverEngines.sIntParams.u8SpeedState == 1U)
					{
						for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
						{
							sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = C_FCU__HE_STATIC_HOVER_RPM;
							vFCU_THROTTLE__Set_Throttle(u8Counter-1, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__STEP);
						}
						sFCU.sHoverEngines.sIntParams.u8SpeedState = 0U;
					}
				}
			} // end of if(sFCU.sHoverEngines.sIntParams.u8RunAuto == 1U) //Manage HE RPM during flight

			// If is received the command to release the static hovering
			// or if the POD_DRIVE FSM disable the HE,
			if((sFCU.sHoverEngines.eGSCommands == NET_PKT__FCU_HOVERENGINES_CONTROL__RELEASE_STATIC_HOVERING) || (sFCU.sHoverEngines.sIntParams.u8Enable == 0U))
			{
				// get pod speed
				u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
				if((sFCU.sStateMachine.sOpStates.u8StaticHovering != 0U) && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
				{
					for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
					{
						sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[u8Counter-1U] = 0U;
						vFCU_THROTTLE__Set_Throttle(u8Counter-1U, 0U, THROTTLE_TYPE__STEP);
//						vFCU_COOLING__Set_Valve(u8Counter-1U, 0.0, 2.0);
					}
				}
			}
			// switch to the idle state only when the HE RPM goes to 0 with a certain tolerance
			u8Status = 1U;
			for(u8Counter = 1U; u8Counter <= 8U; u8Counter++)
			{
					//Luint16 u16Rpm = 0U;
					//s16FCU_ASI__ReadMotorRpm(u8Counter, &u16Rpm);
					Luint16 u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter-1);
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						u8Status = 0U;
			}

			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8Status != 0U)
			{
				// go to state IDLE
				sFCU.sHoverEngines.eState = HOVERENGINES_STATE__IDLE;
				sFCU.sHoverEngines.sIntParams.u8Enable = 0U;
				sFCU.sHoverEngines.sIntParams.u8RunAuto = 0U;
			}
			break;
	} //switch(sFCU.sHoverEngines.eState)
}

E_FCU__HOVERENGINES_STATES_T eFCU_FCTL_HOVERENGINES__Get_State(void)
{
	return sFCU.sHoverEngines.eState;
}

Luint16 u16FCU_FCTL_HOVERENGINES__Get_FaultFlag(void){
	return 0U;
}

void vFCU_FCTL_HOVERENGINES__Enable(void)
{
	sFCU.sHoverEngines.sIntParams.u8Enable = 1U;
}

void vFCU_FCTL_HOVERENGINES__Disable(void)
{
	sFCU.sHoverEngines.sIntParams.u8RunAuto = 0U;
	sFCU.sHoverEngines.sIntParams.u8Enable  = 0U;
}

void vFCU_FCTL_HOVERENGINES__Start(void)
{
	if(sFCU.sHoverEngines.sIntParams.u8Enable != 0U)
		sFCU.sHoverEngines.sIntParams.u8RunAuto = 1U;
}

void vFCU_FCTL_HOVERENGINES__Stop(void)
{
	sFCU.sHoverEngines.sIntParams.u8RunAuto  = 0U;
}

/** Handle commands from the Ground Station */
 void vFCU_FCTL_HOVERENGINES_GS_START_COMMAND()
 {
	 sFCU.sHoverEngines.eGSCommands = START_STATIC_HOVERING;
 }


//void vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(void)
//{
//	Luint32 u32GS_RPM = sFCU.sHoverEngines.u32CommandValues;
//	switch(sFCU.sHoverEngines.eGSCommands)
//	{
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE1:
//			vFCU_THROTTLE__Set_Throttle(0U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[0U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE2:
//			vFCU_THROTTLE__Set_Throttle(1U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[1U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE3:
//			vFCU_THROTTLE__Set_Throttle(2U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[2U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE4:
//			vFCU_THROTTLE__Set_Throttle(3U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[3U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE5:
//			vFCU_THROTTLE__Set_Throttle(4U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[4U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE6:
//			vFCU_THROTTLE__Set_Throttle(5U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[5U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE7:
//			vFCU_THROTTLE__Set_Throttle(6U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[6U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//
//		case NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE8:
//			vFCU_THROTTLE__Set_Throttle(7U, u32GS_RPM, THROTTLE_TYPE__STEP);
//			sFCU.sHoverEngines.sIntParams.u16CurrentRPMValue[7U] = u32GS_RPM;
//			sFCU.sHoverEngines.eGSCommands = 0U;
//			break;
//	}
//}



//vFCU_FCTL_HOVERENGINES__SetCommand(e32Command, Luint32 u32Value)
//{
//	sFCU.sHoverEngines.eGSCommands = e32Command;
//	sFCU.sHoverEngines.u32CommandValues = u32Value;
//}

#endif //C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL
//	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
//	#error
#endif


#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//	#error
#endif
