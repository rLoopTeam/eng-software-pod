/**
 * @file		FCU__BRAKES__MLP.C
 * @brief		MLP interface for the brakes.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__BRAKES__MLP
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

//the structure
extern struct _strFCU sFCU;

//locals
static void vFCU_BRAKES_MLP__Sample_ADC(E_FCU__BRAKE_INDEX_T eBrake);
static Lint16 s16FCU_BRAKES_MLP__Check_ADC_Limits(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES_MLP__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES_MLP__Apply_Span(E_FCU__BRAKE_INDEX_T eBrake);


/***************************************************************************//**
 * @brief
 * init the systems specifically to the MLP
 *
 */
void vFCU_BRAKES_MLP__Init(void)
{

	Luint8 u8Counter;
	Luint32 u32Header;
	Luint8 u8Test;


	//loop through each brake.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{

		//setup the fault flags
		vFAULTTREE__Init(&sFCU.sBrakes[u8Counter].sFaultFlags);

		//clear the current ADC sample
		sFCU.sBrakes[u8Counter].sMLP.u16ADC_Sample = 0U;

		//clear the zero value.
		sFCU.sBrakes[u8Counter].sMLP.u16ADC_Zero = 0U;

		//clear the ADC minus zero intermediate equation result.
		sFCU.sBrakes[u8Counter].sMLP.s32ADC_Minus_Zero = 0;

		//init the span
		sFCU.sBrakes[u8Counter].sMLP.f32SystemSpan = 1.0F;

		//brake pos.
		sFCU.sBrakes[u8Counter].sMLP.f32BrakePosition_Percent = 0.0F;

	}

	//check the CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);
	if(u8Test == 1U)
	{
		//valid
		sFCU.sBrakes[0].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO);
		sFCU.sBrakes[1].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO);

		sFCU.sBrakes[0].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN);
		sFCU.sBrakes[1].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN);

	}//if(u8Test == 1U)
	else
	{
		//CRC is invalid
		//rewrite.
		vEEPARAM__WriteU32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER, 0xAABBCCDD, 1U);

		//save the zero
		vEEPARAM__WriteU16(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO, 0U, 1U);
		vEEPARAM__WriteU16(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO, 0U, 1U);

		//do the span
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN, 1.0F, 1U);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN, 1.0F, 0U);

		//redo the CRC;
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);

		//1. Reload the structures.
		sFCU.sBrakes[0].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO);
		sFCU.sBrakes[1].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO);
		sFCU.sBrakes[0].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN);
		sFCU.sBrakes[1].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN);

		//set the flags for a general fault and cal data reload fault.
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[0].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[0].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[1].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[1].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);


	}//else if(u8Test == 1U)

	//initialize ADC user
	vRM4_ADC_USER__Init();

}

/***************************************************************************//**
 * @brief
 * resample the MLP sensors
 *
 */
void vFCU_BRAKES_MLP__Process(void)
{
	Luint8 u8Counter;
	Lint16 s16Return;

	//loop through each brake.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{
		//Update the ADC:
		vFCU_BRAKES_MLP__Sample_ADC((E_FCU__BRAKE_INDEX_T)u8Counter);

		//check the limits
		s16Return = s16FCU_BRAKES_MLP__Check_ADC_Limits((E_FCU__BRAKE_INDEX_T)u8Counter);
		if(s16Return >= 0)
		{

			//the adc limits are safe, proceed

			//filter the data.

			//zero the data.
			vFCU_BRAKES_MLP__Apply_Zero((E_FCU__BRAKE_INDEX_T)u8Counter);

			//apply the span.
			vFCU_BRAKES_MLP__Apply_Span((E_FCU__BRAKE_INDEX_T)u8Counter);

			//at this point here, the value in f32BrakePosition_Percent is the calibrated brake position.


		}
		else
		{
			//todo:
			//something bad happened with the ADC,
		}

	}


}


/***************************************************************************//**
 * @brief
 * Call this function to sample the ADC channel associated with the brake
 *
 */
void vFCU_BRAKES_MLP__Sample_ADC(E_FCU__BRAKE_INDEX_T eBrake)
{
	//Initialize conversion and process ADC
	vRM4_ADC_USER__StartConversion();
	vRM4_ADC_USER__Process();

	//determine the brake index
	switch(eBrake)
	{

		case FCU_BRAKE__LEFT:
			//read from the ADC channel 0
			sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample = u16RM4_ADC_USER__Get_RawData(0U);
			break;

		case FCU_BRAKE__RIGHT:
			//read from the ADC channel 1
			sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample = u16RM4_ADC_USER__Get_RawData(1U);
			break;

		default:
			//todo, log the error.
			break;

	}//switch(eBrake)


	//todo: Check the ADC for the most recent sample.


}

/***************************************************************************//**
 * @brief
 * Check the limits of the ADC data
 *
 * @return			-1 = Error, limits out of range\n
 * 					0 = success
 */
Lint16 s16FCU_BRAKES_MLP__Check_ADC_Limits(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lint16 s16Return;

	//init vars
	s16Return = -1;


	//Todo

	//1. determine the brake index
	//2. check if the data is in range.
	//hint: sFCU.sBrakes[].u16ADC_Sample
	if (		(sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Sample < C_LOCALDEF__LCCM655__ADC_SAMPLE__LOWER_BOUND) ||
			(sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Sample > C_LOCALDEF__LCCM655__ADC_SAMPLE__UPPER_BOUND))
	{
		s16Return = -1;
	}
	else
		{
			s16Return = 0;
		}

	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Filtering the MLP sensor value
 *
 * @return			Filtered Value
 *
 */
Lint16 s16FCU_BRAKES_MLP__Filter_ADC_Value(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lint16 s16Return;

	s16Return = u16NUMERICAL_FILTERING__Add_U16(	sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Sample,
												&sFCU.sBrakes[(Luint32)eBrake].sMLP.u16AverageCounter,
												C_MLP__MAX_AVERAGE_SIZE,
												&sFCU.sBrakes[(Luint32)eBrake].sMLP.u16AverageArray[0]);

	return s16Return;
}



/***************************************************************************//**
 * @brief
 * Apply the system span value.
 *
 * @example
 * Brake_Pos = (ADCValue - Zero) * Span
 *
 */
void vFCU_BRAKES_MLP__Apply_Span(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lfloat32 f32Temp;

	//protect the array
	if((Luint32)eBrake < C_FCU__NUM_BRAKES)
	{

		//cast to F32
		f32Temp = (Lfloat32)sFCU.sBrakes[(Luint32)eBrake].sMLP.s32ADC_Minus_Zero;

		//apply the span
		f32Temp *= sFCU.sBrakes[(Luint32)eBrake].sMLP.f32SystemSpan;

		//assign
		sFCU.sBrakes[(Luint32)eBrake].sMLP.f32BrakePosition_Percent = f32Temp;

	}
	else
	{
		//error
		//log this error
	}
}

/***************************************************************************//**
 * @brief
 * Apply the zero value to the ADC sample
 *
 */
void vFCU_BRAKES_MLP__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lint32 s32Temp;

	//protect the array
	if((Luint32)eBrake < C_FCU__NUM_BRAKES)
	{

		//convert ADC sample to s32
		s32Temp = (Lint32)sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Sample;

		//subtract the zero
		s32Temp =- (Lint32)sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Zero;

		//assign to the intermediate result
		sFCU.sBrakes[(Luint32)eBrake].sMLP.s32ADC_Minus_Zero = s32Temp;

	}
	else
	{
		//error
	}
}

#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

