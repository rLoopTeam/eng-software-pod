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

extern struct _strAMC7812_DAC strAMC7812_DAC;

/***************************************************************************//**
 * @brief
 * Init the core module
 * 
 * @st_funcMD5		ED56D8E9A5830A1D90727FF6BB2FB08D
 * @st_funcID		LCCM658R0.FILE.000.FUNC.001
 */
void vAMC7812__Init(void)
{
	//init lowlevel
	vAMC7812_LOWLEVEL__Init();
	
	//init I2C
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

	Lint16 s16Return = 0;

	//handle the state machine
	switch ( strAMC7812_DAC.eState )
	{
		case AMC7812_DAC_STATE__IDLE:
			//do nothing
			s16Return = 0;
			break;

		case AMC7812_DAC_STATE__INIT_DEVICE:
			//reset the device

			//wait a little bit incase we came in from clocking out bad I2C data.
			vRM4_DELAYS__Delay_mS(10U);

			//AMC7812 must be reset after power up
			s16Return = s16AMC7812_I2C__TxCommand( C_LOCALDEF__LCCM658__BUS_ADDX, ACM7812_DAC_REG__RESET );

			if ( s16Return >= 0 )
			{
				//success
				//change state
				strAMC7812_DAC.eState = AMC7812_DAC_STATE__WRITE;
			}
			else
			{
				//read error, handle state.
				strAMC7812_DAC.eState = AMC7812_DAC_STATE__ERROR;

			}
			break;



		case AMC7812_DAC_STATE__WRITE:

			// write throttle values
			s16Return = s16AMC7812_I2C__WriteU16( C_LOCALDEF__LCCM658__BUS_ADDX, strAMC7812_DAC.eDAC_Data_Addx, strAMC7812_DAC.u16ThrottleCommand );

			if ( s16Return >= 0 )
			{
				//sample started, wait for some processing loops to expire

				//change states
				strAMC7812_DAC.eState = AMC7812_DAC_STATE__WAIT_LOOPS;

			}
			else
			{
				//error has occurred
				strAMC7812_DAC.eState = AMC7812_DAC_STATE__ERROR;
			}

			break;

		case AMC7812_DAC_STATE__WAIT_LOOPS:

			//todo, change to constant
			if ( strAMC7812_DAC.u32LoopCounter > C_LOCALDEF__LCCM658__NUM_CONVERSION_LOOPS )
			{
				//move on to write to DAC
				strAMC7812_DAC.eState = AMC7812_DAC_STATE__WRITE;

			}
			else
			{
				//increment the loop counter;
				strAMC7812_DAC.u32LoopCounter += 1;
				//stay in state
			}

			s16Return = 0;

			break;


		case AMC7812_DAC_STATE__ERROR:
			//some error has happened
			break;

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

