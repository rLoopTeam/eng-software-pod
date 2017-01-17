/**
 * @file		LGU.H
 * @brief		Landing Gear Control Unit
 * @author		Lachlan, Frank
 * @copyright	rLoop Inc.
 */

 
#ifndef _LGU_H_
#define _LGU_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vLGU__Init(void);
		void vLGU__Process(void);
		void vLGU__RTI_100MS_ISR(void);
		void vLGU__RTI_10MS_ISR(void);

	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_LGU_H_

