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
		#define C_ATA6870__VREF_V					(1.6667F)
		
		/** Burst transfer length, NEVER modify this */
		#define C_ATA6870__BUSRT_LENGTH				(14U)
		
		/** max number of monitored cells */
		#define C_ATA6870__MAX_CELLS				(6U)
		
		/** The total number of cells managed by the ATA device */
		#define C_ATA6870__TOTAL_CELLS				(C_LOCALDEF__LCCM650__NUM_DEVICES * C_ATA6870__MAX_CELLS)


		/** Voltage input measurement resolution in VOLTS */
		#define C_ATA6870__ADC_RES_V				(0.00152656F)

		/** Voltage thresholds for each module, CHANGE IF NEEDED*/
		#define C_ATA6870__MIN_VOLTS				(3.5)
		#define C_ATA6870__MAX_VOLTS				(4.3)

		/** mV Offset
		 * CONSIDER: Do not change this*/
		#define C_ATA6870__OFFSET_VOLTAGE 			(410.0F)

		/** Max ATA devices on any one bus */
		#define C_ATA6870__MAX_BUS_DEVICES			(16U)

		/** Balancer Stats */
		typedef enum
		{

			/** not doing anything, waiting for a start command*/
			BALANCE_STATE__IDLE = 0U,

			/** Wait for a voltage update before starting balancing */
			BALANCE_STATE__WAIT_VOLTAGE_UPDATE,

			/** Start the balancing process */
			BALANCE_STATE__START_BALANCING,

			/** Check to see if we are balanced	 */
			BALANCE_STATE__CHECK_BALANCED,

			/** balancing has completed */
			BALANCE_STATE__BALANCED

		}E_ATA6870__BALANCE_STATE_T;

		/** State types for the ATA6870N state machine */
		typedef enum
		{
			ATA6870_STATE__IDLE = 0U,
			ATA6870_STATE__ERROR,
			ATA6870_STATE__INIT_DEVICE,
			ATA6870_STATE__START_CONVERSION,
			ATA6870_STATE__WAIT_CONVERSION,
			ATA6870_STATE__READ_CELL_VOLTAGES,
			ATA6870_STATE__RUN_FILTERING,

			ATA6870_STATE__SUM_CELL_VOLTAGES,
			ATA6870_STATE__AVERAGE_CELL_VOLTAGES,

			ATA6870_STATE__INTERRUPT,
			
		}E_ATA6870_STATE_T;


		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _str6870
		{
			E_ATA6870_STATE_T eState;

			/** A list of all revision ID's found on each bus */
			Luint8 u8RevID[C_ATA6870__MAX_BUS_DEVICES];

			/** Balancing control state machine */
			struct
			{
				/** The current balancing state */
				E_ATA6870__BALANCE_STATE_T eState;

				/** Total number of cells allowed to be balanced at any one time
				 * this will reduce thermal load on the BMS boards.
				 * NOTE: This value is the number of cells per ATA device, not in total.
				 */
				Luint8 u8MaxBalanceCells;

				/** The state of the resistors so we don't flood the SPI */
				Luint8 u8ResistorOn[C_ATA6870__TOTAL_CELLS];

				/** The tolerance in volts betwen the average and considering a cell needing balancing */
				Lfloat32 f32BalanceTolerance;

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


			/** Voltages of a complete battery pack **/
			Lfloat32 f32Voltage[C_ATA6870__TOTAL_CELLS];

			#if C_LOCALDEF__LCCM650__AVERAGE_WINDOW > 0U

				/** buffers of the filtered voltages */
				Lfloat32 f32VoltagesBuffer[C_ATA6870__TOTAL_CELLS][C_LOCALDEF__LCCM650__AVERAGE_WINDOW];

				/** The filter position */
				Luint16 u16AverageCounter[C_ATA6870__TOTAL_CELLS];

				/** The filtered voltage */
				Lfloat32 f32FiltVoltage[C_ATA6870__TOTAL_CELLS];

			#else

			#endif

			/** just a counter for the number of times the volts have been re-read*/
			Luint32 u32VoltsUpdateCount;

			/** Current filtering channel */
			Luint16 u16FilteringChannel;

			/** Total battery pack voltage */
			Lfloat32 f32PackVoltage;

			/** The average pack cell voltage */
			Lfloat32 f32AverageCellVoltage;

			/** The average has been updated, cleared in the balancer */
			Luint8 u8AverageUpdated;

			/** The count of 10ms ISR's*/
			Luint32 u32ISR_Counter;
		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vATA6870__Init(void);
		void vATA6870__Process(void);
		void vATA6870__10MS_ISR(void);
		Luint32 u32ATA6870__Get_VoltsUpdateCount(void);
		
		//balance control
		void vATA6870_BALANCE__Init(void);
		void vATA6870_BALANCE__Start(void);
		void vATA6870_BALANCE__Stop(void);
		Luint8 u8ATA6870_BALANCE__Is_Busy(void);
		void vATA6870_BALANCE__Process(void);
		void vATA6870_BALANCE__Manual(Luint8 u8CellIndex, Luint8 u8Enable);

		//lowlevel
		void vATA6870_LOWLEVEL__Init(void);
		void vATA6870_LOWLEVEL__Reg_WriteU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length);
		void vATA6870_LOWLEVEL__Reg_ReadU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length);
		void vATA6870_LOWLEVEL__PowerOn(void);
		void vATA6870_LOWLEVEL__PowerOff(void);
		Luint8 u8ATA6870_LOWLEVEL__Get_PowerAvail(void);

		//cells
		void vATA6870_CELL__Get_Voltages(Luint8 u8DeviceIndex, Lfloat32 *pf32Voltages, Lfloat32 *pF32Temperature);
		Lint16 s16ATA6870_CELL__BulkRead_All(void);
		void vATA6870_CELL__Average_CellVoltages(void);
		void vATA6870_CELL__Sum_CellVoltages(void);
		Lfloat32 f32ATA6870_CELL__Get_PackVoltage(void);
		Lint16 s16ATA6870_CELL__Check_CellVoltageError(Lfloat32 *pf32Voltages);
		Lfloat32 f32ATA6870_CELL__Get_HighestVoltage(void);
		Lfloat32 f32ATA6870_CELL__Get_LowestVoltage(void);
		
		//device scanning
		void vATA6870_SCAN__Start(void);
		void vATA6870_SCAN__Init(void);

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

