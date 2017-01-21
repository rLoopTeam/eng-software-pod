/**
 * @file		POWER__IV_MEASURE.C
 * @brief		Charger current and voltage measurement
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__IV_MEASURE
 * @ingroup POWER_NODE
 * @{ */

#include "../../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

#define ADCREFERENCEVOLTAGE				(3.3F)

extern struct _strPWRNODE sPWRNODE;


/***************************************************************************//**
 * @brief
 * Init the charger voltage and current measurement
 * 
 * @st_funcMD5		60D7C48E9A55F549B328B969C6A38605
 * @st_funcID		LCCM653R0.FILE.023.FUNC.001
 */
void vPWRNODE_CHG_IV__Init(void)
{

	//the ADC is already init

}

/***************************************************************************//**
 * @brief
 * Process the charger voltage and current measurement.
 * 
 * @st_funcMD5		AF5EF4D90978E6F62271760FF836E754
 * @st_funcID		LCCM653R0.FILE.023.FUNC.002
 */
void vPWRNODE_CHG_IV__Process(void)
{
	Luint8 u8New;
	Lfloat32 f32ADC_REF;
	Lfloat32 f32ADC_Sample;


	//Sample the ADC channels if new data is available
	u8New = u8RM4_ADC_USER__Is_NewDataAvailable();
	if(u8New == 1U)
	{

		//get the ADC data for each channel
		// * CHARGE CURRENT		INPUT			AD1:08
		// * BATTERY VOLTAGE		INPUT			AD1:09
		// * CHARGE VOLTAGE		INPUT			AD1:10
		f32ADC_Sample = u16RM4_ADC_USER__Get_RawData(0U);
		f32ADC_REF = u16RM4_ADC_USER__Get_RawData(1U);

		//Convert ADC to current reading
		sPWRNODE.sHASS600.f32HASS_CurrentReading = (f32ADC_Sample - f32ADC_REF) * (ADCREFERENCEVOLTAGE/4096) * 600/0.625F;


		//todo
		//scale the data correctly for each sensor

		//filter the scaled data or filter on the raw data

		//set any alarms (flags based on any limits)

		//taken the data now
		vRM4_ADC_USER__Clear_NewDataAvailable();

	}
	else
	{
		//adc not ready yet
	}
}

//todo: provide functions to get the current voltages and currents as well as any fault flags.


#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER
#ifndef C_LOCALDEF__LCCM653__ENABLE_CHARGER
	#error
#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

