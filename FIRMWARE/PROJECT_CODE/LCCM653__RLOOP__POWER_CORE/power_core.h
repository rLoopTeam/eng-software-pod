
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
		#include <LCCM653__RLOOP__POWER_CORE/power_core__defines.h>
		#include <LCCM653__RLOOP__POWER_CORE/power_core__eeprom_index.h>
		#include <LCCM653__RLOOP__POWER_CORE/power_core__enums.h>


		//local fault flags
		#include <LCCM653__RLOOP__POWER_CORE/power_core__fault_flags.h>
		#include <LCCM653__RLOOP__POWER_CORE/CHARGER/IV_MEASURE/power__iv_measure__fault_flags.h>

		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

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

			/** The personality */
			E_PWRNODE_TYPE_T ePersonality;

			/** The ethernet port that we are transmitting from*/
			Luint16 u16EthPort;

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

			/** Temperature sensors (battery temp)*/
			struct
			{

				/** Temp sensor processing states */
				E_BATT_TEMP__STATE_T eState;

				/** Loaded from memory the number of configured sensors */
				Luint16 u16NumSensors;

				/** Pack memory CRC */
				Luint16 u16PackMemCRC;

				/** Highest Temp */
				Lfloat32 f32HighestTemp;

				/** The index of the highest temperature sensor */
				Luint16 u16HighestSensorIndex;

				/** Average Temp */
				Lfloat32 f32AverageTemp;

				/** Is any new data available? */
				Luint8 u8NewTempAvail;

				/** Counter of number if times the temp sensor was scanned */
				Luint32 u32TempScanCount;

			}sTemp;

			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
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
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U
			/** Pi Comms Layer */
			struct
			{

				/** the current state */
				E_POWER_PICOM__STATE_T eState;

				/** 100ms timer interrupt tick*/
				Luint8 u8100MS_Timer;

			}sPiComms;
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
			/** Charger Control */
			struct
			{

				/** Algo */
				struct
				{

					/** Charger state machine */
					E_PWR__CHARGER_STATE_T eState;

				}sAlgo;


				/** Configurable Parameters */
				Lfloat32 f32MaxHighestCell;
				Lfloat32 f32MaxPackVoltage;
				Lfloat32 f32MinPackVoltage;
				Lfloat32 f32MaxCellTemp;

				/** Charger Relay control state */
				E_PWRNODE__CHG_RLY_STATES_T eRelayState;


			}sCharger;
			#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER

			/** ATA6870 interface */
//			#define NUM_CELLS_PER_MODULE    (6U)
/*
			struct
			{

				struct
				{
					Luint8 u8DeviceIndex;

					Lfloat32 pf32Voltages[NUM_CELLS_PER_MODULE];


					Lfloat32 pf32DeviceTemperature;

				}sDevice[C_LOCALDEF__LCCM650__NUM_DEVICES];

			}sATA6870;
*/

			#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
			/** BMS Subsystem */
			struct
			{
				Luint8 u8Dummy;
			}sBMS;
			#endif

			/** LEM HASS 600-S Current Transducer **/
			struct
			{
				/** Current Reading after converted from Voltage */
				Lfloat32 f32HASS_CurrentReading;

				/** Voltage Reading at Init **/
				Lfloat32 f32HASS_VoltageOffSet;

				/** Current Transducer Fault Flag */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				Luint16 u16HAAS_Current_Average_Counter;
				Lfloat32 f32HAAS_Current_Average_Array[C_PWRCORE__CURRENT_AVG_SIZE];

			}sHASS600;

			/** Cooling System **/
			struct
			{
				/** Hover Engine Cooling Subsystem **/
				struct
				{
					Lfloat32 f32Temperature;
					E_PWRNODE__COOLING_STATES eState;
					E_PWR__COOLING_HOVESOLENOID_STATE_T eHoverSolenoidState;
				}sHoverEngineCoolingSystem[POWER_COOLING__MAX_HOVERENG];

				/** Eddy Brake Cooling Subsystem **/
				struct
				{
					Lfloat32 f32Temperature;
					E_PWRNODE__COOLING_STATES eState;
					E_PWR__COOLING_EDDYSOLENOID_STATE_T eEddySolenoidState;
				}sEddyBrakeCoolingSystem[POWER_COOLING__MAX_EDDYBRAKES];

				/** Cooling System Main State Mainchine */
				E_PWRNODE__COOLING_T eMainState;

				/** Count of 100ms */
				Luint32 u32100MS_Count;
			}sCooling;

			/** Win32 Functions*/
#ifdef WIN32
			struct
			{
				/** The node temp from the TSYS01 sensor */
				Lfloat32 f32NodeTemperature;

			}sWIN32;

#endif

			#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
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

			/** UDP diagnostics system */
			struct
			{

				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u810MS_Flag;

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;

				/** A copy of block 0.*/
				Luint32 u32Block0;

			}sUDPDiag;

			#endif

			/** PV Repress System */
			struct
			{

				/** Repress state machine */
				E_PWRNODE__REPRESS_T eState;

				/** The solenoid state */
				E_PWRNODE_REPRESS_SOL_STATE eSolState;

				/** Count of 100ms */
				Luint32 u32100MS_Count;

				/** Pressure Value */
				Lfloat32 f32Press;

			}sRePress;

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

			//transmit
			void vPWRNODE_NET_TX__Init(void);
			void vPWRNODE_NET_TX__Process(void);
			void vPWRNODE_NET_TX__10MS_ISR(void);

		//main application state machine
		void vPWRNODE_SM__Init(void);
		void vPWRNODE_SM__Process(void);
		void vPWRNODE_SM__Enable_ChargingState(void);
		void vPWRNODE_SM__Stop_ChargingState(void);

		//DC/DC converter system
		void vPWRNODE_DC__Init(void);
		void vPWRNODE_DC__Process(void);
		void vPWRNODE_DC__Pet_GS_Message(Luint32 u32Key);
		Luint32 u32PWRNODE_DC__Get_TimerCount(void);
		void vPWRNODE_DC__Pod_Safe_Unlock(Luint32 u32UnlockKey);
		void vPWRNODE_DC__Pod_Safe_Go(void);
		void vPWRNODE_DC__100MS_ISR(void);
		void vPWRNODE_DC__Latch(Luint32 u32Key);

		//charger relay
		void vPWRNODE_CHG_RELAY__Init(void);
		void vPWRNODE_CHG_RELAY__Process(void);
		void vPWRNODE_CHG_RELAY__On(void);
		void vPWRNODE_CHG_RELAY__Off(void);

		//charge algo
		void vPWRNODE_CHG__Init(void);
		void vPWRNODE_CHG__Process(void);
		void vPWRNODE_CHG__Start(void);
		Luint8 u8PWRNODE_CHG__Is_Busy(void);
		void vPWRNODE_CHG__Abort(void);
		void vPWRNODE_GHG__Start_ManualBalance(void);
		void vPWRNODE_GHG__Stop_ManualBalance(void);

		//charger current and voltage measurement
		void vPWRNODE_CHG_IV__Init(void);
		void vPWRNODE_CHG_IV__Process(void);
		void vPWR_CHARGER_ETH__Init(void);
		void vPWR_CHARGER_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//BMS interface layer
		void vPWRNODE_BMS__Init(void);
		void vPWRNODE_BMS__Process(void);
		Lfloat32 f32PWRNODE_BMS__Cell_Get_HighestVoltage(void);
		Lfloat32 f32PWRNODE_BMS__Cell_Get_LowestVoltage(void);
		Lfloat32 f32PWRNODE_BMS__Get_PackVoltage(void);
		Luint8 u8PWRNODE_BMS__Balance_IsBusy(void);
		void vPWRNODE_BMS__Balance_Start(void);
		void vPWRNODE_BMS__Balance_Stop(void);
		void vPWRNODE_BMS__Balance_Manual(Luint8 u8CellIndex, Luint8 u8Enable);
		Luint32 u32PWRNODE_BMS__Get_VoltsUpdateCount(void);

		//eth
		void vPWR_BMS_ETH__Init(void);
		void vPWR_BMS_ETH__Transmit(E_NET__PACKET_T ePacketType);



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
		Luint8 u8PWR_BATTTEMP__Is_Avail(void);

			//memory system
			void vPWRNODE_BATTTEMP_MEM__Init(void);
			void vPWRNODE_BATTTEMP_MEM__Process(void);
			Lint16 s16PWRNODE_BATTEMP_MEM__Load(void);
			Luint16 u16PWRNODE_BATTTEMP_MEM__Get_NumSensors(void);
			void vPWRNODE_BATTEMP_MEM__Set_ROMID(Luint16 u16Index, Luint32 u32ROMID_Upper, Luint32 u32ROMID_Lower);
			void vPWRNODE_BATTEMP_MEM__Set_UserData(Luint16 u16Index, Luint16 UserIndex, Luint8 u8BusID, Luint8 u8Resolution);

			//eth
			void vPWRNODE_BAATTEMP_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vPWRNODE_BAATTEMP_ETH__Transmit_ROMID(Luint32 u32Index);

		//node temperature reading
		void vPWRNODE_NODETEMP__Init(void);
		void vPWRNODE_NODETEMP__Process(void);
		Lfloat32 f32PWRNODE_NODETEMP__Get_DegC(void);
		Luint32 u32PWRNODE_NODETEMP__Get_FaultFlags(void);

		//node pressure reading
		void vPWRNODE_NODEPRESS__Init(void);
		void vPWRNODE_NODEPRESS__Process(void);
		Lfloat32 f32PWRNODE_NODEPRESS__Get_Pressure_Bar(void);

		//PV repress system
		void vPWR_PVPRESS__Init(void);
		void vPWR_PVPRESS__Process(void);
		void vPWR_PVPRESS__100MS_ISR(void);
		void vPWR_PVPRESS__Enable(Luint32 u32Value);

		//cooling system
		void vPWR_COOLING__Init(void);
		void vPWR_COOLING__Process(void);
		void vPWR_COOLING__100MS_ISR(void);
		void vPWR_COOLING__Enable(Luint32 u32Value);
		void vPWR_COOLING__Solennoid_TurnAllOff(void);
		void vPWR_COOLING__Solennoid_TurnOff(Luint32 u32PinNumber);
		void vPWR_COOLING__Solennoid_TurnOn(Luint32 u32PinNumber);
		void vPWR_COOLING_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//cooling hover subsystem
		void vPWR_COOLING_HOVER__Init(void);
		void vPWR_COOLING_HOVER__Process(void);

		//cooling eddy subsystem
		void vPWR_COOLING_EDDY__Init(void);
		void vPWR_COOLING_EDDY__Process(void);
		void vPWR_BMS_ETH__Init(void);
		void vPWR_BMS_ETH__Transmit(E_NET__PACKET_T ePacketType);

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

