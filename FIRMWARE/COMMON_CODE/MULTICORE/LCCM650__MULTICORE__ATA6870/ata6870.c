/**
 * @file		ATA6870.C
 * @brief		Top level file for the ATA6870N device
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__CORE
 * @ingroup ATA6870
 * @{ */

#include "ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
struct _str6870 sATA6870;

//locals
static void vATA6870__StartConversion(Luint8 u8VoltageMode, Luint8 u8TempBit);


/***************************************************************************//**
 * @brief
 * Init any ATA6870 systems
 * 
 * @st_funcMD5		DD75420783FCC074EFEE1B22E4564570
 * @st_funcID		LCCM650R0.FILE.000.FUNC.001
 */
void vATA6870__Init(void)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/ 
	Luint8 u8Counter;
	Luint8 u8Counter2;
	Luint8 u8Temp;

	sATA6870.u32VoltsUpdateCount = 0U;

	//Init NTC Temp reading and Voltages
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		sATA6870.f32NTCTemperatureReading[u8Counter] = 0;
	}

	//clear cell specifics
	for(u8Counter = 0U; u8Counter < C_ATA6870__TOTAL_CELLS; u8Counter++)
	{
		sATA6870.f32Voltage[u8Counter] = 0.0F;

		#if C_LOCALDEF__LCCM650__AVERAGE_WINDOW > 0
			sATA6870.f32FiltVoltage[u8Counter] = 0.0F;
			sATA6870.u16AverageCounter[u8Counter] = 0U;

			for(u8Counter2 = 0U; u8Counter2 < C_LOCALDEF__LCCM650__AVERAGE_WINDOW; u8Counter2++)
			{
				sATA6870.f32VoltagesBuffer[u8Counter][u8Counter2] = 0.0F;
			}

		#endif //C_LOCALDEF__LCCM650__AVERAGE_WINDOW
	}


	sATA6870.eState = ATA6870_STATE__INIT_DEVICE;
	sATA6870.f32AverageCellVoltage = 0.0F;
	sATA6870.f32PackVoltage = 0.0F;
	sATA6870.u8AverageUpdated = 0U;

	//setup the lowlevel
	vATA6870_LOWLEVEL__Init();
	
	//setup the interrupts
	vATA6870_INT__Init();

	//init the blancer subsystem
	vATA6870_BALANCE__Init();
	
	//star the scanner
	vATA6870_SCAN__Init();

	//switch on
	vATA6870_LOWLEVEL__PowerOn();

	//delay a bit for things to settle
	vRM4_DELAYS__Delay_mS(100U);



	/*lint +e934*/ 

}

/***************************************************************************//**
 * @brief
 * Process any ATA6870 tasks
 * 
 * @st_funcMD5		CC6F99350533FEAE2044081BD632EF21
 * @st_funcID		LCCM650R0.FILE.000.FUNC.002
 */
void vATA6870__Process(void)
{

	Lint16 s16Return;
	Luint8 u8Counter;
	Luint8 u8Temp;

	//handle the state machine
	switch(sATA6870.eState)
	{
		case ATA6870_STATE__IDLE:
			//do nothing,
			break;

		case ATA6870_STATE__INIT_DEVICE:

			//setup and get the basic BMS pods operational
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
			{

				//setup the control register with CRC or not
				#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
					u8Temp = 0x10U;
				#else
					u8Temp = 0x00U;
				#endif
				vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__CONTROL, &u8Temp, 1U);

				//setup the interupts
				//Only do the important onces for now
				//TODO do we need to mask undervoltage?
				u8Temp = 0x16U;
				vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__IRQ_MASK, &u8Temp, 1U);

				//Other house keeping issues:
				//Todo
				//1. Check under voltage issues
				//2. Check comms actually works.

			}//for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)

			//u8Temp = 0x01U;
			//vATA6870_LOWLEVEL__Reg_WriteU8(0U, ATA6870_REG__OPERATION, &u8Temp, 1U);


			//make sure we have our devices
			vATA6870_SCAN__Start();

			sATA6870.eState = ATA6870_STATE__START_CONVERSION;
			break;

		case ATA6870_STATE__START_CONVERSION:

			//start the conversion and enable temperature and voltage conversions on all devices
			vATA6870__StartConversion(1U, 1U);

			//clear the counter
			sATA6870.u32ISR_Counter = 0U;

			//change state
			sATA6870.eState = ATA6870_STATE__WAIT_CONVERSION;
			break;

		case ATA6870_STATE__WAIT_CONVERSION:

			// 8.2ms conversion time according to datasheet
			if(sATA6870.u32ISR_Counter > 2U)
			{
				//go and read the voltages now
				sATA6870.eState = ATA6870_STATE__READ_CELL_VOLTAGES;
			}
			else
			{
				//wait here.
			}
			break;

		case ATA6870_STATE__READ_CELL_VOLTAGES:
			//do a read of all volts and temps in the device
			s16Return = s16ATA6870_CELL__BulkRead_All();

			//clear the filtering channel.
			sATA6870.u16FilteringChannel = 0U;

			sATA6870.eState = ATA6870_STATE__RUN_FILTERING;
			break;


		case ATA6870_STATE__RUN_FILTERING:

			//run the filtering if we are enabled.

			#if C_LOCALDEF__LCCM650__AVERAGE_WINDOW > 0U

				//do the filtering
				sATA6870.f32FiltVoltage[sATA6870.u16FilteringChannel] = f32NUMERICAL_FILTERING__Add_F32(sATA6870.f32Voltage[sATA6870.u16FilteringChannel],
																									&sATA6870.u16AverageCounter[sATA6870.u16FilteringChannel],
																									C_LOCALDEF__LCCM650__AVERAGE_WINDOW,
																									&sATA6870.f32VoltagesBuffer[sATA6870.u16FilteringChannel][0]);
				if(sATA6870.u16FilteringChannel < (C_ATA6870__TOTAL_CELLS - 1))
				{
					sATA6870.u16FilteringChannel++;
				}
				else
				{
					//go an create the sum of all voltages.
					sATA6870.eState = ATA6870_STATE__SUM_CELL_VOLTAGES;
				}

			#else
				//go an create the sum of all voltages.
				sATA6870.eState = ATA6870_STATE__SUM_CELL_VOLTAGES;
			#endif


			break;

		case ATA6870_STATE__SUM_CELL_VOLTAGES:
			//sum the cell voltages together.
			vATA6870_CELL__Sum_CellVoltages();

			//generate the cell voltage average
			sATA6870.eState = ATA6870_STATE__AVERAGE_CELL_VOLTAGES;

			break;

		case ATA6870_STATE__AVERAGE_CELL_VOLTAGES:

			//create the average.
			vATA6870_CELL__Average_CellVoltages();

			//inc the counter
			sATA6870.u32VoltsUpdateCount++;

			//go back and do another conversion
			sATA6870.eState = ATA6870_STATE__START_CONVERSION;
			break;

		default:
			//todo:
			break;

	}//switch(sATA6870.eState)

	//process any balancer tasks.
	vATA6870_BALANCE__Process();


}


/***************************************************************************//**
 * @brief
 * Start ATA6870N Conversion
 *
 * @param[in]		u8TempBit				Enable temp measurement
 * @param[in]		u8VoltageMode			Enable volt measurement
 */
void vATA6870__StartConversion(Luint8 u8VoltageMode, Luint8 u8TempBit)
{
	// loop counter
	Luint8 u8Counter;
	// Temporary Data
	Luint8 u8TempData;
	Luint8 u8Status;
	Luint8 u8Op;

	// start conversion by clearing out any existing commands and issuing our own
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		//Clear any existing interrupts on each device
		u8Status = u8ATA6870_STATUS__Get_IRQ_Status(u8Counter);

		// check and clear existing commands
		u8Op = u8ATA6870_STATUS__Get_Op_Status(u8Counter);
		if(u8Op != 0U)
		{
			//OpClear
			u8TempData = 0x00U;

			//clear existing command
			vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__OPERATION, &u8TempData, 1U);

			vRM4_DELAYS__Delay_mS(5U);

			//Get Status
			u8Status = u8ATA6870_STATUS__Get_IRQ_Status(u8Counter);

			//Get Op Status
			u8Status = u8ATA6870_STATUS__Get_Op_Status(u8Counter);
		}
		else
		{
			//todo:
		}

		//Op Req Data
		u8TempData = (0x01 | (u8VoltageMode << 1) | (u8TempBit << 3));

		//Start Conversion
		vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__OPERATION, &u8TempData, 1U);

	}//for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)


}

Luint32 u32ATA6870__Get_VoltsUpdateCount(void)
{
	return sATA6870.u32VoltsUpdateCount;
}

/***************************************************************************//**
 * @brief
 * 10ms ISR
 *
 * @st_funcMD5		EFCD04EB2C2B91C6325DB0C8D146E16B
 * @st_funcID		LCCM644R0.FILE.000.FUNC.004
 */
void vATA6870__10MS_ISR(void)
{
	//inc the count of 10ms interrupts.
	sATA6870.u32ISR_Counter++;
}

//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_CRC
	#error
#endif

#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif

