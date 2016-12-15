/**
 * @file		AMC7812__DAC.C
 * @brief		DAC Portion of the device
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.007
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__DAC
 * @ingroup AMC7812
 * @{ */

#include "../amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

extern struct _strAMC7812_DAC strAMC7812_DAC;


/***************************************************************************//**
 * @brief
 * Init the DAC portion.
 * 
 * @st_funcMD5		C180710CF0A27FA75265B2D3FA81C0E7
 * @st_funcID		LCCM658R0.FILE.007.FUNC.001
 */
void vAMC7812_DAC__Init(void)
{

	// structure init
	strAMC7812_DAC.eState = AMC7812_DAC_STATE__INIT_DEVICE;
	strAMC7812_DAC.u32LoopCounter = 0U;
	strAMC7812_DAC.u16MaxVoltage = DAC_OUT_MAX_MVOLTS;
	strAMC7812_DAC.u16MinVoltage = DAC_OUT_MIN_MVOLTS;


	// assign the address of the output pin data register
//
	u8DACOutputChannelAddr[0] = AMC7812_REG_ADR__DAC_0_DATA;
	u8DACOutputChannelAddr[1] = AMC7812_REG_ADR__DAC_1_DATA;
	u8DACOutputChannelAddr[2] = AMC7812_REG_ADR__DAC_2_DATA;
	u8DACOutputChannelAddr[3] = AMC7812_REG_ADR__DAC_3_DATA;
	u8DACOutputChannelAddr[4] = AMC7812_REG_ADR__DAC_4_DATA;
	u8DACOutputChannelAddr[5] = AMC7812_REG_ADR__DAC_5_DATA;
	u8DACOutputChannelAddr[6] = AMC7812_REG_ADR__DAC_6_DATA;
	u8DACOutputChannelAddr[7] = AMC7812_REG_ADR__DAC_7_DATA;
	u8DACOutputChannelAddr[8] = AMC7812_REG_ADR__DAC_8_DATA;
	u8DACOutputChannelAddr[9] = AMC7812_REG_ADR__DAC_9_DATA;
	u8DACOutputChannelAddr[10] = AMC7812_REG_ADR__DAC_10_DATA;
	u8DACOutputChannelAddr[11] = AMC7812_REG_ADR__DAC_11_DATA;
//
}


Luint16 vAMC7812_DAC__Process(void)
{

	// declarations

	Luint8 u8ReturnVal;
	Lint16 s16Return;
	Luint16 u16RegisterBitValues;
	Luint16 u16DeviceIDAddr;

	// initialize

	s16Return = -1;

	// state machine

	switch(strAMC7812_DAC.eState)
	{
		case AMC7812_DAC_STATE__IDLE:

			s16Return = 0;
			break;

		case AMC7812_DAC_STATE__INIT_DEVICE:

			// reset the device

			// wait in case we came in from clocking out bad I2C data

			vRM4_DELAYS__Delay_mS(10U);

			// software reset

			s16Return = -1;
			//s16Return = s16AMC7812_I2C__TxCommand(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__SW_RESET);

			// Hardware reset

			// first, set the pin direction

			vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);

			// To reset the device, create a pulse:

			// first check the value of the pin

			u8ReturnVal = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);

			if(u8ReturnVal == 0U)
			{
				// if the pin is low, set the pin high and wait

				vRM4_N2HET_PINS__Set_PinHigh(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);
				//vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, u32Bit, u32Value);

				vRM4_DELAYS__Delay_uS(100U);
			}
			else
			{
				// ok
			}

			// set the pin low, wait, set the pin high, and wait

			vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);

			vRM4_DELAYS__Delay_uS(100U);

			vRM4_N2HET_PINS__Set_PinHigh(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);

			vRM4_DELAYS__Delay_uS(100U);

			// check the value of the pin (should be 1)

			u8ReturnVal = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, RM48_N2HET1_PIN__AMC7812_HW_RESET);

			// optional: check the device ID (should be 0x1220)

			s16Return = s16AMC7812_I2C__ReadU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_REG_ADR__DEV_ID, &u16DeviceIDAddr);

			if (u8ReturnVal == 1U)
			{
				// Power-on reset successful
				// set the power-down register

				// initialize bit field

				u16RegisterBitValues = 0x0000;

				// set the bits high to activate the DAC pins 0 to 7 (bits 1 - 8)

				u16RegisterBitValues |= (0xFF << 1);

				// also set the PREF bit (bit 13) high because we are using the internal voltage reference

				u16RegisterBitValues |= (1 << 13);

				// final value should be 0x21FE (for all pins: u16RegisterBitValues = 0x3FFE)

				// set the power-down register

				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_REG_ADR__PWR_DWN, u16RegisterBitValues);

				// set the DAC gain
				// output voltage is GAIN * Vref,
				// where GAIN = 2 or 5 if bit is low or high, respectively

				if(AMC7812_DAC_GAIN_FLAG == 1U)
				{
					// set for high gain (x5)
					// setting all channels the same, can be set individually
					u16RegisterBitValues = 0x0FFF;

					strAMC7812_DAC.u8Gain = 5U;
				}
				else
				{
					// set for low gain (x2)
					// setting all channels the same, can be set individually
					u16RegisterBitValues = 0x0000;

					strAMC7812_DAC.u8Gain = 2U;
				}
				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__GAINS, u16RegisterBitValues);

				// Set the configuration mode

				if(AMC7812_DAC_CONFIG_MODE_FLAG == 1U)
				{
					// set bits to 1 for synchronous load
					// setting all channels the same, can be set individually
					u16RegisterBitValues = 0x0FFF;
				}
				else
				{
					// set bits for asynchronous load
					// setting all channels the same, can be set individually
					u16RegisterBitValues = 0x0000;
				}
				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__CONFIG, u16RegisterBitValues);

				// Compute the output scale factor (DAC registers are 12-bit, so range is 0 to 2^12 = 4096)
				// 	The DAC register value is Vreqd * Gain * Vref / 2^12

				strAMC7812_DAC.f32ScaleFactor = (4096.0F) / (Lfloat32)(strAMC7812_DAC.u8Gain * AMC7812_DAC_VREF);

			}	// end if (u8ReturnVal == 1U)

			if (u8ReturnVal == 0U && s16Return >= 0U)
			{
				// setup successful, change state

				strAMC7812_DAC.eState = AMC7812_DAC_STATE__IDLE;
			}
			else
			{
				// setup failed, change state

				strAMC7812_DAC.eState = AMC7812_DAC_STATE__ERROR;

			}
			break;

		case AMC7812_DAC_STATE__SET_VOLTAGE:

			// set output pin voltage

			break;

		case AMC7812_DAC_STATE__ERROR:

			// an error has occurred

			break;

	}	// end of switch(strAMC7812_DAC.eState)

	return s16Return;

}	// end vAMC7812_DAC__Process(void)



//--- Set the voltage of the specified pin for the given command and conversion factor (to millivolts) ---//

Lint16 s16AMC7812_DAC__SetPinVoltage(void)
{
	// declarations

	Lint16 s16Return;
	Luint16 u16OutputVolts;
	Lfloat32 f32ThrottleToMVolts;
	Luint16 u16Command;
	Luint16 u16MaxCommandValue;
	Luint16 u16MinCommandValue;
	Luint16 u16MaxVolts;
	Luint16 u16MinVolts;
	Luint8 u8RegAddr;
	Lfloat32 f32ScaleFactor;
	Luint16 u16DACData;
	Lfloat32 f32temp1, f32temp2;


	// set local variables

	u16Command = strAMC7812_DAC.u16Command;
	u16MaxCommandValue = strAMC7812_DAC.u16MaxCommandValue;
	u16MinCommandValue = strAMC7812_DAC.u16MinCommandValue;
	u16MaxVolts = strAMC7812_DAC.u16MaxVoltage;
	u16MinVolts = strAMC7812_DAC.u16MinVoltage;
	u8RegAddr = strAMC7812_DAC.u8DACRegAddr;
	f32ScaleFactor = strAMC7812_DAC.f32ScaleFactor;

	// set the state

	strAMC7812_DAC.eState = AMC7812_DAC_STATE__SET_VOLTAGE;

	// compute command conversion factor (command units to millivolts)

	f32temp1 = (Lfloat32)(u16MaxVolts - u16MinVolts);
	f32temp2 = (Lfloat32)(u16MaxCommandValue - u16MinCommandValue);
	f32ThrottleToMVolts = f32temp1 / f32temp2;


	// Compute required voltage for the throttle command value

	u16OutputVolts = (Luint16)(u16Command * f32ThrottleToMVolts);

	// Check that output is within range

	if(u16OutputVolts > u16MaxVolts)
	{
		u16OutputVolts = u16MaxVolts;
	}
	else
	{
		if(u16OutputVolts < u16MinVolts)
		{
			u16OutputVolts = u16MinVolts;
		}
		else
		{
			// okay, no action req'd
		}
	}

	// Compute the DAC 12-bit register value to get the desired voltage output:

	f32temp1 = (Lfloat32)u16OutputVolts * f32ScaleFactor;
	u16DACData = (Luint16)f32temp1;

	// initialize return flag

	s16Return = -1;

	// call I2C write function

	s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, u8RegAddr, u16DACData);

	if(s16Return >= 0)
	{
		// successful, change state

		strAMC7812_DAC.eState = AMC7812_DAC_STATE__IDLE;
	}
	else
	{
		// failed, change state

		strAMC7812_DAC.eState = AMC7812_DAC_STATE__ERROR;
	}

	return s16Return;
}



#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

