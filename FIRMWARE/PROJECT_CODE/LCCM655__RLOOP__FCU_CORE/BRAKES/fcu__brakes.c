/**
 * @file		FCU__BRAKES.C
 * @brief		Brake control subsystem for the FCU
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
 * @addtogroup FCU__BRAKES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

//locals
static void vFCU_BRAKES__Sample_ADC(E_FCU__BRAKE_INDEX_T eBrake);
static Lint16 s16FCU_BRAKES__Check_ADC_Limits(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake);
static void vFCU_BRAKES__Apply_Span(E_FCU__BRAKE_INDEX_T eBrake);

/***************************************************************************//**
 * @brief
 * Init any brakes variables, etc.
 * 
 *
 */
void vFCU_BRAKES__Init(void)
{

	Luint8 u8Counter;

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
		sFCU.sBrakes[u8Counter].sMLP.f32BrakePosition_Percent = 0.0F;

	}


	//todo, load the zero value from memory.



}


/***************************************************************************//**
 * @brief
 * Process any brakes tasks.
 * 
 */
void vFCU_BRAKES__Process(void)
{
	Lint16 s16Return;
	Luint8 u8Counter;

	//loop through each brake.
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_BRAKES; u8Counter++)
	{
		//Update the ADC:
		vFCU_BRAKES__Sample_ADC((E_FCU__BRAKE_INDEX_T)u8Counter);

		//check the limits
		s16Return = s16FCU_BRAKES__Check_ADC_Limits((E_FCU__BRAKE_INDEX_T)u8Counter);
		if(s16Return >= 0)
		{

			//the adc limits are safe, proceed

			//filter the data.

			//zero the data.
			vFCU_BRAKES__Apply_Zero((E_FCU__BRAKE_INDEX_T)u8Counter);

			//apply the span.
			vFCU_BRAKES__Apply_Span((E_FCU__BRAKE_INDEX_T)u8Counter);

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
 * Apply the system span value.
 *
 * @example
 * Brake_Pos = (ADCValue - Zero) * Span
 *
 */
void vFCU_BRAKES__Apply_Span(E_FCU__BRAKE_INDEX_T eBrake)
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
void vFCU_BRAKES__Apply_Zero(E_FCU__BRAKE_INDEX_T eBrake)
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


/***************************************************************************//**
 * @brief
 * Call this function to sample the ADC channel associated with the brake
 *
 */
void vFCU_BRAKES__Sample_ADC(E_FCU__BRAKE_INDEX_T eBrake)
{

	//determine the brake index
	switch(eBrake)
	{

		case FCU_BRAKE__LEFT:
			//read from the ADC
			sFCU.sBrakes[(Luint32)FCU_BRAKE__LEFT].sMLP.u16ADC_Sample = u16RM4_ADC_USER__Get_RawData(0U);
			break;

		case FCU_BRAKE__RIGHT:
			//read from the ADC
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
Lint16 s16FCU_BRAKES__Check_ADC_Limits(E_FCU__BRAKE_INDEX_T eBrake)
{
	Lint16 s16Return;

	//init vars
	s16Return = -1;


	//Todo

	//1. determine the brake index
	//2. check if the data is in range.
	//hint: sFCU.sBrakes[].u16ADC_Sample


	return s16Return;

}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

