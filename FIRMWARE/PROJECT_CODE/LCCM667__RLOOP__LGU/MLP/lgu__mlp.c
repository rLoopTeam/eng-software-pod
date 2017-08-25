#include "../lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM667__ENABLE_MLP == 1U

extern TS_LGU__MAIN sLGU;

void vLGU_MLP__Init(void)
{
	Luint8 u8Counter;


	for(u8Counter = 0U; u8Counter < C_LGU__NUM_MLP; u8Counter++)
	{
		sLGU.sMLP[u8Counter].u16ADC_Raw = 0U;
	}
}

void vLGU_MLP__Process(void)
{
	Luint8 u8Counter;

	//process the ADC channels
	vRM4_ADC_USER__Process();

	if(u8RM4_ADC_USER__Is_NewDataAvailable() == 1U)
	{
		//get the data for each of our devices
		for(u8Counter = 0U; u8Counter < C_LGU__NUM_MLP; u8Counter++)
		{
			sLGU.sMLP[u8Counter].u16ADC_Raw = u16RM4_ADC_USER__Get_AveragedData(u8Counter);
		}

		//clear the flag now we are done with it
		vRM4_ADC_USER__Clear_NewDataAvailable();

		//starts a new conversion, now that the old one is done with
		vRM4_ADC_USER__StartConversion();
	}
	else
	{
	//do nothing
	}

}

#endif //C_LOCALDEF__LCCM667__ENABLE_MLP
#ifndef C_LOCALDEF__LCCM667__ENABLE_MLP
	#error
#endif
#endif//
