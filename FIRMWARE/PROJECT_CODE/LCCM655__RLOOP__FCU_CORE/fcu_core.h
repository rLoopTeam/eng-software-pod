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

		//state machine types
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__types.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/
		/** main flight control structure */
		struct _strFCU
		{
			/** The init statemachine */
			E_FCU__INIT_STATE_TYPES eInitStates;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vFCU__Init(void);
		DLL_DECLARATION void vFCU__Process(void);
		
		
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

