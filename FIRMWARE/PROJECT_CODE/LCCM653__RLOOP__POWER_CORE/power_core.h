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
		Includes
		*******************************************************************************/
		#include <LCCM653__RLOOP__POWER_CORE/PI_COMMS/power_core__pi_comms__types.h>
		#include <LCCM653__RLOOP__POWER_CORE/power_core__state_types.h>

		//local fault flags
		#include <LCCM653__RLOOP__POWER_CORE/power_core__fault_flags.h>



		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>


		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/

		/** Main Power Node Structure */
		struct _strPWRNODE
		{
			//upper structure guarding
			Luint32 u32Guard1;

			/** main state machine */
			E_PWRNODE__RUN_STATES eMainState;

			/** fault flags structure */
			struct
			{

				/** Main top level fault system */
				FAULT_TREE__PUBLIC_T sTopLevel;

			}sFaults;

			/** Power on state machines and diagnostics */
			struct
			{

				/** The current Init State */
				E_PWRNODE__INIT_STATES eState;

			}sInit;

			/** DC/DC Converter control layer */
			struct
			{

				/** DC/DC state machine */
				E_PWR_DC__STATE_T eState;

				/** Unlock Key Issued*/
				Luint8 u8Unlock;

				/** Issued to safe the pod */
				Luint8 u8PodSafeCommand;

				/** 100ms timer tick flag */
				Luint8 u8100MS_Tick;

				/** Increments of 100ms */
				Luint32 u32100MS_TimerCount;

			}sDC;

			/** Pi Comms Layer */
			struct
			{

				/** the current state */
				E_POWER_PICOM__STATE_T eState;

				/** 100ms timer interrupt tick*/
				Luint8 u8100MS_Timer;

			}sPiComms;

			/** Charger Control */
			struct
			{

				/** Charger Relay control state */
				E_PWRNODE__CHG_RLY_STATES_T eRelayState;


			}sCharger;


			/** Win32 Functions*/
#ifdef WIN32
			struct
			{
				/** The node temp from the TSYS01 sensor */
				Lfloat32 f32NodeTemperature;

			}sWIN32;

#endif
			/** Ethernet comms structure */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4];

				/** 10ms timer tick */
				Luint8 u810MS_Timer;

				/** main state machine */
				E_PWRNODE_NET__MAIN_STATES eMainState;

			}sEthernet;

			//lower structure guarding
			Luint32 u32Guard2;

		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vPWRNODE__Init(void);
		DLL_DECLARATION void vPWRNODE__Process(void);
		void vPWRNODE__RTI_100MS_ISR(void);
		void vPWRNODE__RTI_10MS_ISR(void);

		//fault subsystem
		void vPWRNODE_FAULTS__Init(void);
		void vPWRNODE_FAULTS__Process(void);

		//networking
		void vPWRNODE_NET__Init(void);
		void vPWRNODE_NET__Process(void);
		void vPWRNODE_NET__10MS_ISR(void);
		Luint8 u8PWRNODE_NET__Is_LinkUp(void);
		void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vPWRNODE_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);

		//main application state machine
		void vPWRNODE_SM__Init(void);
		void vPWRNODE_SM__Process(void);

		//DC/DC converter system
		void vPWRNODE_DC__Init(void);
		void vPWRNODE_DC__Process(void);
		void vPWRNODE_DC__Pet_GS_Message(Luint32 u32Key);
		Luint32 u32PWRNODE_DC__Get_TimerCount(void);
		void vPWRNODE_DC__Pod_Safe_Unlock(Luint32 u32UnlockKey);
		void vPWRNODE_DC__Pod_Safe_Go(void);
		void vPWRNODE_DC__100MS_ISR(void);

		//charger relay
		void vPWRNODE_CHG_RELAY__Init(void);
		void vPWRNODE_CHG_RELAY__Process(void);
		void vPWRNODE_CHG_RELAY__On(void);
		void vPWRNODE_CHG_RELAY__Off(void);

		//BMS interface layer
		void vPWRNODE_BMS__Init(void);
		void vPWRNODE_BMS__Process(void);

		//pi comms interface
		void vPWRNODE_PICOMMS__Init(void);
		void vPWRNODE_PICOMMS__Process(void);
		void vPWRNODE_PICOMMS__100MS_ISR(void);

			//common messaging interface
			//for the PodSafe (DC/DC converter system)
			void vPWRNODE_PICOMMS_MSG__PodSafe__UnlockKey(Luint32 u32Key);
			void vPWRNODE_PICOMMS_MSG__PodSafe__Execute(void);
			Luint32 u32PWRNODE_PICOMMS_MSG__PodSafe__Get_Watchdog_Value(void);

			//for the node temperature system
			Lfloat32 f32PWRNODE_PICOMMS_MSG__NodeTemp__Get_DegC(void);
			Luint32 u32PWRNODE_PICOMMS_MSG__NodeTemp__Get_FaulFlags(void);

			//for the node pressure system



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
		Lfloat32 f32PWRNODE_NODETEMP__Get_DegC(void);
		Luint32 u32PWRNODE_NODETEMP__Get_FaultFlags(void);

		//node pressure reading
		void vPWRNODE_NODEPRESS__Init(void);
		void vPWRNODE_NODEPRESS__Process(void);
		Lfloat32 f32PWRNODE_NODEPRESS__Get_Pressure_Bar(void);

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

