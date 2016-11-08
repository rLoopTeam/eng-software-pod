/**
 * @file		RM4_RTI__PRIVATE.H
 * @brief		Private decs for the RTI system
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM124R0.FILE.004
 */

 #ifndef RM4_RTI__PRIVATE_H_
#define RM4_RTI__PRIVATE_H_

		/*STRUCTURES*/
		typedef volatile struct rtiBase
		{
			/*0x0000: Global Control Register */
			Luint32 GCTRL;
			/*0x0004: Timebase Control Register */
			Luint32 TBCTRL;
			/*0x0008: Capture Control Register */
			Luint32 CAPCTRL;
			/*0x000C: Compare Control Register */
			Luint32 COMPCTRL;
			
			 /*Counter x selection:
			- 0: Counter 0
			- 1: Counter 1
			*/
			struct
			{
				/*0x0010,0x0030: Free Running Counter x Register */
				Luint32 FRCx
				/*0x0014,0x0034: Up Counter x Register */;
				Luint32 UCx;
				/*0x0018,0x0038: u32Compare Up Counter x Register */
				Luint32 CPUCx;
				/*0x001C,0x003C: Reserved */
				Luint32 : 32;
				/*0x0020,0x0040: Capture Free Running Counter x Register */
				Luint32 CAFRCx
				/*0x0024,0x0044: Capture Up Counter x Register */;
				Luint32 CAUCx;
				/*0x0028,0x0048: Reserved */
				Luint32 : 32;
				/*0x002C,0x004C: Reserved */
				Luint32 : 32;
			} CNT[2U];
			
			/*Compare x selection:
			- 0: u32Compare 0
			- 1: u32Compare 1
			- 2: u32Compare 2
			- 3: u32Compare 3
			*/
			struct
			{
				/*0x0050,0x0058,0x0060,0x0068: u32Compare x Register */
				Luint32 COMPx;
				/*0x0054,0x005C,0x0064,0x006C: Update u32Compare x Register */
				Luint32 UDCPx;
			} CMP[4U];
			
			Luint32 TBLCOMP;		/*0x0070: External Clock Timebase Low u32Compare Register */
			Luint32 TBHCOMP;		/*0x0074: External Clock Timebase High u32Compare Register */
			Luint32 : 32;		 /*0x0078: Reserved */
			Luint32 : 32;		 /*0x007C: Reserved */
			Luint32 SETINT;		 /*0x0080: Set/Status Interrupt Register */
			Luint32 CLEARINT;	 /*0x0084: Clear/Status Interrupt Register */
			Luint32 INTFLAG;		/*0x0088: Interrupt Flag Register */
			Luint32 : 32;		 /*0x008C: Reserved	 */
			Luint32 DWDCTRL;		/*0x0090: Digital Watchdog Control Register */
			Luint32 DWDPRLD;		/*0x0094: Digital Watchdog Preload Register */
			Luint32 WDSTATUS;	 /*0x0098: Watchdog Status Register */
			Luint32 WDKEY;		 /*0x009C: Watchdog Key Register */
			Luint32 DWDCNTR;		/*0x00A0: Digital Watchdog Down Counter */
			Luint32 WWDRXNCTRL;	 /*0x00A4: Digital Windowed Watchdog Reaction Control */
			Luint32 WWDSIZECTRL;	/*0x00A8: Digital Windowed Watchdog Window Size Control */
			Luint32 INTCLRENABLE; /*0x00AC: RTI u32Compare Interrupt Clear Enable Register */
			Luint32 COMP0CLR;	 /*0x00B0: RTI u32Compare 0 Clear Register */
			Luint32 COMP1CLR;	 /*0x00B4: RTI u32Compare 1 Clear Register */
			Luint32 COMP2CLR;	 /*0x00B8: RTI u32Compare 2 Clear Register */
			Luint32 COMP3CLR;	 /*0x00BC: RTI u32Compare 3 Clear Register */

		} RM4_RTI__BASE_T;

		//our register
		#define rtiREG1 ((RM4_RTI__BASE_T *)0xFFFFFC00)

		/** @enum dwdViolationTag
		* @brief DWD Violations
		*/
		typedef enum
		{
			DWD_VIOLATION__NO_TIME = 0U,
			DWD_VIOLATION__TIME_WINDOW = 1U,
			DWD_VIOLATION__ENDTIME_WINDOW = 2U,
			DWD_VIOLATION__STARTTIME_WINDOW = 3U,
			DWD_VIOLATION__KEY_SEQUENCE = 4U
			
		}RM4_RTI_DWD__VIOLATION_T;

		/* USER CODE BEGIN (2) */
		/* USER CODE END */

		/** @enum dwdResetStatusTag
		* @brief DWD Reset status
		*/
		typedef enum
		{
			DWD_RESET_STATUS__NO_RESET = 0U,
			DWD_RESET_STATUS__RESET_GENERATED	= 1U
		}RM4_RTI_DWD__RESET_STATUS_T;

		/* USER CODE BEGIN (3) */
		/* USER CODE END */

		/** @enum dwwdReactionTag
		* @brief DWWD Reaction on vioaltion
		*/
		typedef enum
		{
			DWD_REACTION__RESET = 0x00000005U,
			DWD_VIOLATION__NMI = 0x0000000AU
		}RM4_RTI_DWD__REACTION_T;

		/* USER CODE BEGIN (4) */
		/* USER CODE END */

		/** @enum dwwdWindowSizeTag
		* @brief DWWD Window size
		*/
		typedef enum
		{
			DWD_WINDOW__100_PERCENT = 0x00000005U,
			DWD_WINDOW__50_PERCENT	= 0x00000050U,
			DWD_WINDOW__25_PERCENT	= 0x00000500U,
			DWD_WINDOW__12_5_PERCENT = 0x00005000U,
			DWD_WINDOW__6_25_PERCENT = 0x00050000U,
			DWD_WINDOW__3_125_PERCENT = 0x00500000U
			
		}RM4_RTI_DWD__WINDOW_SIZE_T;


#endif //RM4_RTI__PRIVATE_H_

