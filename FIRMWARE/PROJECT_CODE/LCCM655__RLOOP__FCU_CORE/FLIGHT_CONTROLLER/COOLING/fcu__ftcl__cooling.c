/**
 * @file		FCU__FLIGHT_CONTROL__COOLING_CONTROL.C
 * @brief		Cooling Control Subsystem
 * @author		Paul Le Henaff, Marek Gutt-Mostowy
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__FLIGHT_CTL__COOLING_CONTROL
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_FCTL_COOLING__Init(void)
{
	//TODOD MOVE TO sFCU
	sFCU.sCoolingControl.eGSCoolingCommand = COOLING_CTL_DO_NOTHING; // Set the commands from the ground station to DO_NOTHING at startup
}


void vFCU_FCTL_COOLING__Process(void)
{
	vFCU_FCTL_COOLING__ManualCommandsHandle();

	Luint32 u32PodSpeed = vFCU__POD_SPEED();

	switch(sFCU.sStateMachine.eMissionPhase)
	{
		case MISSION_PHASE__TEST:
		case MISSION_PHASE__PRE_RUN:
		case MISSION_PHASE__POST_RUN:
			/** Main pod command listener*/
			switch(sFCU.sStateMachine.eGSCommands)
			{
				case STATIC_HOVERING:
					if (sFCU.sStateMachine.sOpStates.u8Lifted == 1U && u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
					{
						vFCU_FCTL_COOLING__Enable();
					}
					break;
				case RELEASE_STATIC_HOVERING:
					if (sFCU.sStateMachine.sOpStates.u8StaticHovering == 1U && u32PodSpeed < C_FCU__NAV_PODSPEED_STANDBY)
					{
						vFCU_FCTL_COOLING__Disable();
					}
					break;
			}
			break;
	}
}

void vFCU_FCTL_COOLING__ManualCommandsHandle()
{
	/** Cooling specific command listener*/
	// TODO move to sFCU
	switch(sFCU.sCoolingControl.eGSCoolingCommand)
	{
		// manual commands (for debugging etc)
		case CLOSE_ALL_VALVES:
			vPWR_COOLING__Solennoid_TurnAllOff();
			break;
		case SET_VALVE:
			// TODO find/write function to set the state of a valve
			break;
	}
}

/**
	Nominal commands used by the system
*/
void vFCU_FCTL_COOLING__Enable(void)
{
	vPWR_COOLING__Enable(1U);
}

void vFCU_FCTL_COOLING__Disable(void)
{
	vPWR_COOLING__Enable(0U);
}

/**
	Manual commands used for debugging
*/
void vFCU_COOLING__Valve_Enable(Luint32 u32SolennoidNumber)
{
	// TODO find out what channel and pin numbers to use
	// Possible pin numbers:
	// 8U
	// 16U
	// 22U
	// 23U
	vPWR_COOLING__Solennoid_TurnOn(N2HET_CHANNEL__1, u32SolennoidNumber);
}

void vFCU_COOLING__Valve_Disable(Luint32 u32SolennoidNumber)
{
	// TODO find out what channel and pin numbers to use
	// Possible pin numbers:
	// 8U
	// 16U
	// 22U
	// 23U
	vPWR_COOLING__Solennoid_TurnOff(N2HET_CHANNEL__1, u32SolennoidNumber);
}

#endif //C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
