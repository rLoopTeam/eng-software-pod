/**
 * @file		FCU_CORE.H
 * @brief		Main header for the FCU
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.001
 */

#ifndef _FCU_CORE_H_
#define _FCU_CORE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vFCU__Init(void);
		void vFCU__Process(void);
		
		
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

