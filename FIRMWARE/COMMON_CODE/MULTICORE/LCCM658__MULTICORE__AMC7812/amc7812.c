/**
 * @file		AMC7812.C
 * @brief		MAC7812 Core Layer
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM658R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup AMC7812__CORE
 * @ingroup AMC7812
 * @{ */

#include "amc7812.h"
#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

struct _strAMC7812 sAMC;

/***************************************************************************//**
 * @brief
 * Init the core module
 * 
 * @st_funcMD5		ED56D8E9A5830A1D90727FF6BB2FB08D
 * @st_funcID		LCCM658R0.FILE.000.FUNC.001
 */
void vAMC7812__Init(void)
{

	//init the vars
	sAMC.eState = AMC7812_STATE__RESET;

	//int the fault tree
	vFAULTTREE__Init(&sAMC.sFaultTree);

	//init lowlevel
	vAMC7812_LOWLEVEL__Init();
	
	//init I2C Layer
	vAMC7812_I2C__Init();
	
	//Setup any GPIO
	vAMC7812_GPIO__Init();
	
	//setup the DAC
	vAMC7812_DAC__Init();
	
	//Setup the ADC
	vAMC7812_ADC__Init();
	

}

/***************************************************************************//**
 * @brief
 * Process any core tasks.
 * 
 * @st_funcMD5		96394E4CC69E197E228D42A9743AF8BC
 * @st_funcID		LCCM658R0.FILE.000.FUNC.002
 */
void vAMC7812__Process(void)
{
	Luint8 u8Counter;
	Luint8 u8Temp;
	Lint16 s16Return;
	Luint16 u16DeviceID;
	Luint16 u16Temp;

#if 0
	Luint8 u8EngineNumber = 0;
	Luint16 u16ThrottleCommand = 0;
	E_AMC7812_DAC_DATA_REG_ADDRESSES eDAC_REG_ADDR;
#endif

	//process the DAC section
	vAMC7812_DAC__Process();

	//do the ADC
	vAMC7812_ADC__Process();

	//GPIO
	vAMC7812_GPIO__Process();

	//handle the state machine
	switch(sAMC.eState)
	{
		case AMC7812_STATE__RESET:

			//out of POR reset we want to do a software reset.

#ifndef WIN32
			//wait a little bit incase we came in from clocking out bad I2C data.
			vRM4_DELAYS__Delay_mS(10U);
#endif

			//AMC7812 must be reset after power up
			s16Return = s16AMC7812_I2C__TxCommand(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__SW_RESET);
			if(s16Return >= 0)
			{
				//success
				//change state
				sAMC.eState = AMC7812_STATE__CONFIGURE_DAC;
			}
			else
			{
				vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__00);
				vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__02);

				//read error, handle state.
				sAMC.eState = AMC7812_STATE__FAULT;

			}

			break;

		case AMC7812_STATE__CONFIGURE_DAC:

			//setup the DAC
			//get a sample of the device ID, great for debugging
			s16Return = s16AMC7812_I2C__ReadU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_REG_ADR__DEV_ID, &u16DeviceID);
			if(s16Return >= 0)
			{
				//good

				u16Temp = 0x0000;

				// set the bits high to activate the DAC pins 0 to 7 (bits 1 - 8)
				u16Temp |= (0x00FFU << 4U);

				// also set the PREF bit (bit 13) high because we are using the internal voltage reference
				u16Temp |= (1U << 13U);

				// final value should be 0x21FE (for all pins: u16RegisterBitValues = 0x3FFE)
				// set the power-down register
				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_REG_ADR__PWR_DWN, u16Temp);


				//set all the gains to 2.0
				u16Temp = 0x0000U;
				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__GAINS, u16Temp);

				//async load so as we can set all the channels individually
				u16Temp = 0x0000U;
				s16Return = s16AMC7812_I2C__WriteU16(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__CONFIG, u16Temp);


			}
			else
			{
				vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__00);
				vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__02);

				//big problem
				sAMC.eState = AMC7812_STATE__FAULT;
			}


			sAMC.eState = AMC7812_STATE__IDLE;
			break;

		case AMC7812_STATE__IDLE:

			//we are idle, waiting for a command or something to happen
			u8Temp = 0U;
			for(u8Counter = 0U; u8Counter < NUM_DAC_CHANNELS; u8Counter++)
			{
				u8Temp += sAMC.sDAC.u8NewValueLatched[u8Counter];
			}

			//do we need to udate some dac settings?
			if(u8Temp > 0U)
			{

			}
			else
			{
				//stay in state
			}

			break;


		case AMC7812_STATE__UPDATE_DAC:
			//update the DAC settings on the device

			if(sAMC.sDAC.u8NewValueLatched[sAMC.sDAC.u8UpdatePos] == 1U)
			{
				//we have a new value, send it.
				s16Return = s16AMC7812_I2C__WriteU16(	C_LOCALDEF__LCCM658__BUS_ADDX,
														AMC7812_REG_ADR__DAC_0_DATA + sAMC.sDAC.u8UpdatePos,
														sAMC.sDAC.u16DAC_OutputValue[sAMC.sDAC.u8UpdatePos]);
				if(s16Return >= 0)
				{
					//success
					//change state
					sAMC.eState = AMC7812_STATE__IDLE;
				}
				else
				{
					//read error, handle state.
					sAMC.eState = AMC7812_STATE__FAULT;

				}
			}
			else
			{
				//no new value latched
				sAMC.eState = AMC7812_STATE__IDLE;
			}

			//inc the pos
			if(sAMC.sDAC.u8UpdatePos < NUM_DAC_CHANNELS)
			{
				sAMC.sDAC.u8UpdatePos++;
			}
			else
			{
				sAMC.sDAC.u8UpdatePos = 0U;
			}
			break;

		case AMC7812_STATE__FAULT:
			//some error has happened

			break;

		default:
			//do nothing
			break;

	} //switch(sAMC.eState)


}

E_AMC7812__MNAIN_STATES_T eAMC7812__Get_State(void)
{
	return sAMC.eState;
}

Luint32 u32AMC7812__Get_FaultFlags(void)
{
	return sAMC.sFaultTree.u32Flags[0];
}

//ufser level function to set the DAC voltage
void vAMC7182__DAC_SetVoltage(Luint8 u8Channel, Lfloat32 f32Voltage)
{
	//make sure we are in range
	if(u8Channel < NUM_DAC_CHANNELS)
	{
		//do the update on the DAC
		vAMC7182_DAC__DAC_UpdateVoltage(u8Channel, f32Voltage);
	}
	else
	{
		//error
		vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sAMC.sFaultTree, C_LCCM658__CORE__FAULT_INDEX__01);
	}


}

#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

