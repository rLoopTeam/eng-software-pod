#ifndef _H_BRIDGE_H_
#define _H_BRIDGE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		typedef enum
		{
			
			/** No direction, set off */
			HBRIDGE_DIR__NONE = 0U,

			/** Rotate forward */
			HBRIDGE_DIR__FORWARD,

			/** Rotate in reverse */
			HBRIDGE_DIR__REVERSE
			
		}TE_HBRIDGE_DIR;

		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vSIL3_HBRIDGE__Init(void);
		void vSIL3_HBRIDGE__Process(void);
		
		
		
		//lowlevel
		void vSIL3_HBRIDGE_LOWLEVEL__Init(void);
		void vSIL3_HBRIDGE_LOWLEVEL__Process(void);
		void vSIL3_HBRIDGE_LOWLEVEL__Set_Dir(Luint8 u8MotorIndex, TE_HBRIDGE_DIR eDir);
		
		
		
	#endif //#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_H_BRIDGE_H_

