/**
 * @file		MMA8451__LOCALDEF.H
 * @brief		mma8451 localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM418R0.FILE.015
 */

#if 0

/*******************************************************************************
SIL3 - MMA8451 3 AXIS ACCELEROMETER
*******************************************************************************/
	#define C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE == 1U

		//Define the number of MMA8451's that are on the I2C Chain (MAX = 2)
		//Limit if 2 is due to addx pin limit
		//for 4 devices, two chains will be used, the second for device 2,3
		#define C_LOCALDEF__LCCM418__NUM_DEVICES							(1U)

		#define C_LOCALDEF__LCCM418__DELAY_US(x)							vRM4_DELAYS__Delay_uS(x)

		/** The max number of process loops without seeing an interrupt before we raise a flag. */
		#define C_LOCALDEF__LCCM418__MAX_INTERRUPT_LOST_COUNT				(100000U)

		/** set to 1 to use interrupts, not polling method */
		#define C_LOCALDEF__LCCM418__USE_INTERRUPT_DEV0						(0U)
		#define C_LOCALDEF__LCCM418__USE_INTERRUPT_DEV1						(0U)
		#define C_LOCALDEF__LCCM418__USE_INTERRUPT_DEV2						(0U)
		#define C_LOCALDEF__LCCM418__USE_INTERRUPT_DEV3						(0U)
		
		/** Force interrupt pin on, but do not use interrupts 
		This will be used if you just want data ready available on the IO pin
		but would perform a manual poll of the device register.
		*/
		#define C_LOCALDEF__LCCM418__FORCE_INTERRUPT_DEV0					(0U)
		#define C_LOCALDEF__LCCM418__FORCE_INTERRUPT_DEV1					(0U)
		#define C_LOCALDEF__LCCM418__FORCE_INTERRUPT_DEV2					(0U)
		#define C_LOCALDEF__LCCM418__FORCE_INTERRUPT_DEV3					(0U)
		
		//sensor G-Force range, 2,4,8
		#define C_LOCALDEF__LCCM418__G_FORCE_RANGE							(8U)

		//testing options
		#define C_LOCALDEF__LCCM418__ENABLE_TEST_SPEC 						(0U)

		//enable rate of change calculations
		#define C_LOCALDEF__LCCM418__ENABLE_ROC								(1U)
		#define C_LOCALDEF__LCCM418__ENABLE_G_FORCE							(1U)


		//the number of samples for the averaging
		#define C_LOCALDEF__LCCM418__USER_AVERAGE_MAX_SAMPLES				(64U)
		#define C_LOCALDEF__LCCM418__ROC_AVERAGE_MAX_SAMPLES				(40U)
		
		//define the data rate required
		//Valid Values are: 800, 400, 200, 100, 50, 12, 6, 1
		#define C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ						(50U)
		#define C_LOCALDEF__LCCM418__DEV1__DATA_RATE_HZ						(50U)
		#define C_LOCALDEF__LCCM418__DEV2__DATA_RATE_HZ						(50U)
		#define C_LOCALDEF__LCCM418__DEV3__DATA_RATE_HZ						(50U)
		
		
		//The parameter indexes
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__U32_HEADER				(0U)
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR0_X_ZERO		(1U)
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR0_Y_ZERO		2U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR0_Z_ZERO		3U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR1_X_ZERO		4U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR1_Y_ZERO		5U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR1_Z_ZERO		6U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR2_X_ZERO		7U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR2_Y_ZERO		8U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR2_Z_ZERO		9U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR3_X_ZERO		10U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR3_Y_ZERO		11U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__S16_SENSOR3_Z_ZERO		12U
		#define C_LOCALDEF__LCCM418__PARAM_INDEX__U16_CRC					13U
		
		
		//I2C PORT DETAILS
		#define C_LOCALDEF__LCCM418__I2C0_TX_BYTE(device, reg, byt) 			s16PIC32_I2C_USER__TxByte(C_I2C_DEVICE__I2C3A, device, reg, byt)
		#define C_LOCALDEF__LCCM418__I2C0_RX_BYTE(device, reg, ptrByte)			s16PIC32_I2C_USER__RxByte(C_I2C_DEVICE__I2C3A, device, reg, ptrByte)
		#define C_LOCALDEF__LCCM418__I2C0_RX_ARRAY(device, reg, pArray, len) 	s16PIC32_I2C_USER__RxByteArray(C_I2C_DEVICE__I2C3A, device, reg, pArray, len)

		#define C_LOCALDEF__LCCM418__I2C1_TX_BYTE(device, reg, byt) 			s16PIC32_I2C_USER__TxByte(C_I2C_DEVICE__I2C3A, device, reg, byt)
		#define C_LOCALDEF__LCCM418__I2C1_RX_BYTE(device, reg, ptrByte)			s16PIC32_I2C_USER__RxByte(C_I2C_DEVICE__I2C3A, device, reg, ptrByte)
		#define C_LOCALDEF__LCCM418__I2C1_RX_ARRAY(device, reg, pArray, len) 	s16PIC32_I2C_USER__RxByteArray(C_I2C_DEVICE__I2C3A, device, reg, pArray, len)
		
		//main include file
		#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8451.h>
	#endif //C_LOCALDEF__LCCM418__ENABLE_THIS_MODULE

#endif //0
