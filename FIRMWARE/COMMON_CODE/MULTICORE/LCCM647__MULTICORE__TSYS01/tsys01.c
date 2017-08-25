/**
 * @file		TSYS01.C
 * @brief		TSYS01 Temp Sensor Driver
 * @author		Dean, Lachlan Grogan
 * @st_fileID	LCCM647R0.FILE.000
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup TSYS01__CORE
 * @ingroup TSYS01
 * @{ */
 
#include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>
#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

//structure
TS_TSYS01__MAIN sTSYS;

//locals
static Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values);
static void vTSYS01__Delay_mS(Luint32 u32Value);

/***************************************************************************//**
 * @brief
 * Init any variables as needed
 * 
 * @st_funcMD5		AD7E1745A84BCDE183BB048EB939545D
 * @st_funcID		LCCM647R0.FILE.000.FUNC.001
 */
void vTSYS01__Init(void)
{
	Luint8 u8Counter;

	//configure guarding
	sTSYS.u32Guard0 = 0xABCD1234U;
	sTSYS.u32Guard1 = 0x98765432U;
	sTSYS.u8NewDataAvail = 0U;
	
	//setup the flags
	vSIL3_FAULTTREE__Init(&sTSYS.sFaultFlags);
	
	//structure init
	sTSYS.eState = TSYS01_STATE__INIT_DEVICE;
	sTSYS.u32LoopCounter = 0U;
	sTSYS.u32AverageResult = 0U;
	sTSYS.u32AverageResult_Div256 = 0U;
	sTSYS.u16AverageCounter = 0U;

	//set to some out there value
	sTSYS.f32TempDegC = 127.0F;
	sTSYS.u3210MS_Timer = 0U;

	//clear the average
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM647__MAX_FILTER_SAMPLES; u8Counter++)
	{
		sTSYS.u32AverageArray[u8Counter] = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Main processing state machine.
 * 
 * @st_funcMD5		2596479478B2632DCEF8B53771667CED
 * @st_funcID		LCCM647R0.FILE.000.FUNC.002
 */
void vTSYS01__Process(void)
{
	Luint16 u16KValues[5];
	Lfloat32 f32Term[5];
	Lfloat32 f32Pow;
	Lint16 s16Return;

	//check the guarding
	if(sTSYS.u32Guard0 != 0xABCD1234U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__01);
	}
	if(sTSYS.u32Guard1 != 0x98765432U)
	{
		vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__01);
	}
	
	
	//handle the state machine
	switch(sTSYS.eState)
	{
		case TSYS01_STATE__IDLE:
			//do nothing,
			break;

		case TSYS01_STATE__INIT_DEVICE:
			//reset the device

			//wait a little bit incase we came in from clocking out bad I2C data.
			vTSYS01__Delay_mS(10U);

			//TSYS01 must be reset after power up
			s16Return = s16TSYS01_I2C__TxCommand(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__RESET);
			if(s16Return >= 0)
			{
				//success
				//change state
				sTSYS.eState = TSYS01_STATE__READ_CONSTANTS;
			}
			else
			{
				//update faults
				vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__00);
				vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__02);
				//read error, handle state.
				sTSYS.eState = TSYS01_STATE__ERROR;
			}
			break;

		case TSYS01_STATE__READ_CONSTANTS:

			//issue the read command and read all 5 values
			s16Return = s16TSYS01__Read_K_Values(&u16KValues[0]);
			if(s16Return >= 0)
			{

				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					u16KValues[4] = 28446;
					u16KValues[3] = 24926;
					u16KValues[2] = 36016;
					u16KValues[1] = 32791;
					u16KValues[0] = 40781;
				#endif

				//process
				// Use K values to compute the full coefficient for each polynomial term,
				// these coeffs are static, so this doesn't have to be done in __Process()
				f32Pow = f32SIL3_NUM_POWER__F32(10.0F, -21.0F);
				sTSYS.f32Coeffs[4] = (-2.0F) * (Lfloat32)u16KValues[4] * f32Pow;

				sTSYS.f32Coeffs[3] = 4.0F * (Lfloat32)u16KValues[3] * f32SIL3_NUM_POWER__F32(10.0F, -16.0F);
				sTSYS.f32Coeffs[2] = -2.0F * (Lfloat32)u16KValues[2] * f32SIL3_NUM_POWER__F32(10.0F, -11.0F);
				sTSYS.f32Coeffs[1] = 1.0F * (Lfloat32)u16KValues[1] * f32SIL3_NUM_POWER__F32(10.0F, -6.0F);
				sTSYS.f32Coeffs[0] = -1.5F * (Lfloat32)u16KValues[0] * f32SIL3_NUM_POWER__F32(10.0F, -2.0F);

				//todo: range checks on constants.

				//move to ready state waiting for a conversion start
				sTSYS.eState = TSYS01_STATE__BEGIN_SAMPLE;

			}
			else
			{
				//update faults
				vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__00);
				vSIL3_FAULTTREE__Set_Flag(&sTSYS.sFaultFlags, C_LCCM647__CORE__FAULT_INDEX__03);
			
				//Change to error state
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;


		case TSYS01_STATE__BEGIN_SAMPLE:
			//issue the request
			s16Return = s16TSYS01_I2C__TxCommand(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__START_ADC_TEMPERATURE_CONVERSION);
			if(s16Return >= 0)
			{
				//sample started, wait for some processing loops to expire

				//clear the counter
				sTSYS.u32LoopCounter = 0U;

				//change states
				sTSYS.u3210MS_Timer = 0U;
				sTSYS.eState = TSYS01_STATE__WAIT_LOOPS;

			}
			else
			{
				//error has occurred
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;

		case TSYS01_STATE__WAIT_LOOPS:

			//todo, change to constant
			if(sTSYS.u3210MS_Timer > 20U)
			//if(sTSYS.u32LoopCounter > C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS)
			{
				//move on to read the ADC
				sTSYS.eState = TSYS01_STATE__READ_ADC;

			}
			else
			{
				//increment the loop counter;
				sTSYS.u32LoopCounter += 1U;
				//stay in state
			}
			break;

		case TSYS01_STATE__READ_ADC:
			//do the ADC read
			s16Return = s16TSYS01_I2C__RxU24(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__READ_ADC_TEMPERATURE_RESULT, &sTSYS.u32LastResult);
			if(s16Return >= 0)
			{

				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					sTSYS.u32LastResult = 9378708;
				#endif
				//add to filter
				sTSYS.u32AverageResult = u32SIL3_NUM_FILTERING__Add_U32(sTSYS.u32LastResult,
																		&sTSYS.u16AverageCounter,
																		C_LOCALDEF__LCCM647__MAX_FILTER_SAMPLES,
																		&sTSYS.u32AverageArray[0]);
				#if C_LOCALDEF__LCCM647__ENABLE_DS_VALUES == 1U
					sTSYS.u32AverageResult = 9378708;
				#endif

				//generate the DIV256 option
				sTSYS.u32AverageResult_Div256 = sTSYS.u32AverageResult >> 8U;

				//change state
				sTSYS.eState = TSYS01_STATE__COMPUTE;
			}
			else
			{
				//error has occurred
				sTSYS.eState = TSYS01_STATE__ERROR;
			}

			break;

		case TSYS01_STATE__COMPUTE:
			// Compute temperature polynomial terms individually then sum
			f32Term[4] = sTSYS.f32Coeffs[4] * f32SIL3_NUM_POWER__F32((Lfloat32)sTSYS.u32AverageResult_Div256, 4.0F);
			f32Term[3] = sTSYS.f32Coeffs[3] * f32SIL3_NUM_POWER__F32((Lfloat32)sTSYS.u32AverageResult_Div256, 3.0F);
			f32Term[2] = sTSYS.f32Coeffs[2] * f32SIL3_NUM_POWER__F32((Lfloat32)sTSYS.u32AverageResult_Div256, 2.0F);
			f32Term[1] = sTSYS.f32Coeffs[1] * (Lfloat32)sTSYS.u32AverageResult_Div256;
			f32Term[0] = sTSYS.f32Coeffs[0];

			// Celsius units
			sTSYS.f32TempDegC = f32Term[4] + f32Term[3] + f32Term[2] + f32Term[1] + f32Term[0];

			//go back and re-sample
			sTSYS.eState = TSYS01_STATE__BEGIN_SAMPLE;

			//set the flag
			sTSYS.u8NewDataAvail = 1U;

			break;

		case TSYS01_STATE__ERROR:
			//some error has happened
			break;

	}

}

Luint8 u8TSYS__Get_NewDataAvail(void)
{
	return sTSYS.u8NewDataAvail;
}

/***************************************************************************//**
 * @brief
 * Read each of the 5 K calibration constants over i2c
 * 
 * @param[in]		*pu16Values				Pointer to returned values
 * @return			0 = success\n
 * 					-ve = fault 
 * @st_funcMD5		3FAB8ED94A8C7555A93E8EE1B56426F9
 * @st_funcID		LCCM647R0.FILE.000.FUNC.003
 */
Lint16 s16TSYS01__Read_K_Values(Luint16 *pu16Values)
{
	Lint16 s16Return;
	Luint16 * pu16Temp;

	vTSYS01__Delay_mS(10U);
	pu16Temp = &pu16Values[0];
	s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k0_ADR, pu16Temp);
	if(s16Return >= 0)
	{
		vTSYS01__Delay_mS(10U);
		pu16Temp = &pu16Values[1];
		s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k1_ADR, pu16Temp);
		if(s16Return >= 0)
		{
			vTSYS01__Delay_mS(10U);
			pu16Temp = &pu16Values[2];
			s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k2_ADR, pu16Temp);
			if(s16Return >= 0)
			{
				vTSYS01__Delay_mS(10U);
				pu16Temp = &pu16Values[3];
				s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k3_ADR, pu16Temp);
				if(s16Return >= 0)
				{
					vTSYS01__Delay_mS(10U);
					pu16Temp = &pu16Values[4];
					s16Return = s16TSYS01_I2C__RxU16(C_LOCALDEF__LCCM647__BUS_ADDX, TSYS01_REG__k4_ADR, pu16Temp);

					//fall on
				}
				else
				{
					//fall on
				}

			}
			else
			{
				//fall on with error code
			}

		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//fall on
	}

	//return with the status of the I2C read
	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Standard delay routine
 * 
 * @param[in]		u32Value			ms Delay Value
 * @st_funcMD5		E7819127BB146243E4215732DBF139AF
 * @st_funcID		LCCM647R0.FILE.000.FUNC.005
 */
void vTSYS01__Delay_mS(Luint32 u32Value)
{

	#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
		vRM4_DELAYS__Delay_mS(u32Value);
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
		vMSP430_DELAYS__Delay_mS(u32Value);
	#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U
		//no delay on WIN32
	#else
		#error
	#endif

}


/***************************************************************************//**
 * @brief
 * Most recent measurement, made global for external use
 * 
 * @return			Temperature in DegC
 * @st_funcMD5		8659D658713AB1BA9D1CC17CFF9FDCB4
 * @st_funcID		LCCM647R0.FILE.000.FUNC.004
 */
Lfloat32 f32TSYS01__Get_TempDegC(void)
{
	//clear the flag
	sTSYS.u8NewDataAvail = 0U;

	//return the temp
	return sTSYS.f32TempDegC;
}

/***************************************************************************//**
 * @brief
 * Get any module level fault flags.
 * 
 * @return			The fault flags
 * @st_funcMD5		EE994C7B49C8B626208C270E5ED75C07
 * @st_funcID		LCCM647R0.FILE.000.FUNC.006
 */
Luint32 u32TSYS01__Get_FaultFlags(void)
{
	return sTSYS.sFaultFlags.u32Flags[0];
}

void vTSYS01__10MS_Timer(void)
{
	sTSYS.u3210MS_Timer++;
}

#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
