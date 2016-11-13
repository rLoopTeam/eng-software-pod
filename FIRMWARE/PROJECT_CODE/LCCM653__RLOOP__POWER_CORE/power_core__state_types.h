/*
 * power_core__state_types.h
 *
 *  Created on: 13 Nov 2016
 *      Author: Lachlan
 */

#ifndef RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__STATE_TYPES_H_
#define RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__STATE_TYPES_H_


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

			/** Run the network search */
			INIT_STATE__CELL_TEMP_SEARCH,

			/** Done with the 1-wire searching */
			INIT_STATE__CELL_TEMP_SEARCH_DONE,

			/** Init the DC/DC converter layer */
			INIT_STATE__DC_CONVERTER,

			/** Init the BMS layer */
			INIT_STATE__BMS,

			/** Start the TSYS01 */
			INIT_STATE__TSYS01,

			/** Init the node pressure MS5607*/
			INIT_STATE__MS5607,


			/** Normal run state */
			INIT_STATE__RUN

		}E_PWRNODE__INIT_STATES;


		/** DC/DC Converter types */
		typedef enum
		{

			/** DC/DC has just come out of reset */
			DC_STATE__RESET = 0U,

			/** check the WDT needs petting */
			DC_STATE__CHECK_WDT_PET,


			DC_STATE__CHECK_POD_SAFE,

		}E_PWR_DC__STATE_T;



#endif /* RLOOP_LCCM653__RLOOP__POWER_CORE_POWER_CORE__STATE_TYPES_H_ */
