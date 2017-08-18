/**
 * @file		HE_THERM.H
 * @brief		Main Header
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.001
 */

#ifndef _HE_THERM_H_
#define _HE_THERM_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		//cross system networking types
		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>
		
		#include <LCCM721__RLOOP__HE_THERM/he_therm__types.h>
		#include <LCCM721__RLOOP__HE_THERM/he_therm__defines.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		typedef struct
		{

			/** Ethernet Systems */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6U];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4U];

			}sEthernet;

			/** UDP diagnostics system */
			struct
			{

				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u810MS_Flag;

				/** 25x 10 MS ticks */
				Luint8 u8250MS_Flag;

				/** 50x 10 MS ticks */
				Luint8 u8500MS_Flag;

				/** 100x 10 MS ticks for 1 second  */
				Luint8 u81000MS_Flag;

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;


			}sUDPDiag;

			/** Temperature sensors*/
			struct
			{

				/** Temp sensor processing states */
				TE_HETHERM_TEMP__STATE_T eState;

				/** Loaded from memory the number of configured sensors */
				Luint16 u16NumSensors;

				/** Pack memory CRC */
				Luint16 u16PackMemCRC;


				/** Is any new data available? */
				Luint8 u8NewTempAvail;

				/** Counter of number if times the temp sensor was scanned */
				Luint32 u32TempScanCount;

			}sTemp;

			/** Motor Temp System*/
			struct
			{

				struct
				{

					/** Used for computing the highest temperature */
					Lfloat32 f32High;

					/** Used for computing the sum of the temperatures */
					Lfloat32 f32Sum;

					/** The index of the highest temperature sensor */
					Luint16 u16HighestSensorIndex;

					/** Total Count of sensors on this side */
					Luint16 u16TotalCount;

					/** Highest Temp */
					Lfloat32 f32HighestTemp;

					/** Average Temp */
					Lfloat32 f32AverageTemp;


				}sLeftHE, sRightHE, sBrakeMotor;


			}sMotorTemp;

			/** Solenoid control structure */
			struct
			{

				/** Individual Channels */
				struct
				{
					/** Have we thresholded above 75C = 1
					 * Have we thresholded above 95C = 2
					 * Have we thresholded below 65C = 3
					 * Else 0
					 *  */
					Luint8 u8ChannelOverTemp_State;


				}sLeft, sRight, sBrake;


			}sSol;



		}TS_HET__MAIN;

        #define SOL_LEFT  0
        #define SOL_RIGHT 1
        #define SOL_BRAKE 2

		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vHETHERM__Init(void);
		DLL_DECLARATION void vHETHERM__Process(void);

		//ethernet
		void vHETHERM_ETH__Init(void);
		void vHETHERM_ETH__Process(void);
		Luint8 u8HETHERM_ETH__Is_LinkUp(void);
		void vHETHERM_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vHETHERM_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);
		void vHETHERM_ETH__10MS_ISR(void);

		//thermcouple system
		void vHETHERM_TC__Init(void);
		void vHETHERM_TC__Process(void);
		Luint8 u8HETHERM_TC__Is_Avail(void);
		
		//solenoids
		void vHETHERM_SOL__Init(void);
		void vHETHERM_SOL__Process(void);
		void vHETHERM_SOL__Close(Luint8 u8Index);
		void vHETHERM_SOL__Open(Luint8 u8Index);

		//timers
		DLL_DECLARATION void vHETHERM_TIMERS__10MS_ISR(void);
		DLL_DECLARATION void vHETHERM_TIMERS__100MS_ISR(void);
		
			//For WIN32
		#ifdef WIN32
			typedef void (__cdecl * pHETHERM_WIN32__UpdateData_Callback_FuncType)(Luint8 u8SolL, Luint8 u8SolR);
			DLL_DECLARATION void vHETHERM_WIN32__SetCallback_UpdateData(pHETHERM_WIN32__UpdateData_Callback_FuncType pFunc);
			void vHETHERM_WIN32__UpdateData(Luint8 u8SolL, Luint8 u8SolR);
		#endif	
		
	#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_HE_THERM_H_

