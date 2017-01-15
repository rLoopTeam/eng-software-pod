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
static void vFCU_BRAKES_MLP__Sample_ADC(void);
static Lint16 s16FCU_BRAKES_MLP__Check_ADC_Limits(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES_MLP__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES_MLP__Apply_Span(E_FCU__BRAKE_INDEX_T eBrake);
static Lint16 s16FCU_BRAKES_MLP__Filter_ADC_Value(E_FCU__BRAKE_INDEX_T eBrake);

/***************************************************************************//**
 * @brief
 * init the systems specifically to the MLP
 * 
 * @st_funcMD5		1526985EB514C32C0F929BD217105401
 * @st_funcID		LCCM655R0.FILE.024.FUNC.001
 */
void vFCU_BRAKES_MLP__Init(void)
{

	Luint8 u8Counter;
	Luint8 u8Test;

	//loop through each brake.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{
		//clear the current ADC sample
		sFCU.sBrakes[u8Counter].sMLP.u16ADC_Sample = 0U;

		//clear the zero value.
		sFCU.sBrakes[u8Counter].sMLP.u16ADC_Zero = 0U;

		//clear the ADC minus zero intermediate equation result.
		sFCU.sBrakes[u8Counter].sMLP.s32ADC_Minus_Zero = 0;

		//init the span
		sFCU.sBrakes[u8Counter].sMLP.f32SystemSpan = 1.0F;

		//brake pos.
		sFCU.sBrakes[u8Counter].sMLP.f32BrakePosition_mm = 0.0F;

		//set lowest mlp value to a high flag
		sFCU.sBrakes[u8Counter].sMLP.lowest_value = 9999U;

		//set higest mlp value to 0
		sFCU.sBrakes[u8Counter].sMLP.highest_value = 0U;

		#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
			//debug only
			sFCU.sBrakes[(Luint32)u8Counter].sMLP.zero_count = 0U;
		#endif

		// temporary use; identify when the startup sequence is over and ADC won't be 0.
		sFCU.sBrakes[(Luint32)u8Counter].sMLP.u8Running = 0U;

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
		vFAULTTREE__Set_Flag(&sFCU.sBrakesGlobal.sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sBrakesGlobal.sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);



	}//else if(u8Test == 1U)

#ifndef WIN32
	//now that we are ready, start the conversions.
	vRM4_ADC_USER__StartConversion();
#endif

}

/***************************************************************************//**
 * @brief
 * resample the MLP sensors
 * 
 * @st_funcMD5		BD5E7979D0E472FD0EA53691718E9C7F
 * @st_funcID		LCCM655R0.FILE.024.FUNC.002
 */
void vFCU_BRAKES_MLP__Process(void)
{
	Luint8 u8Counter;
	Lint16 s16Limit;
	Lint16 s16Return;

	//Update the ADC:
	//new data may or not be available.
	vFCU_BRAKES_MLP__Sample_ADC();

	//loop through each brake.
	//always do the processing.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{

		//check the limits
		s16Limit = s16FCU_BRAKES_MLP__Check_ADC_Limits((E_FCU__BRAKE_INDEX_T)u8Counter);
		if(s16Limit >= 0)
		{

			//the adc limits are safe, proceed

			//filter the data.
			s16Return = s16FCU_BRAKES_MLP__Filter_ADC_Value((E_FCU__BRAKE_INDEX_T)u8Counter);
			if( s16Return < 0 )
			{
				//handle error
			}
			else
			{
				sFCU.sBrakes[(Luint32)u8Counter].sMLP.u16ADC_FilteredSample = (Luint16) s16Return;
			}

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
			//this may only be that we were below the limit during power up
		}


	}//for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)


}


/***************************************************************************//**
 * @brief
 *  Call this function to sample the ADC channel associated with the brake
 * 
 * @param[in]		eBrake				The brake index
 * @st_funcMD5		22651109FEC8DB182929455B0B0FE06D
 * @st_funcID		LCCM655R0.FILE.024.FUNC.003
 */
void vFCU_BRAKES_MLP__Sample_ADC(void)
{
	Luint8 u8New;
	Luint8 u8Counter;

	//check the ADC converter process
#ifndef WIN32
	u8New = u8RM4_ADC_USER__Is_NewDataAvailable();
#else
	u8New = 1U;
#endif
	if(u8New == 1U)
	{

		for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
		{
			//determine the brake index
			switch(u8Counter)
			{

				case FCU_BRAKE__LEFT:
					//read from the ADC channel 0
	#ifndef WIN32
					sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample = u16RM4_ADC_USER__Get_RawData(0U);
	#else
					sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample = sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.sWin32.u16ADC_Sample;
	#endif
					if (sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample > sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.highest_value) {
						sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.highest_value = sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample;
					}
					// sometimes sample hits 0 but isn't a real value, throw it out
					if (sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample < sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.lowest_value && sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample != 0U) {
						sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.lowest_value = sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample;
					}
					break;

				case FCU_BRAKE__RIGHT:
					//read from the ADC channel 1
	#ifndef WIN32
					sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample = u16RM4_ADC_USER__Get_RawData(1U);
	#else
					sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample = sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.sWin32.u16ADC_Sample;
	#endif
					if (sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample > sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.highest_value) {
						sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.highest_value = sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample;
					}
					// sometimes sample hits 0 but isn't a real value, throw it out
					if (sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample < sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.lowest_value && sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample != 0U) {
						sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.lowest_value = sFCU.sBrakes[(Luint32)FCU_BRAKE__RIGHT].sMLP.u16ADC_Sample;
					}
					break;


				default:
					//todo, log the error.
					break;

			}//switch(eBrake)

		}//for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)

		//taken the data now
#ifndef WIN32
		vRM4_ADC_USER__Clear_NewDataAvailable();
#endif
	}
	else
	{
		//no new ADC, don't do anything
	}



}

/***************************************************************************//**
 * @brief
 * Check the limits of the ADC data
 *
 * @param[in]		eBrake				The brake index
 * @return			-1 = Error, limits out of range\n
 * 					0 = success
 * @st_funcMD5		BE00FC48D260311DF0578D1DA2E875DB
 * @st_funcID		LCCM655R0.FILE.024.FUNC.004
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
 * @param[in]		eBrake					The brake index
 * @return			Filtered Value
 * @st_funcMD5		5026035D4C7154FA483D9F60FA67916B
 * @st_funcID		LCCM655R0.FILE.024.FUNC.005
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
 * @param[in]		eBrake				The brake index
 * @st_funcMD5		30F2A16DDC839D704891DC145917EA38
 * @st_funcID		LCCM655R0.FILE.024.FUNC.006
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
		sFCU.sBrakes[(Luint32)eBrake].sMLP.f32BrakePosition_mm = f32Temp;

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
 * @param[in]		eBrake					The brake index
 * @st_funcMD5		91B14636179F6DEA07A2A6B2DD7B2C37
 * @st_funcID		LCCM655R0.FILE.024.FUNC.007
 */
void vFCU_BRAKES_MLP__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lint32 s32Temp;

	//protect the array
	if((Luint32)eBrake < C_FCU__NUM_BRAKES)
	{

		//convert ADC sample to s32
		s32Temp = (Lint32)sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_FilteredSample;

		//subtract the zero
		s32Temp -= (Lint32)sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Zero;

		//assign to the intermediate result
		sFCU.sBrakes[(Luint32)eBrake].sMLP.s32ADC_Minus_Zero = s32Temp;

	}
	else
	{
		//error
	}
}


/***************************************************************************//**
 * @brief
 * compute live calibration zero
 * 
 * @param[in]		eBrake				The brake channel.
 * @param[in]		u32Key				0x11112222U
 * @st_funcMD5		45386F94C0417E4653974BA16A98646C
 * @st_funcID		LCCM655R0.FILE.024.FUNC.008
 */
void vFCU_BRAKES_MLP__ComputeCalibration_Zero(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake)
{
	if (u32Key == 0x11112222U)
	{
		switch (eBrake)
		{
			case FCU_BRAKE__LEFT:

				//save	
				vEEPARAM__WriteU16(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO, sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_FilteredSample, 1U);

				//redo the CRC;
				vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);

				//1. Reload the structures.
				sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_ZERO);


				break;

			case FCU_BRAKE__RIGHT:
				//save	
				vEEPARAM__WriteU16(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO, sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_FilteredSample, 1U);

				//redo the CRC;
				vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);

				//1. Reload the structures.
				sFCU.sBrakes[(Luint32)eBrake].sMLP.u16ADC_Zero = u16EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_ZERO);
				break;

			default:
				//do nothing
				break;
		}

	}
	else
	{
		//something went wrong
	}
}


/***************************************************************************//**
 * @brief
 * Compute the calibration span value from the current brake pos
 * 
 * @param[in]		eBrake				The brake channel
 * @param[in]		u32Key				0x33334444U
 * @st_funcMD5		AA133F10248B752876733A4737ADC5A3
 * @st_funcID		LCCM655R0.FILE.024.FUNC.009
 */
void vFCU_BRAKES_MLP__ComputeCalibration_Span(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake)
{
	Lfloat32 f32Temp;

	if (u32Key == 0x33334444U)
	{
		switch (eBrake)
		{
			case FCU_BRAKE__LEFT:

				//current screw pos
				f32Temp = (Lfloat32)sFCU.sBrakes[(Luint8)eBrake].sMove.s32currentPos;
				//to mm
				f32Temp /= 1000.0F;
				f32Temp /= (Lfloat32)sFCU.sBrakes[(Luint32)eBrake].sMLP.s32ADC_Minus_Zero;

				//save	
				vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN, f32Temp, 1U);

				//redo the CRC;
				vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);

				//1. Reload the structures.
				sFCU.sBrakes[(Luint32)eBrake].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE0_SPAN);


				break;

			case FCU_BRAKE__RIGHT:
				//current screw pos
				f32Temp = (Lfloat32)sFCU.sBrakes[(Luint8)eBrake].sMove.s32currentPos;
				//to mm
				f32Temp /= 1000.0F;
				f32Temp /= (Lfloat32)sFCU.sBrakes[(Luint32)eBrake].sMLP.s32ADC_Minus_Zero;

				//save	
				vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN, f32Temp, 1U);

				//redo the CRC;
				vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_HEADER,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN,
														C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKES_CRC);

				//1. Reload the structures.
				sFCU.sBrakes[(Luint32)eBrake].sMLP.f32SystemSpan = f32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__BRAKE1_SPAN);

				break;

			default:
				//do nothing
				break;
		}

	}
	else
	{
		//something went wrong
	}
}

#ifdef WIN32

/***************************************************************************//**
 * @brief
 * On win32 fake the ADC values
 * 
 * @param[in]		u16Value				New ADC 2 ^ 12 max
 * @param[in]		u8Brake					Brake channel
 * @st_funcMD5		FE9BBEF7B50192E25F21E2048DF1AAC7
 * @st_funcID		LCCM655R0.FILE.024.FUNC.010
 */
void vFCU_BRAKES_MLP_WIN32__ForceADC(Luint8 u8Brake, Luint16 u16Value)
{
	sFCU.sBrakes[u8Brake].sMLP.sWin32.u16ADC_Sample = u16Value;
}

#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

