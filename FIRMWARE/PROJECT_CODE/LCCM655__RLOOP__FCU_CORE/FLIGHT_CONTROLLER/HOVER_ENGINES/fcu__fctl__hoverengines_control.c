/**
* @file       FCU_FCTRL_HOVERENGINES_CONTROL.C
* @brief      Hover Engines Control
* @author	  Alessandro Caratelli, Marek Gutt-Mostowy
* @copyright  rLoop Inc.
*/

/////////////////////////////////////////////
///////////  WORK IN PROGRESS  //////////////
/////////////////////////////////////////////

// TO DO:
// - Verification

 //Hoverengines handle
 //   void   vFCU_FCTL_HOVERENGINES__Init(void);
 //   void   vFCU_FCTL_HOVERENGINES__Process(void);
 //   void   vFCU_FCTL_HOVERENGINES__Start(void);
 //   void   vFCU_FCTL_HOVERENGINES__Stop(void);
// Luint16 u16FCU_FCTL_HOVERENGINES__Get_State(void)


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

	sFCU.sHoverEngines.eGSCommands = HE_CTL_DO_NOTHING; // Set the commands from the ground station to DO_NOTHING at startup

	sFCU.sHoverEngines.eState = HOVERENGINES_STATE__IDLE; // set the first state of the hover engines control state machine to IDLE

	vFCU_THROTTLE__Enable_Run(); // Enable the throttles state machine
}



void vFCU_FCTL_HOVERENGINES__Process(void)
{
	Luint32 u32PodSpeed; // SHOULD COME FROM THE NAVIGATION FUNCTIONS
	Luint16 u16Rpm[8]; // Used in order to avoid fetching from structure
	Luint16 u8status;
	Luint8  u8Counter;


	vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(); // Call the function with manual commands handling

	switch(sFCU.sHoverEngines.eState)
	{

		case HOVERENGINES_STATE__IDLE:
			// if is received the "Enable hover engines" command or if is active the autonomous behaviour set by the TOD_DRIVE FSM
			if((sFCU.sHoverEngines.eGSCommands == HE_CTL_STATIC_HOVERING) || (sFCU.sHoverEngines.sIntParams.u8Enable == 1U && sFCU.sHoverEngines.sIntParams.u8RunAuto == 1U))
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
			// this state enable the 2nd group of Hover Engines

			if(sFCU.sHoverEngines.sIntParams.u8TempVar < 1U)
			{
				for(u8Counter = 1U; u8Counter < 8U; u8Counter++)
				{
					if(u8Counter == 1U || u8Counter == 2U || u8Counter == 5U || u8Counter == 6U)
					{
						// activate the cooling system for the 2nd group of Hover Engines
						vFCU_COOLING__Set_Valve(u8Counter, 0.5, 1.5); // to be changed (this function is not yet implemented
						// linearly set the 2nd group of Hover Engine RPM from 0 to hover engine nominal RPM
						vFCU_THROTTLE__Set_Throttle(u8Counter, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__RAMP);
						sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = C_FCU__HE_STATIC_HOVER_RPM;
					}
				}
				sFCU.sHoverEngines.sIntParams.u8TempVar = 1U;
			}
			// read the RPM value of the 1st group of Hover Engines
			// If all RPM reach the C_FCU__HE_STATIC_HOVER_RPM value with
			// a certain tolerance, than set the status flag to 1
			u8status = 1U;
			for(u8Counter = 1U; u8Counter < 8U; u8Counter++)
			{
				if(u8Counter == 1U || u8Counter == 2U || u8Counter == 5U || u8Counter == 6U)
				{

					Luint16 u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter);
					//Luint16 u16Rpm = 0U;
					//s16FCU_ASI__ReadMotorRpm(u8Counter, &u16Rpm);
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						u8status = 0U;
				}
			}

			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8status > 0U)
			{
				// go to state HOVERENGINES_STATE__HOVERING
				sFCU.sHoverEngines.eState = HOVERENGINES_STATE__ENABLE_2ND_GROUP;
			}
			break;


		case HOVERENGINES_STATE__ENABLE_2ND_GROUP:
			// this state enable the 2th group of Hover Engines

			if(sFCU.sHoverEngines.sIntParams.u8TempVar < 2U)
			{
				for(u8Counter = 1U; u8Counter < 8U; u8Counter++)
				{
					if(u8Counter == 3U || u8Counter == 4U || u8Counter == 7U || u8Counter == 8U)
					{
						// activate the cooling system for the 2nd group of Hover Engines
						vFCU_COOLING__Set_Valve(u8Counter, 0.5, 1.5); // to be changed (this function is not yet implemented
						// linearly set the 2th group of Hover Engine RPM from 0 to hover engine nominal RPM
						vFCU_THROTTLE__Set_Throttle(u8Counter, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__RAMP);
						sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = C_FCU__HE_STATIC_HOVER_RPM;
					}
				}
				sFCU.sHoverEngines.sIntParams.u8TempVar = 2U;
			}

			// read the RPM value of the 1th group of Hover Engines
			// If all RPM reach the C_FCU__HE_STATIC_HOVER_RPM value with
			// a certain tolerance, than set the status flag to 1
			u8status = 1U;
			for(u8Counter = 1U; u8Counter < 8U; u8Counter++)
			{
				if(u8Counter == 3U || u8Counter == 4U || u8Counter == 7U || u8Counter == 8U)
				{
					Luint16 u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter);
					//Luint16 u16Rpm = 0U;
					//s16FCU_ASI__ReadMotorRpm(u8Counter, &u16Rpm);
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						u8status = 0U;
				}
			}
			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8status > 0U)
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
				for(u8Counter = 1; u8Counter < 8; u8Counter++) // VERIFY PARAMETERS
				{
					// RPM, Temperature and Current are monitored,
					// a fault is reported if those values goes out of the safety range.
					Luint16 u16Rpm = 0;
					Lfloat32  f32Current = 0;
					//Luint16 u16Voltage = 0;
					Lfloat32 f32Temp = 0;
					Luint8  u8ErrorFlag = 0;

					//read hover engine RPM
					u16FCU_ASI__ReadMotorRpm(u8Counter);
					//TODO: CHECK s16FCU_ASI_CTRL__ReadMotorRpm(u8Counter, &u16Rpm);

					//read hover engine Current
					f32FCU_ASI__ReadMotorCurrent(u8Counter);
					//s16FCU_ASI_CTRL__ReadMotorCurrent(u8Counter, &f32Current);

					//read hover engine Voltage
					//s16FCU_ASI_CTRL__ReadMotorVoltage(u8Counter, &u16Voltage);

					//read hover engine Temperature
					f32FCU_ASI__ReadControllerTemperature(u8Counter);
					//s16FCU_ASI_CTRL__ReadControllerTemperature(u8Counter, &f32Temp);

					// verify Current range
					u8ErrorFlag = (f32Current > C_FCU__HE_MAX_CURRENT) ? 1U : 0U;
					u8ErrorFlag = (f32Current < C_FCU__HE_MIN_CURRENT) ? 1U : u8ErrorFlag;
					// verify voltage range
					//u8ErrorFlag = (u16Voltage > C_FCU__HE_MAX_VOLTAGE) ? 1U : u8ErrorFlag;
					//u8ErrorFlag = (u16Voltage < C_FCU__HE_MIN_VOLTAGE) ? 1U : u8ErrorFlag;
					// verify max temperature
					u8ErrorFlag = (f32Temp > C_FCU__HE_MAX_TEMPERATURE) ? 1U : u8ErrorFlag;
					// verify RPM value
					u8ErrorFlag = (u16Rpm > (sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue + C_FCU__HE_RPM_TOLERANCE)) ? 1U : u8ErrorFlag;
					u8ErrorFlag = (u16Rpm < (sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue - C_FCU__HE_RPM_TOLERANCE)) ? 1U : u8ErrorFlag;

					if(u8ErrorFlag == 1U)
					{
						// set hover engine X RPM command and hover engine Y RPM command to 0,
						// where HEY is the hover engine symmetrically opposite to HEX with respect to pod center
						Luint8 u8SimmetricalIndex;
						u8SimmetricalIndex = (u8Counter < 5) ?  (u8Counter + 4) :  (u8Counter - 4);
						vFCU_THROTTLE__Set_Throttle(u8Counter, 0U, THROTTLE_TYPE__STEP);
						vFCU_THROTTLE__Set_Throttle(u8SimmetricalIndex, 0U, THROTTLE_TYPE__STEP);
						sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = 0U;
						sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8SimmetricalIndex] = 0U;
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
						for(u8Counter = 1; u8Counter < 8; u8Counter++)
						{
							//the HE RPM is reduced to hover engine cruise RPM
							sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = C_FCU__HE_CRUISE_RPM;
							vFCU_THROTTLE__Set_Throttle(u8Counter, C_FCU__HE_CRUISE_RPM, THROTTLE_TYPE__STEP);
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
						for(u8Counter = 1; u8Counter < 8; u8Counter++)
						{
							sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = C_FCU__HE_STATIC_HOVER_RPM;
							vFCU_THROTTLE__Set_Throttle(u8Counter, C_FCU__HE_STATIC_HOVER_RPM, THROTTLE_TYPE__STEP);
						}
						sFCU.sHoverEngines.sIntParams.u8SpeedState = 0U;
					}
				}
			} // end of if(sFCU.sHoverEngines.sIntParams.u8RunAuto == 1U) //Manage HE RPM during flight

			// If is received the command to release the static hovering
			// or if the POD_DRIVE FSM disable the HE,
			if((sFCU.sHoverEngines.eGSCommands == HE_CTL_RELEASE_STATIC_HOVERING) || (sFCU.sHoverEngines.sIntParams.u8Enable == 0U))
			{
				// get pod speed
				u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
				if((sFCU.sStateMachine.sOpStates.u8StaticHovering != 0U) && (u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY))
				{
					for(u8Counter = 1; u8Counter < 8; u8Counter++)
					{
						sFCU.sHoverEngines.sIntParams.u32CurrentRPMValue[u8Counter] = 0;
						vFCU_THROTTLE__Set_Throttle(u8Counter, 0, THROTTLE_TYPE__STEP);
						vFCU_COOLING__Set_Valve(u8Counter, 0.0, 2.0);
					}
				}
			}
			// switch to the idle state only when the HE RPM goes to 0 with a certain tolerance
			u8status = 1U;
			for(u8Counter = 1U; u8Counter < 8U; u8Counter++)
			{
					//Luint16 u16Rpm = 0U;
					//s16FCU_ASI__ReadMotorRpm(u8Counter, &u16Rpm);
					Luint16 u16Rpm = u16FCU_ASI__ReadMotorRpm(u8Counter);
					if(u16Rpm < (C_FCU__HE_CRUISE_RPM - C_FCU__HE_RPM_TOLERANCE))
						u8status = 0U;
			}

			// If all the four THROTTLEs reached the C_FCU__HE_STATIC_HOVER_RPM
			if(u8status != 0U)
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
	// TO DO
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


void vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(void)
{
	Luint8 u8ManualControlActive;
	Luint32 u32PodSpeed;
	Luint32 u32GS_RPM = sFCU.sHoverEngines.u32CommandValues;
	switch(sFCU.sHoverEngines.eGSCommands)
	{
		case HE_CTL_M_SET_SPEED_HE1:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(1U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE2:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(2U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE3:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(3U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE4:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(4U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE5:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(5U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE6:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(6U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE7:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(7U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;

		case HE_CTL_M_SET_SPEED_HE8:
			u32PodSpeed = u32FCU_FCTL_NAV__PodSpeed();
			if(u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
				vFCU_THROTTLE__Set_Throttle(8U, u32GS_RPM, THROTTLE_TYPE__STEP);
			break;
	}
}

//temporary cooling function
 void vFCU_COOLING__Set_Valve(ValveNumber, TimeOn, TimeOff)
 {
	 //do nothing
 }

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
