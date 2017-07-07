/**
 * @file		HE_THERM.H
 * @brief		
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
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

			/** Temperature sensors (battery temp)*/
			struct
			{

				/** Temp sensor processing states */
				TE_HETHERM_TEMP__STATE_T eState;

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

		}TS_HET__MAIN;

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

		//thermcouple system
		void vHETHERM_TC__Init(void);
		void vHETHERM_TC__Process(void);
		Luint8 u8HETHERM_TC__Is_Avail(void);
		
		//timers
		void vHETHERM_TIMERS__10MS_ISR(void);
		void vHETHERM_TIMERS__100MS_ISR(void);
		
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

