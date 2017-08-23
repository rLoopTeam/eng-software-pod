/**
 * @file		BQ76.H
 * @brief		Main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.001
 */

#ifndef _BQ76_H_
#define _BQ76_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__fault_flags.h>
		#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__device_fault_flags.h>
		#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__reg_defs.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/

		/** Max number of cells managed by this device, do not change */
		#define C_BQ76__MAX_CELLS_PER_DEVICE										(6U)

		/** The total number of cells managed by the device chain */
		#define C_BQ76__TOTAL_CELLS													(C_LOCALDEF__LCCM715__NUM_DEVICES * C_BQ76__MAX_CELLS_PER_DEVICE)

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

		}TE_BQ76__BALANCE_STATE_T;


		/** State types for the BQ76 state machine */
		typedef enum
		{
			BQ76_STATE__IDLE = 0U,
			BQ76_STATE__ERROR,
			BQ76_STATE__INIT_DEVICE,
			BQ76_STATE__START_CONVERSION,
			BQ76_STATE__WAIT_CONVERSION,
			BQ76_STATE__READ_CELL_VOLTAGES,
			BQ76_STATE__RUN_FILTERING,

			BQ76_STATE__SUM_CELL_VOLTAGES,
			BQ76_STATE__AVERAGE_CELL_VOLTAGES,

			BQ76_STATE__INTERRUPT,

		}TE_BQ76__STATE_T;
		
		/** The cell level sampling state machine */
		typedef enum
		{
			
			/** Idle state */
			CELLS_STATE__IDLE = 0U,
			
			/** Start the conversion */
			CELLS_STATE__START_CONVERT,
			
			/** Wait for the conversion to complete */
			CELLS_STATE__WAIT_CONVERT,
			
			/** Read the cell voltages */
			CELLS_STATE__READ_VOLTS,
			
			/** Convert raw to voltages */
			CELLS_STATE__CONVERT_VOLTS,
			
			/** Do any filtering as needed */
			CELLS_STATE__RUN_AVERAGER,

			/** Compute the min/max volts */
			CELLS_STATE__COMPUTE_MIN_MAX,

			/** Compute the battery */
			CELLS_STATE__COMPUTE_BATTERY,

			
		}TE_BQ76__CELLS_STATE;

		/*******************************************************************************
		Structures
		*******************************************************************************/
		typedef struct
		{

			/** The main state machine */
			TE_BQ76__STATE_T eState;

			/** Battery pack structure */
			struct
			{
				/** The computed pack voltage */
				Lfloat32 f32PackVoltage;

			}sBattery;

			/** Balance Control */
			struct
			{

				/** Resistor control state for the balancer */
				Luint8 u8Resistor[C_BQ76__TOTAL_CELLS];

				/** Hit every 10ms by the ISR **/
				/** Used to update the discharge resistor status **/
				Luint32 u3210MS_Counter;

			}sBalance;


			/** Individual Cells */
			struct
			{
				/** Individual cell voltages */
				Lfloat32 f32CellVoltage;

				#if C_LOCALDEF__LCCM715__AVERAGE_WINDOW > 0U
					/** buffers of the filtered voltages */
					Lfloat32 f32VoltagesBuffer[C_LOCALDEF__LCCM715__AVERAGE_WINDOW];

					/** The filter position */
					Luint16 u16AverageCounter;

					/** The filtered voltage */
					Lfloat32 f32FiltVoltage;
				#else
					//nothing here
				#endif

			}sCell[C_BQ76__TOTAL_CELLS];


			/** Cell handling system */
			struct
			{
				
				/** Cell level state machine */
				TE_BQ76__CELLS_STATE sState;
				
				/** Count of 10ms interrupts */
				Luint32 u3210MS_Counter;
				
				/** Highest cell voltage */
				Lfloat32 f32Highest;

				/** Lowest cell voltage */
				Lfloat32 f32Lowest;

				/** Number of times state machine has read cells */
				Luint32 u32UpdateCount;

			}sCells;
			
			/** The individual devices */
			struct
			{

				/** Individual device fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** Raw Read Array for Volts */
				Luint8 u8RawVoltArray[C_BQ76__MAX_CELLS_PER_DEVICE * 2U];
				
			}sDevice[C_LOCALDEF__LCCM715__NUM_DEVICES];
			
		}TS_BQ76__MAIN;

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vBQ76__Init(void);
		void vBQ76__Process(void);
		Lfloat32 f32BQ76__Get_CellVoltage(Luint8 u8CellIndex);
		void vBQ76__10MS_ISR(void);
		Luint32 u32BQ76__Get_FaultFlags(Luint8 u8DeviceIndex);
		Luint32 u32BQ76__Get_VoltsUpdateCount(void);

		//balance control
		void vBQ76_BALANCE__Init(void);
		void vBQ76_BALANCE__Process(void);
		void vBQ76_BALANCE__Start(void);
		Luint8 u8BQ76_BALANCE__Is_Busy(void);
		void vBQ76_BALANCE__Stop(void);
		void vBQ76_BALANCE__Manual(Luint8 u8CellIndex, Luint8 u8Enable);
		void vBQ76_BALANCE__Update_Discharge_Resistors(void);
		void vBQ76_BALANCE__10MS_ISR(void);

		//battery pack calculations
		void vBQ76_BATTERY__Init(void);
		void vBQ76_BATTERY__Process(void);
		Lfloat32 f32BQ76_BATTERY__Get_PackVoltage(void);
		void vBQ76_BATTERY__Compute_PackVoltage(void);

		//cell level functions
		void vBQ76_CELLS__Init(void);
		void vBQ76_CELLS__Process(void);
		void vBQ76_CELLS__10MS_ISR(void);
		Lfloat32 f32BQ76_CELLS__Compute_CellVoltage(Luint8 u8HighByte, Luint8 u8LowByte);
		Lfloat32 f32BQ76_CELLS__Get_HighestVoltage(void);
		Lfloat32 f32BQ76_CELLS__Get_LowestVoltage(void);

		//resistors
		void vBQ76_RES__Init(void);
		void vBQ76_RES__Process(void);
		void vBQ76_RES__Resistor_On(Luint8 u8CellIndex);
		void vBQ76_RES__Resistor_Off(Luint8 u8CellIndex);
		void vBQ76_RES__Resistors_Update(void);
		void vBQ76_RES__All_Off(void);

		//CRC
		Luint8 u8BQ76_CRC__Compute(Luint8 *pu8Buffer, Luint8 u8Length);

		//SPI interface
		void vBQ76_SPI__Init(void);
		void vBQ76_SPI__Process(void);
		void vBQ76_SPI__Reset_All(void);
		Luint8 u8BQ76_SPI__Read_U8(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg);
		void vBQ76_SPI__Write_U8(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg, Luint8 u8Value);
		void vBQ76_SPI__Read_U8_Array(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg, Luint8 *pu8Data, Luint8 u8Length);


	#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_BQ76_H_S

