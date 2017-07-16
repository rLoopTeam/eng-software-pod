#ifndef _H_BRIDGE_H_
#define _H_BRIDGE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		typedef enum
		{
			HBRIDGE_DIR__FORWARD = 0U,
			
			HBRIDGE_DIR__REVERSE
			
		}TE_HBRIDGE_DIR;

		/*******************************************************************************
		Structures
		*******************************************************************************/


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vHBRIDGE__Init(void);
		void vHBRIDGE__Process(void);
		
		
		
		//lowlevel
		void vHBRIDGE_LOWLEVEL__Init(void);
		void vHBRIDGE_LOWLEVEL__Process(void);
		void vHBRIDGE_LOWLEVEL__Set_Dir(Luint8 u8MotorIndex, TE_HBRIDGE_DIR eDir);
		
		
		
	#endif //#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_H_BRIDGE_H_

