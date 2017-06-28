#ifndef _HE_THERM_H_
#define _HE_THERM_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		//cross system networking types
		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		typedef struct
		{

			/** Ethernet Systems */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6U];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4U];
			}sEthernet;


		}TS_HET__MAIN;

		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vHETHERM__Init(void);
		void vHETHERM__Process(void);

	#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_HE_THERM_H_

