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

Lfloat32 f32_Current_Filter_ADC_Value(Lfloat32 ADC_Sample);

/***************************************************************************//**
 * @brief
 * Init the charger voltage and current measurement
 * 
 * @st_funcMD5		60D7C48E9A55F549B328B969C6A38605
 * @st_funcID		LCCM653R0.FILE.023.FUNC.001
 */
void vPWRNODE_CHG_IV__Init(void)
{
	vFAULTTREE__Init(&sPWRNODE.sHASS600.sFaultFlags);

	//the ADC is already init

	//Zero
	sPWRNODE.sHASS600.f32HASS_VoltageOffSet = f32RM4_ADC_USER__Get_Voltage(0U);
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
	Lfloat32 f32Voltage_Sample;


	//Sample the ADC channels if new data is available
#ifndef WIN32
	u8New = u8RM4_ADC_USER__Is_NewDataAvailable();
#else
	u8New = 1U;
#endif
	if(u8New == 1U)
	{

		//get the ADC data for each channel
		// * CHARGE CURRENT		INPUT			AD1:08
		// * BATTERY VOLTAGE		INPUT			AD1:09
		// * CHARGE VOLTAGE		INPUT			AD1:10
		f32Voltage_Sample = f32RM4_ADC_USER__Get_Voltage(0U) - sPWRNODE.sHASS600.f32HASS_VoltageOffSet;

		//Convert voltage reading to current reading
		sPWRNODE.sHASS600.f32HASS_CurrentReading = f32_Current_Filter_ADC_Value( 906.59F * f32Voltage_Sample - 2219.5F);


		//todo
		//scale the data correctly for each sensor

		//filter the scaled data or filter on the raw data

		//TODO Change 999999 limit to something like 600 Amps?
		//set any alarms (flags based on any limits)
		if (sPWRNODE.sHASS600.f32HASS_CurrentReading > 999999)
		{
			vFAULTTREE__Set_Flag(&sPWRNODE.sHASS600.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX__00);
			vFAULTTREE__Set_Flag(&sPWRNODE.sHASS600.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX_MASK__00);
		}

		//taken the data now
		vRM4_ADC_USER__Clear_NewDataAvailable();

	}
	else
	{
		//adc not ready yet, don't do anything
	}
}

/***************************************************************************//**
 * @brief
 * Average the current readings
 *
 * @st_funcMD5		AF5EF4D90978E6F62271760FF836E754
 * @st_funcID		LCCM653R0.FILE.023.FUNC.002
 */

Lfloat32 f32_Current_Filter_ADC_Value(Lfloat32 ADC_Sample)
{
	Lfloat32 f32Return;

	f32Return = f32NUMERICAL_FILTERING__Add_F32(	ADC_Sample,
												&sPWRNODE.sHASS600.u16HAAS_Current_Average_Counter,
												C_PWRCORE__CURRENT_AVG_SIZE,
												&sPWRNODE.sHASS600.f32HAAS_Current_Average_Array[0]);

	return f32Return;
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

