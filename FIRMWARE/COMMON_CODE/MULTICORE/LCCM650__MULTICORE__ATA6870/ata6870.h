/**
 * @file		ATA6870.H
 * @brief		Main header file of public functions and structures for the ATA6870 driver
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.001
 */

#ifndef _ATA6870_H_
#define _ATA6870_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

		#include <MULTICORE/LCCM650__MULTICORE__ATA6870/ata6870__register_defs.h>
	
	
		/*******************************************************************************
		Defines
		*******************************************************************************/
		
		/** Internal Vref Voltage */
		#define C_ATA6870__VREF_V				(1.6667F)
		
		/** Burst transfer length, NEVER modify this */
		#define C_ATA6870__BUSRT_LENGTH				(14U)
		
		/** max number of monitored cells */
		#define C_ATA6870__MAX_CELLS				(6U)
		
		/** Voltage input measurement resolution in VOLTS */
		#define C_ATA6870__ADC_RES_V				(0.0015F)
		

		/** Balancer Stats */
		typedef enum
		{

			/** not doing anything, waiting for a start command*/
			BALANCE_STATE__IDLE = 0U


		}E_ATA6870__BALANCE_STATE_T;


		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _str6870
		{

			/** Balancing control state machine */
			struct
			{
				E_ATA6870__BALANCE_STATE_T eState;

			}sBalance;

			/** Structure for each individual device in the chain */
			struct
			{
				/** Interrupt support */
				struct
				{
					/** The status of the last device ID command where the IRQ status is returned
					as part of the ID phase of the SPI transaction */
					Luint16 u16IRQ_Status;
				
				}sIRQ;
		
			}sDevice[C_LOCALDEF__LCCM650__NUM_DEVICES];

			/** NTC Temperature Reading **/
			Lfloat32 f32NTCTemperatureReading[C_LOCALDEF__LCCM650__NUM_DEVICES];

			/** Voltages of a battery pack **/
			Lfloat32 f32Voltage[C_LOCALDEF__LCCM650__NUM_6P_MODULES];
		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vATA6870__Init(void);
		void vATA6870__Process(void);
		
		//balance control
		void vATA6870_BALANCE__Init(void);
		void vATA6870_BALANCE__Start(void);
		void vATA6870_BALANCE__Stop(void);
		Luint8 u8ATA6870_BALANCE__Is_Busy(void);
		void vATA6870_BALANCE__Process(void);

		//lowlevel
		void vATA6870_LOWLEVEL__Init(void);
		void vATA6870_LOWLEVEL__Reg_WriteU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length);
		void vATA6870_LOWLEVEL__Reg_ReadU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length);
		void vATA6870_LOWLEVEL__PowerOn(void);
		void vATA6870_LOWLEVEL__PowerOff(void);
		Luint8 u8ATA6870_LOWLEVEL__Get_PowerAvail(void);

		//cells
		void vATA6870_CELL__Get_Voltages(Luint8 u8DeviceIndex, Lfloat32 *pf32Voltages, Lfloat32 *pF32Temperature);
		
		//device scanning
		void vATA6870_SCAN__Start(void);

		//resisotr control
		void vATA6870_RES__TurnOn(Luint8 u8DeviceIndex, Luint8 u8CellIndex);
		void vATA6870_RES__TurnOff(Luint8 u8DeviceIndex, Luint8 u8CellIndex);
		void vATA6870_RES__TurnAllOff(Luint8 u8DeviceIndex);
		
		//undervoltage detection
		void vATA6870_UV__Set_UVTrip(Luint8 u8DeviceIndex, Lfloat32 f32Value);
		
		//status
		Luint8 u8ATA6870_STATUS__Get_Op_Status(Luint8 u8DeviceIndex);
		Luint8 u8ATA6870_STATUS__Get_IRQ_Status(Luint8 u8DeviceIndex);
		
		//interrupts
		void vATA6870_INT__Init(void);
		void vATA6870_INT__ISR(Luint8 u8DeviceIndex);
		
	//safetys
	#ifndef C_LOCALDEF__LCCM650__NUM_DEVICES
		#error
	#endif
		
	#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_ATA6870_H_

