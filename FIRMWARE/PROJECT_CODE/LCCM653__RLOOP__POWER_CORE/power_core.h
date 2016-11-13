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

		#include <LCCM653__RLOOP__POWER_CORE/PI_COMMS/power_core__pi_comms__types.h>

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
			INIT_STATE__CELL_TEMP_START,

			/** Run the network search */
			INIT_STATE__CELL_TEMP_SEARCH,

			/** Done with the 1-wire searching */
			INIT_STATE__CELL_TEMP_SEARCH_DONE,

			/** Init the BMS layer */
			INIT_STATE__BMS,

			/** Start the TSYS01 */
			INIT_STATE__TSYS01,

			/** Init the node pressure MS5607*/
			INIT_STATE__MS5607,


			/** Normal run state */
			INIT_STATE__RUN

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

			/** Pi Comms Layer */
			struct
			{

				/** the current state */
				E_POWER_PICOM__STATE_T eState;

			}sPiComms;


			/** Win32 Functions*/
#ifdef WIN32
			struct
			{
				/** The node temp from the TSYS01 sensor */
				Lfloat32 f32NodeTemperature;

			}sWIN32;

#endif

		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vPWRNODE__Init(void);
		DLL_DECLARATION void vPWRNODE__Process(void);

		//main application state machine
		void vPWRNODE_SM__Init(void);

		//BMS interface layer
		void vPWRNODE_BMS__Init(void);
		void vPWRNODE_BMS__Process(void);

		//pi comms interface
		void vPWRNODE_PICOMMS__Init(void);
		void vPWRNODE_PICOMMS__Process(void);

		//CAN
		void vPWRNODE_CAN__Init(void);
		void vPWRNODE_CAN__Process(void);

		//battery temperature system
		void vPWRNODE_BATTTEMP__Init(void);
		void vPWRNODE_BATTTEMP__Process(void);
		void vPWRNODE_BATTTEMP__Start_Search(void);
		Luint8 u8PWRNODE_BATTTEMP__Search_IsBusy(void);

		//node temperature reading
		void vPWRNODE_NODETEMP__Init(void);
		void vPWRNODE_NODETEMP__Process(void);
		Lfloat32 f32PWRNODE_NODETEMP__Get_Temperature_DegC(void);

		//node pressure reading
		void vPWNODE_NODEPRESS__Init(void);
		void vPWNODE_NODEPRESS__Process(void);

#ifdef WIN32
		void vPWRNODE_WIN32__Init(void);
		DLL_DECLARATION void vPWRNODE_WIN32__Set_NodeTemperature(Lfloat32 f32Temperature);
#endif

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_POWER_CORE_H_

