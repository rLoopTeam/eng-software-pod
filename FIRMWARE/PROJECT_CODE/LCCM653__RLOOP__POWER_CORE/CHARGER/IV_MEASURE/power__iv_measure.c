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

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

extern struct _strPWRNODE sPWRNODE;


void vPWRNODE_CHG_IV__Init(void)
{

	//the ADC is already init

}

void vPWRNODE_CHG_IV__Process(void)
{
	Luint8 u8New;

	//Sample the ADC channels if new data is available
	u8New = u8RM4_ADC_USER__Is_NewDataAvailable();
	if(u8New == 1U)
	{

		//get the ADC data for each channel
		// * CHARGE CURRENT		INPUT			AD1:08
		// * BATTERY VOLTAGE		INPUT			AD1:09
		// * CHARGE VOLTAGE		INPUT			AD1:10
		u16RM4_ADC_USER__Get_RawData(0U);

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

