/**
 * @file		rm4_eeprom.h
 * @brief		Main header for RM4 eeprom
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM230R0.FILE.002
 */

#ifndef _RM4_EEPROM_H_
#define _RM4_EEPROM_H_
	/*lint -e537*/
	#include <localdef.h>

	#ifndef C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE
		#error
	#endif

	/*
	2.2.3 Flash Memory
		The RM48x microcontrollers support up to 3MB of flash for use as program memory. This is divided into
		two separate flash banks, each 1.5MB. The microcontrollers also support a separate 64KB flash bank for
		use as emulated EEPROM.
	2.2.3.1 Flash Bank Sectoring Configuration
		Each bank is divided into multiple sectors. A flash sector is the smallest region in the flash bank that must
		be erased. The sectoring configuration of each flash bank is shown in Table 2-4.
		1. The Flash banks are 144-bit wide bank with ECC support.
		2. The flash bank7 can be programmed while executing code from flash bank0 or bank1.
		3. Code execution is not allowed from flash bank7.
		Refer to the device datasheet for electrical and timing specifications related to the flash module.
	*/

	#define C_LCCM320__FLASH_START_ADDX		0xF0200000U
	#define C_LCCM320__FLASH_BANK			7U
	#define C_LCCM320__FLASH_NUM_SECTORS	4U
	#define C_LCCM320__FLASH_SECTOR_SIZE_BYTES		0x4000U
	#define C_LCCM320__FLASH_SIZE_U32S		0x1000U

	#define C_LCCM320__FLASH_SECTOR_0__START_ADDX		0xF0200000U
	#define C_LCCM320__FLASH_SECTOR_1__START_ADDX		0xF0204000U
	#define C_LCCM320__FLASH_SECTOR_2__START_ADDX		0xF0208000U
	#define C_LCCM320__FLASH_SECTOR_3__START_ADDX		0xF020C000U



	#if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U

		/*****************************************************************************
		Includes
		*****************************************************************************/
		#include <MULTICORE/lccm284__multicore__fault_tree/fault_tree__public.h>
		//fault flags file.
		#include <RM4/LCCM230__RM4__EEPROM/rm4_eeprom__fault_flags.h>


		/** EEPROM Structure */
		typedef struct
		{

			/** The buffer to hold a programming sector */
			Luint8 u8Buffer[C_LCCM320__FLASH_SECTOR_SIZE_BYTES];

			/** The fault tree structure */
			FAULT_TREE__PUBLIC_T sFaultTree;

			//are we init?
			Luint8 u8Init;

			//Is our memory buffer dirty?
			Luint8 u8Dirty;

		}RM4_EEPROM__T;

		/*****************************************************************************
		Function proto's
		*****************************************************************************/
		void vRM4_EEPROM__Init(void);
		Luint32 u32RM4_EEPROM__Read(Luint32 u32AddxOffset);
		Lint32 s32RM4_EEPROM__Read(Luint32 u32AddxOffset);
		Lfloat32 f32RM4_EEPROM__Read(Luint32 u32AddxOffset);
		Lint16 s16RM4_EEPROM__Save(void);
		void vRM4_EEPROM__WriteU32(Luint32 u32AddxOffset, Luint32 u32Value, Luint8 u8Delay);
		void vRM4_EEPROM__WriteS32(Luint32 u32AddxOffset, Lint32 s32Value, Luint8 u8Delay);
		void vRM4_EEPROM__WriteF32(Luint32 u32AddxOffset, Lfloat32 f32Value, Luint8 u8Delay);
		void vRM4_EEPROM__Write_U8Array(Luint8 u8Sector, Luint16 u16AddxInSector, Luint8 *pu8Array, Luint16 u16Length);
		void vRM4_EEPROM__Read_U8Array(Luint8 u8Sector, Luint16 u16AddxInSector, Luint8 *pu8Array, Luint16 u16Length);

		//testing
		#if C_LOCALDEF__LCCM230__ENABLE_TEST_SPEC == 1U
			void vLCCM230_TS_001(void);
			void vLCCM230_TS_002(void);
			void vLCCM230_TS_003(void);
			void vLCCM230_TS_004(void);
			void vLCCM230_TS_005(void);
			void vLCCM230_TS_006(void);
			void vLCCM230_TS_007(void);
		#endif

	#endif //#if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U

#endif //#ifndef _RM4_EEPROM_H_
