/**
 * @file		tsys01.h
 * @brief		Pressure Vessel Temperature Sensor
 * @author		Dean
 * @copyright	rLoop Inc.
 * @st_fileID	
 */

/* TSYS01 DATASHEET: https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwjutOLC54HQAhVmj1QKHRrAAUIQFggkMAA&url=http%3A%2F%2Fwww.te.com%2Fcommerce%2FDocumentDelivery%2FDDEController%3FAction%3Dsrchrtrv%26DocNm%3DTSYS01%26DocType%3DData%2BSheet%26DocLang%3DEnglish&usg=AFQjCNEkhORJ0w3T3VXH99vjER0cTqTaeQ 
*/


// File intent is to address issues listed here: https://github.com/rLoopTeam/eng-software-pod/milestone/1


#ifndef _TSYS01_H_
#define _TSYS01_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		/** enum type for tsys01 temperature coefficient addresses (k values) */
		typedef enum
		{ 
			k4_ADR = 0xA2,
	    	k3_ADR = 0xA4,
	    	k2_ADR = 0xA6,
	    	k1_ADR = 0xA8,
	    	k0_ADR = 0xAA
	    }E_K_COEFF_ADR;

		/** enum type for all other tsys01 addresses */
		typedef enum
		{
			RESET = 0x1E,
			START_ADC_TEMPERATURE_CONVERSION = 0x48,
			READ_ADC_TEMPERATURE_RESULT = 0x00,
			PROM_READ_ADDRESS_0 = 0xA0,
			PROM_READ_ADDRESS_6 = 0xAC,
			PROM_READ_ADDRESS_7 = 0xAE
		}E_TSYS01_ADRS;


		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vTSYS01__Init(void);
		void vTSYS01__Process(void);
		
		
	#endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_TSYS01_H_

