/**
 * @file		DS2482S.H
 * @brief		Main DS2482S header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.001
 */

#ifndef _DS2482S_H_
#define _DS2482S_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

		/*lint -e950*/
		#include <MULTICORE/LCCM641__MULTICORE__DS2482S/ds2482s__reg_defs.h>
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strDS2482S
		{

			/** Search parameters */
			struct
			{
				/** the last read serial number from the search*/
				Luint8 u8ROM_SerialNumber[8U];


				/** Bit index that identifies from which bit the (next) search
				 * discrepency should start. */
				Luint8 u8LastDiscrepancy;

				/** Bit index that identifies the LastDiscrepancy within the first
				 * 8-bit family code ROM number */
				Luint8 u8LastFamilyDiscrepancy;

				/** Indicates tha the previous seach uncovered the last device, there are no
				 * more devices participating */
				Luint8 u8LastDeviceFlag;

				/** CRC storage */
				Luint8 u8CRC8;

			}sSearch[C_LOCALDEF__LCCM641__NUM_DEVICS];

			/** Specific flags and diagnostics for each device */
			struct
			{

				/** The local fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

			}sDevice[C_LOCALDEF__LCCM641__NUM_DEVICS];

		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		//user layer
		void vDS2482S__Init(void);
		void vDS2482S__Process(void);
		Luint8 u8DS2482S_USER__1Wire_Reset(Luint8 u8DeviceIndex);


		//device
		Lint16 s16DS2482S_DEVICE__Reset(Luint8 u8DeviceIndex);
		Lint16 s16DS2482S_DEVICE__Get_Status(Luint8 u8DeviceIndex, Luint8 *pu8Status);
		Lint16 s16DS2482S_DEVICE__Set_ConfigRegister(Luint8 u8DeviceIndex, Luint8 u8Value);
		Lint16 s16DS2482S_DEVICE__Read_ConfigRegister(Luint8 u8DeviceIndex, Luint8 *pu8Value);
		Luint8 u8DS2482S_DEVICE__Wait_Busy(Luint8 u8DeviceIndex, Luint8 *pu8Status);
		Lint16 s16DS2482S_DEVICE__Read_Byte(Luint8 u8DeviceIndex, Luint8 *pu8Value);

		//lowlevel
		void vDS2482S_LOWLEVEL__Init(Luint8 u8DeviceIndex);
		Lint16 s16DS2482S_LOWLEVEL__TxReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister);
		Lint16 s16DS2482S_LOWLEVEL__RxReg(Luint8 u8DeviceIndex, Luint8 *pu8Data);
		Lint16 s16DS2482S_LOWLEVEL__WriteReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister, Luint8 u8Value);
		Lint16 s16DS2482S_LOWLEVEL__ReadReg(Luint8 u8DeviceIndex, E_DS2482_REGS eRegister, Luint8 *pu8Value);

		//CRC
		Luint8 u8DS2482S_CRC__CRC8(const Luint8 *pu8Data, Luint8 u8Length);

		//onewire
		Lint16 s16DS2482S_1WIRE__Generate_Reset(Luint8 u8DeviceIndex);
		Lint16 s16DS2482S_1WIRE__WriteByte(Luint8 u8DeviceIndex, Luint8 u8Byte, Luint8 u8PowerUp);
		Lint16 s16DS2482S_1WIRE__ReadByte(Luint8 u8DeviceIndex, Luint8 *pu8Byte, Luint8 u8PowerUp);
		Lint16 s16DS2482S_1WIRE__WriteBit(Luint8 u8DeviceIndex, Luint8 u8Byte, Luint8 u8PowerUp);
		Lint16 s16DS2482S_1WIRE__ReadBit(Luint8 u8DeviceIndex, Luint8 *pu8Byte);
		Lint16 s16DS2482S_1WIRE__SelectDevice(Luint8 u8DeviceIndex, const Luint8 *pu8Addx);
		Lint16 s16DS2482S_1WIRE__Skip(Luint8 u8DeviceIndex);

		//search
		Lint16 s16DS2482S_SEARCH__SearchFirstDevice(Luint8 u8DeviceIndex, Luint8 *pu8Addx);
		Lint16 s16DS2482S_SEARCH__SearchNextDevice(Luint8 u8DeviceIndex, Luint8 *pu8Addx);
		Lint16 s16DS2482S_SEARCH__Verify(Luint8 u8DeviceIndex, const Luint8 *pu8Addx);


		//safetys
		#ifndef C_LOCALDEF__LCCM641__NUM_DEVICS
			#error
		#endif

	#endif //#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_DS2482S_H_


