/**
 * @file		POWER_CORE__LOCALDEF.H
 * @brief		Local definitions template for the power node core.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.002
 */

#if 0

/*******************************************************************************
RLOOP - POWER NODE CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

		/** Enable or disable the PiComms layer */
		#define C_LOCALDEF__LCCM653__ENABLE_PI_COMMS						(1U)

		/** Enable the battery temperature measurement system */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP						(1U)

		/** Enable or disable battery temp search */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP_SEARCH				(0U)

		/** Enable the BMS Subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_BMS								(1U)

		/** Enable the PV temp system using TSYS01 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP						(1U)

		/** Node pressure using MS5607 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS						(1U)

		/** Enable the DC/DC converter subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER					(1U)

		//when the DC/DC is enabled we can implement a timeout timer from
		//heartbeat (or any GS comms)
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER__HEART_TIMEOUT		(1U)

		//define the max amount of 100ms increments before the WDT turns off
		#define C_LOCALDEF__LCCM653__DC_CONVERTER__HEART_TIMER_MAX			(30U)

		/** Enable the charger subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_CHARGER							(1U)

		/** Enable Ethernet */
		#define C_LOCALDEF__LCCM653__ENABLE_ETHERNET						(1U)

		/** Enable Pressure Vesel Repress System */
		#define C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS						(1U)

		/** Enable HE Cooling System */
		#define C_LOCALDEF__LCCM653__ENABLE_COOLING							(1U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM653__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM653__RLOOP__POWER_CORE/power_core.h>

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

#endif //#if 0

