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

	//init the state machine variables
	sFCU.eBrakeStates = BRAKE_STATE__IDLE;

	//init the limit switches
	vFCU_BRAKES_SW__Init();

	//init the MLP sensor
	vFCU_BRAKES_MLP__Init();

	//init the stepper rotate module
	vFCU_BRAKES_STEP__Init();




}


/***************************************************************************//**
 * @brief
 * Process any brakes tasks.
 * 
 */
void vFCU_BRAKES__Process(void)
{
	//process the stepper driver if its active
	vSTEPDRIVE__Process();

	switch(sFCU.eBrakeStates)
	{

		case BRAKE_STATE__IDLE:
			//idle state, wait here until we are commanded to move via a chance state.
			break;

		case BRAKE_STATE__BEGIN_MOVE:
			//begin to move the brakes, setup the movement planner
			//compare brake distances with known postion, limit switch postion and MLP position before moving.
			//alert upper layer if movement not possible due to position sensor error
			break;

		case BRAKE_STATE__MOVING:
			//the brakes are moving,
			//monitor their performance by getting the current pos from the move planner
			//check the MLP (it will lag)
			//process any PID algo's here too
			break;

		case BRAKE_STATE__MOVE_STOPPED:
			//once we have completed moving, switch to stop state

			//once stopped go back to idle state
			break;


		case BRAKE_STATE__FAULT:

			//a fault has occurred
			break



	}

}

//move the brakes to a distance in MM from the I Beam
//approx distances are 25mm (fully open) to 0mm (fully closed)
//some calibration will be needed here.
void vFCU_BRAKES__Move_IBeam_Distance_MM(Lfloat32 f32Distance)
{

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





#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

