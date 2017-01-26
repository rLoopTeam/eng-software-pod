/*
 * power_core__state_types.h
 *
 *  Created on: 13 Nov 2016
 *      Author: Lachlan
 */

#ifndef _POWER__STATE_TYPES_H_
#define _POWER__STATE_TYPES_H_

	/** Repress state machine */
	typedef enum
	{

		/** Doing nothing*/
		REPRESS_STATE__RESET = 0U,

		/** Idle Phase, once we have been enabled */
		REPRESS_STATE__IDLE,

		/** Check the pressure sensor */
		REPRESS_STATE__CHECK_PRESS_SNSR,

		/** Process the pressure */
		REPRESS_STATE__PROCESS_PRESS,

		/** Fault condition */
		REPRESS_STATE__FAULT

	}E_PWRNODE__REPRESS_T;

	/** Cooling system */
	typedef enum
	{
		/** Do nothing */
		COOLING_STATE__RESET = 0U,

		/** Idle Phase, once we have been enabled */
		COOLING_STATE__IDLE,

		/** Hardware check to see if thermocouples are online */
		COOLING_HARDWARE__CHECK,

		/** Check the thermocouple temperature */
		COOLING_STATE__CHECK_TEMPERATURES,

		/** Process the temperature */
		COOLING_STATE__PROCESS_TEMPERATURES,

		/** Fault condition */
		COOLING_STATE__FAULT
	}E_PWRNODE__COOLING_T;


	/** Solenoid State */
	typedef enum
	{
		REPRESS_SOL_STATE__OFF = 0U,

		REPRESS_SOL_STATE__ON

	}E_PWRNODE_REPRESS_SOL_STATE;

	/** Pack A or B */
	typedef enum
	{
		PWRNODE_TYPE__PACK_A = 0U,

		PWRNODE_TYPE__PACK_B,

		PWRNODE_TYPE__PACK_MAX

	}E_PWRNODE_TYPE_T;

		/** Battery Temp Sensor Scan/load states */
		typedef enum
		{

			/** Do nothing */
			BATT_TEMP_STATE__IDLE = 0U,

			/** Load the temp sensor defaults from memory */
			BATT_TEMP_STATE__LOAD_DEFAULTS,

			/** Configure the sensor resolution after the memory load */
			BATT_TEMP_STATE__CONFIGURE_RESOLUTION,

			/** If we are not loading from memory start a scan */
			BATT_TEMP_STATE__START_SCAN,

			/** Wait for the scanning to finish */
			BATT_TEMP_STATE__WAIT_SCAN,

			/** Running with the temp system */
			BATT_TEMP_STATE__RUN

		}E_BATT_TEMP__STATE_T;

		/** Networking States*/
		typedef enum
		{
			NET_STATE__IDLE = 0U,

			/** wait for the link to become avail */
			NET_STATE__WAIT_LINK,

			/** wait for our timer */
			NET_STATE__WAIT_TIMER_TICK,


			NET_STATE__RUN

		}E_PWRNODE_NET__MAIN_STATES;


		/** Power node control states */
		typedef enum
		{
			/** Just come out of reset */
			RUN_STATE__RESET = 0U,

			RUN_STATE__IDLE,

			/** Start the charging state */
			RUN_STATE__CHARGE_START,

			/** process the battery charger system */
			RUN_STATE__CHARGE_PROCESS,

			/** Cleanup the charging process*/
			RUN_STATE__CHARGE_STOP,

			RUN_STATE__TEST,

		}E_PWRNODE__RUN_STATES;

		/** Charger RELAY state machine control */
		typedef enum
		{

			/** Charger control just come out of reset */
			CHG_RLY_STATE__RESET = 0U,

		}E_PWRNODE__CHG_RLY_STATES_T;


		/** Charge Algo */
		typedef enum
		{

			CHG_STATE__IDLE = 0U,

			/** Start the charging process */
			CHG_STATE__START,

			/** Start balancing */
			CHG_STATE__START_BALANCE,

			/** Check the temperature state of the pack */
			CHG_STATE__CHECK_PACK_TEMP,


			/** Run the balancer*/
			CHG_STATE__RUN_BALANCER,

			/** Close charge contactor relay */
			CHG_STATE__CLOSE_CONTACTOR_RELAY,

			/** Check the amount of current flowing in the charger circuit */
			CHG_STATE__CHECK_CHG_CURRENT,

			/** Check the cell voltages during charging */
			CHG_STATE__CHECK_CELL_V_DURING_CHG,

			/** Manual balance control via the GS */
			CHG_STATE__MANUAL_BALANCING,

			/** Abort charging due to some condition */
			CHG_STATE__ABORT


		}E_PWR__CHARGER_STATE_T;

		/** Init states.
		 * These enums are for the init states of the Power Node. As each subsystem is brought
		 * online the states will be incremented.
		 */
		typedef enum
		{

			/** Unknown state, could also be out of reset */
			INIT_STATE__UNKNOWN = 0U,

			/** First starting state launched after Init */
			INIT_STATE__START,

			/** Init any comms channels such as I2C and SPI */
			INIT_STATE__COMMS,

			/** Init the 1 wire network and I2C <> 1 Wire devices */
			INIT_STATE__CELL_TEMP_START,

			/** Init the DC/DC converter layer */
			INIT_STATE__DC_CONVERTER,

			/** Init the BMS layer */
			INIT_STATE__BMS,

			/** Start the TSYS01 */
			INIT_STATE__TSYS01,

			/** Init the node pressure MS5607*/
			INIT_STATE__MS5607,

			/** start the RTI subsystem */
			INIT_STATE__START_TIMERS,

			/** Start any lower level sytems */
			INIT_STATE__START_LOW_SYSTEM,

			/** Normal run state */
			INIT_STATE__RUN

		}E_PWRNODE__INIT_STATES;


		/** DC/DC Converter types */
		typedef enum
		{

			/** DC/DC has just come out of reset */
			DC_STATE__RESET = 0U,

			/** Once powered must latch on */
			DC_STATE__LATCH_COMMAND,

			/** check the WDT needs petting */
			DC_STATE__CHECK_WDT_PET,

			/** Check if we need to implement the pod safe command from the user */
			DC_STATE__CHECK_POD_SAFE,

			/** Check our internal timer to make sure we have not received comms */
			DC_STATE__CHECK_WDT_TIMER,

		}E_PWR_DC__STATE_T;



#endif /* _POWER__STATE_TYPES_H_ */
