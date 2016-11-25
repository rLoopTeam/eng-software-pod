/**
 * @file		rm4_flash.h
 * @brief		FLASH main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @st_fileID	LCCM135R0.FILE.002
 */

#ifndef _RM4_FLASH_H_
#define _RM4_FLASH_H_

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U

	#include <RM4/LCCM135__RM4__FLASH/rm4_flash__private.h>
	#include <RM4/LCCM135__RM4__FLASH/rm4_flash__fault_flags.h>
	#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>


	//Include the TI parts
	#if C_LOCALDEF__LCCM135__ENABLE_F021 == 1U
		#include <RM4/LCCM135__RM4__FLASH/F021_Flash_API/V2.00.01/Include/F021.h>
	#endif


	//our own return types
	#define C_LCCM135__RETURN_TYPE__SUCCESS					(0)
	#define C_LCCM135__RETURN_TYPE__ERROR_FSM_BUSY			(-1)
	#define C_LCCM135__RETURN_TYPE__ERROR_GENERIC			(-2)
	#define C_LCCM135__RETURN_TYPE__ERROR_NULL_POINTER		(-3)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_COMMAND	(-4)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_ECC_ADDX	(-5)
	#define C_LCCM135__RETURN_TYPE__ERROR_OTP_CHECKSUM		(-6)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_HCLK		(-7)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_BANK		(-8)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_ADDX		(-9)
	#define C_LCCM135__RETURN_TYPE__ERROR_INVALID_READ_MODE	(-10)
	#define C_LCCM135__RETURN_TYPE__ERROR_DATA_BUFF_LEN		(-11)
	#define C_LCCM135__RETURN_TYPE__ERROR_ECC_BUFF_LEN		(-12)
	#define C_LCCM135__RETURN_TYPE__ERROR_ECC_BUFF_MISMATCH	(-13)
	#define C_LCCM135__RETURN_TYPE__ERROR_NOT_AVAIL			(-14)


	#define C_LCCM135__RETURN_TYPE__ERROR_NOT_ERASED			(-15)
	#define C_LCCM135__RETURN_TYPE__ERROR_NOT_PROGRAMMED		(-16)
	#define C_LCCM135__RETURN_TYPE__ERROR_DUT_FAILED			(-17)



	#if C_LOCALDEF__LCCM135__ENABLE_F021 == 1U


		//function protos
		void vRM4_FLASH__Init(void);
		Luint32 u32RM4_FLASH__Get_FaultFlags(void);
		Lint16 s16RM4_FLASH__BlockProgram(Luint32 u32Bank, Luint32 u32Flash_Start_Address, Luint32 u32Data_Start_Address, Luint32 u32Size_In_Bytes);
		Lint16 s16RM4_FLASH__SectorErase(Luint32 u32Bank, Luint32 u32Flash_Start_Address, Luint32 u32Size_In_Bytes);
		Lint16 s16RM4_FLASH__BankErase(Luint32 u32Bank, Luint32 u32Flash_Start_Address, Luint32 u32Size_In_Bytes);
		Lint16 s16RM4_FLASH__EraseCheck(Luint32 u32Start_Address, Luint32 u32Bytes);
		Lint16 s16RM4_FLASH__ProgramCheck(Luint32 u32Program_Start_Address, Luint32 u32Source_Start_Address, Luint32 u32No_Of_Bytes);

		#ifndef WIN32
			Lint16 s16RM4_FLASH__F021ErorCode(Fapi_StatusType stReturn1);
			void vRM4_FLASH__SetFault_F021ErorCode(Fapi_StatusType stReturn1);
		#endif

		Lint16 s16RM4_FLASH__ProgramArray(Luint8 u8Bank, Luint8 u8Sector, Luint8 * pu8Array, Luint16 u16Length);

	#endif //C_LOCALDEF__LCCM135__ENABLE_F021

	#ifndef C_LOCALDEF__LCCM135__ENABLE_F021
		#error
	#endif

	#endif //C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE

#endif //_RM4_FLASH_H_
