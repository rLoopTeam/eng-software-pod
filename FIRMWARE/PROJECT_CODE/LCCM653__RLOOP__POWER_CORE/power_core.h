/**
 * @file		POWER_CORE.H
 * @brief		Main header file for the power node core functions
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.001
 */

#ifndef _POWER_CORE_H_
#define _POWER_CORE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/

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
			INIT_STATE__1_WIRE_START,

			/** Run the network search */
			INIT_STATE__1_WIRE_SEARCH

		}E_PWRNODE__INIT_STATES;



		/*******************************************************************************
		Structures
		*******************************************************************************/

		/** Main Power Node Structure */
		struct _strPWRNODE
		{

			/** Power on state machines and diagnostics */
			struct
			{

				/** The current Init State */
				E_PWRNODE__INIT_STATES sState;

			}sInit;


		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vPWRNODE__Init(void);
		void vPWRNODE__Process(void);


	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_POWER_CORE_H_

