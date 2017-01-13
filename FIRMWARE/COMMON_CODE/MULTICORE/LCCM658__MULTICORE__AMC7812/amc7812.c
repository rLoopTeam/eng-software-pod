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


			//wait a little bit incase we came in from clocking out bad I2C data.
			vRM4_DELAYS__Delay_mS(10U);

			//AMC7812 must be reset after power up
			s16Return = s16AMC7812_I2C__TxCommand(C_LOCALDEF__LCCM658__BUS_ADDX, AMC7812_DAC_REG__SW_RESET);
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


#if 0
// ACM7812 DAC control commands

Lint16 s16AMC7812__DAC_Control( Luint8 u8Input )
{

	// ACM7812 DAC control signals:

	// DAC CLR0 (low clears DAC, high is normal)

	// DAC CLR1 (low clears DAC, high is normal)

	// DAC RESET (low resets hardware)

	// DAC DAV (data available - low when conversion ends)

	// DAC CNVT (conversion trigger - falling edge starts sampling)

	return 0;
}

#endif //0

#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

