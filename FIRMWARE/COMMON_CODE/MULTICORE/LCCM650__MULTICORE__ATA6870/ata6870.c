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
extern struct _str6870 sATA6870;
extern struct _strPWRNODE sPWRNODE;

//locals
static Luint8 u8ATA6870__BulkRead(void);
static void vATA6870__StartConversion(Luint8 u8VoltageMode, Luint8 u8TempBit);


/***************************************************************************//**
 * @brief
 * Init any ATA6870 systems
 * 
 * @st_funcMD5		99D6BF2EA733AE85B32BE7F078646C43
 * @st_funcID		LCCM650R0.FILE.000.FUNC.001
 */
void vATA6870__Init(void)
{
	//Taking address of near auto variable, reviewed
	/*lint -e934*/ 
	Luint8 u8Counter;
	Luint8 u8Temp;

	//Init NTC Temp reading and Voltages
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		sPWRNODE.sATA6870.sDevice[u8Counter].pf32Temperature = 0;
		for(u8ModuleCounter = 0U; u8Counter < C_ATA6870__MAX_CELLS; u8ModuleCounter++)
		{
			sPWRNODE.sATA6870.sDevice[u8Counter].f32Voltage[u8ModuleCounter] = 0;
		}
	}

	sATA6870.eState = ATA6870_STATE__INIT_DEVICE;

	//setup the lowlevel
	vATA6870_LOWLEVEL__Init();
	
	//setup the interrupts
	vATA6870_INT__Init();

	//init the blancer subsystem
	vATA6870_BALANCE__Init();
	
	//switch on
	vATA6870_LOWLEVEL__PowerOn();

	//delay a bit for things to settle
	vRM4_DELAYS__Delay_mS(100U);

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

	}

	//u8Temp = 0x01U;
	//vATA6870_LOWLEVEL__Reg_WriteU8(0U, ATA6870_REG__OPERATION, &u8Temp, 1U);


	//make sure we have our devices
	vATA6870_SCAN__Start();

	/*lint +e934*/ 

}

/***************************************************************************//**
 * @brief
 * Process any ATA6870 tasks
 * 
 * @st_funcMD5		B36C2CF202BFF0A45AD77EE21E6F3822
 * @st_funcID		LCCM650R0.FILE.000.FUNC.002
 */
void vATA6870__Process(void)
{
	switch(sATA6870.eState)
	{
		case ATA6870_STATE__IDLE:
			//do nothing,
			break;
		case ATA6870_STATE__INIT_DEVICE:
			sATA6870.eState = ATA6870_STATE__START_CONVERSION;
			break;
		case ATA6870_STATE__START_CONVERSION:
			vATA6870__StartConversion(1U, 1U);
			sATA6870.eState = ATA6870_STATE__WAIT_CONVERSION;
			break;
		case ATA6870_STATE__WAIT_CONVERSION:
			// 8.2ms conversion time according to datasheet
			if(sATA6870.u32ISR_Counter > 1U)
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
			u8ATA6870__BulkRead();
			sATA6870.eState = ATA6870_STATE__START_CONVERSION;
			break;
	}

	//process any balancer tasks.
	vATA6870_BALANCE__Process();
}


/***************************************************************************//**
 * @brief
 * Start ATA6870N Conversion
 *
 * @st_funcMD5
 * @st_funcID
 */
void vATA6870__StartConversion(Luint8 u8VoltageMode, Luint8 u8TempBit)
{
	Luint8 u8Counter;						// loop counter
	Luint8 u8TempData;						// Temporary Data

	// start conversion by clearing out any existing commands and issuing our own
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		//Clear any existing interrupts
		u8ATA6870_STATUS__Get_IRQ_Status(u8Counter);

		// check and clear existing commands
		if (u8ATA6870_STATUS__Get_Op_Status(u8Counter) != 0U)
		{
			//OpClear
			u8TempData = 0x00U;

			//clear existing command
			vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__OPERATION, &u8TempData, 1U);

			vRM4_DELAYS__Delay_mS(5U);

			//Get Status
			u8ATA6870_STATUS__Get_IRQ_Status(u8Counter);

			//Get Op Status
			u8ATA6870_STATUS__Get_Op_Status(u8Counter);
		}

		//Op Req Data
		u8TempData = (0x01 | (u8VoltageMode << 1) | (u8TempBit << 3));
		//Start Conversion
		vATA6870_LOWLEVEL__Reg_WriteU8(u8Counter, ATA6870_REG__OPERATION, &u8TempData, 1U);
	}

	//clear the counter
	sATA6870.u32ISR_Counter = 0U;
}

/***************************************************************************//**
 * @brief
 * bulk read voltages: 6 voltages, 1 temperature
 *
 * @st_funcMD5
 * @st_funcID
 */
Luint8 u8ATA6870__BulkRead(void)
{
	// volt mode = calibration or regular acquisition. 0 for calibration, 1 for regular.
	// tempBit = temperature sensor to select. 1 for internal, 0 for external.


	Luint8 u8Counter;						// loop counter
	Luint8 u8BulkReadError = 0U;			// error flag

	// read data
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		// get voltages for the current device
		vATA6870_CELL__Get_Voltages(u8Counter,
									&sPWRNODE.sATA6870.sDevice[u8Counter].pf32Voltages[0],
									&sPWRNODE.sATA6870.sDevice[u8Counter].pf32Temperature);
		// move to next device
	}
	// check if any cells are dead or out of threshold
	u8BulkReadError = u8ATA6870__u8VoltageError(&sPWRNODE.sATA6870.sDevice[0].pf32Voltages[0]);

	return u8BulkReadError;
}

//*** check if a cell is above or below safe threshold ***//
//TODO: if we use UNDER_VOLT function instead, be sure to implement
//      an upper bound check as well for over voltage
// Lfloat32 *f32Voltages					voltages array of size C_ATA6870__MAX_CELLS
Luint8 u8ATA6870__u8VoltageError(Lfloat32 *pf32Voltages)
{
	Luint8 u8VoltageError = 0U;
	Luint8 u8Counter;

	// check each voltage is within threshold
	for (u8Counter = 0U; u8Counter < C_ATA6870__MAX_CELLS; u8Counter++)
	{
		if (pf32Voltages[u8Counter] > C_ATA6870_MAX_VOLTS)
		{
			// log voltage error
			// TODO: standardize error codes
			u8VoltageError = 1;
		}
		else if (pf32Voltages[u8Counter] < C_ATA6870_MIN_VOLTS)
		{
			// log voltage error
			// TODO: standardize error codes
			u8VoltageError = 2;
		}
		else
		{
			// fall through
		}
	}
	return u8VoltageError;
}
/***************************************************************************//**
 * @brief
 * 10ms ISR
 *
 * @st_funcMD5		2EFF2F9513ECDACF63F2615A2C620299
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

