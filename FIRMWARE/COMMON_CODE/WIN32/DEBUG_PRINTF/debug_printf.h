//(C) SIL3 P/L
//WIN32 debugging support
#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_

	#include <localdef.h>

	//setup our debug statement
	#define DEBUG_PRINT(x) vSIL3_DEBUG_PRINTF_WIN32__Win32Callback(x)
	
	#ifdef WIN32
		//this is the callback function type
		typedef void (__cdecl * pSIL3_DEBUG_PRINTF_Callback_FuncType)(const char * pu8String);
		//these are the function definitions
		extern "C" __declspec(dllexport) void __cdecl vSIL3_DEBUG_PRINTF_WIN32__Set_Callback(pSIL3_DEBUG_PRINTF_Callback_FuncType pFunc);

		void vSIL3_DEBUG_PRINTF_WIN32__Win32Callback(const char * pu8String);
	
	#endif


#endif