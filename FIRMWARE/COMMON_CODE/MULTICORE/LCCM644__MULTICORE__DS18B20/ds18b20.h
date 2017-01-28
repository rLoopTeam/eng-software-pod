/**
 * @file		DS18B20.H
 * @brief		Main header for DS18B20 library
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM644R0.FILE.001
 */


#ifndef _DS18B20_H_
#define _DS18B20_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U
		/*lint -e950*/

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM644__MULTICORE__DS18B20/ds18b20__state_types.h>
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>


		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define C_DS18B20__ROMID_SIZE												(8U)

		#define C_DS18B20__SCRATCHPAD_SIZE											(9U)

		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strDS18B20
		{

			//upper guard.
			Luint32 u32Guard1;

			/** Individual Devices*/
			struct
			{
				/** The device ROM serial number */
				Luint8 u8SerialNumber[C_DS18B20__ROMID_SIZE];

				/** We can support more than a single 1-wire per system, indeed if using the
				 * DS2482 we can support up to 4 one wires.  In this case our sensor could be assigned
				 * on different one wire channels. This variable holds which one wire channel
				 * the device is on.
				 */
				Luint8 u8ChannelIndex;

				/** The resolution of the device in bits. Its important to store this as it affects
				 * timing and other calculations
				 */
				Luint8 u8Resolution;

				/** A user defined index type to help with sensor ID */
				Luint16 u16UserIndex;

			}sDevice[C_LOCALDEF__LCCM644__MAX_DEVICES];


			/** Temperature results */
			struct
			{
				/** The last read temperature */
				Lfloat32 f32Temperature;

			}sTemp[C_LOCALDEF__LCCM644__MAX_DEVICES];

			/** Enumeration results */
			struct
			{

				/** the number of devices we have addresses for */
				Luint16 u16NumDevices;

			}sEnum;



			/** Search State Machine */
			struct
			{

				/** current state */
				E_DS18B20_SEARCH_T sSearchState;

				/** 1-Wire Channel Counter */
				Luint8 u8WireChannelCounter;

				/** The first device searched flag */
				Luint8 u8FirstSearched;

				/** A search has been completed */
				Luint8 u8SearchCompleted;

			}sSearch;

			/**Temporaray scratch pad, save stack */
			Luint8 u8TempScratch[C_DS18B20__SCRATCHPAD_SIZE];


			/** Main state machine */
			E_DS18B20__MAIN_STATES eMainState;

			/** A counter used by the main SM to track progress */
			Luint16 u16MainStateCounter;

			/** The count of 10ms ISR's*/
			Luint32 u32ISR_Counter;


			/** A simple flag to indcate the end of the read process */
			Luint8 u8NewData;

			//lower guard */
			Luint32 u32Guard2;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vDS18B20__Init(void);
		void vDS18B20__Process(void);
		Lfloat32 f32DS18B20__Get_Temperature_DegC(Luint16 u16SensorIndex);
		Luint16 u16DS18B20__Get_NumEnum_Sensors(void);
		Luint8 u8DS18B20__Is_NewDataAvail(void);
		void vDS18B20__Clear_NewDataAvail(void);
		void vDS18B20__10MS_ISR(void);
		Luint32 u32DS18B20__Get_DeviceAddx(void);
		Luint16 u162DS18B20__Get_UserIndex(Luint16 u16SensorIndex);
		Luint8 u82DS18B20__Get_Resolution(Luint16 u16SensorIndex);
		Luint8 u82DS18B20__Get_BusIndex(Luint16 u16SensorIndex);
		void vDS18B20__Get_ROMID(Luint16 u16SensorIndex, Luint8 *pu8Buffer);
		void vDS18B20__Start_ConfigureResolution(void);
		void vDS18B20__Start_TempRead(void);

		//temperature
		Lint16 s16DS18B20_TEMP__Read(Luint16 u16SensorIndex);
		Lint16 s16DS18B20_TEMP__Request(Luint16 u16SensorIndex, Luint8 u8Wait);
		Lint16 s16DS18B20_TEMP__All_Request(Luint16 u16SensorIndex, Luint8 u8Wait);
		Lint16 s16DS18B20_TEMP__All_Request_ByChannel(Luint8 u8ChannelIndex, Luint8 u8Wait);
		Lint16 s16DS18B20_TEMP__Set_Resolution(Luint16 u16SensorIndex, Luint8 u8Resolution);
		Lint16 s16DS18B20_TEMP__Get_Resolution(Luint16 u16SensorIndex, Luint8 *pu8Resolution);
		Lint16 s16DS18B20_TEMP__Get_UserID(Luint16 u16SensorIndex);

		//alarms
		void vDS18B20_ALARMS__Init(void);
		
		//address location
		void vDS18B20_ADDX__Init(void);
		Lint16 s16DS18B20_ADDX__Search(void);
		void vDS18B20_ADDX__SearchSM_Process(void);
		void vDS18B20_ADDX__SearchSM_Start(void);
		Luint8 u8DS18B20_ADDX__SearchSM_IsBusy(void);
		Luint16 u16DS18B20_ADDX__Get_NumEnumerated(void);
		void vDS18B20_ADDX__Set_SearchComplete(void);
		Lint16 s16DS18B20_ADDX__Upload_Addx(Luint16 u16SensorIndex, Luint8 u8ChannelIndex, Luint8 *pu8Addx);

		//scratchpad
		Luint8 u8DS18B20_SCRATCH__Compute_CRC(Luint8 *pu8Scratch);
		Lint16 s16DS18B20_SCRATCH__Read(Luint16 u16SensorIndex, Luint8 *pu8Scratch);
		Lint16 s16DS18B20_SCRATCH__Write(Luint16 u16SensorIndex, const Luint8 *pu8Scratch);

		//wire interface
		Lint16 s16DS18B20_1WIRE__Generate_Reset(Luint8 u8ChannelIndex);
		Lint16 s16DS18B20_1WIRE__SelectDevice(Luint8 u8ChannelIndex, Luint8 *pu8Addx);
		Lint16 s16DS18B20_1WIRE__WriteByte(Luint8 u8ChannelIndex, Luint8 u8Byte);
		Lint16 s16DS18B20_1WIRE__ReadByte(Luint8 u8ChannelIndex, Luint8 *pu8Byte);
		Lint16 s16DS18B20_1WIRE__Skip(Luint8 u8ChannelIndex);
		Lint16 s16DS18B20_SEARCH__SearchFirstDevice(Luint8 u8ChannelIndex, Luint8 *pu8Addx);
		Lint16 s16DS18B20_SEARCH__SearchNextDevice(Luint8 u8ChannelIndex, Luint8 *pu8Addx);
		
		//delay interface
		void vDS18B20_DELAYS__Delay_uS(Luint32 u32Value);
		void vDS18B20_DELAYS__Delay_mS(Luint32 u32Value);
		
		//safetys
		#ifndef C_LOCALDEF__LCCM644__MAX_DEVICES
			#error
		#endif
		#ifndef C_LOCALDEF__LCCM644__MAX_1WIRE_CHANNELS
			#error
		#endif
		#if C_LOCALDEF__LCCM644__MAX_DEVICES > 1000
			//due to data types, limited
			#error
		#endif

	#endif /*#if C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE == 1U*/
	/*safetys*/
	#ifndef C_LOCALDEF__LCCM644__ENABLE_THIS_MODULE
		#error
	#endif
#endif /*_DS18B20_H_*/
