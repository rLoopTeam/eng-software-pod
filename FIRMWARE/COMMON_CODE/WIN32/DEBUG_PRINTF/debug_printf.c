//(C) SIL3 P/L
//WIN32 debugging support
#include "debug_printf.h"
#ifdef WIN32

//this is our function pointer
pDEBUG_PRINTF_Callback_FuncType pDebugFunc;

//Set the callback
DLL_DECLARATION void vDEBUG_PRINTF_WIN32__Set_Callback(pDEBUG_PRINTF_Callback_FuncType pFunc)
{

	pDebugFunc = pFunc;
}

//allow the firmware to callback to WIN32
void vDEBUG_PRINTF_WIN32__Win32Callback(const char * pu8String)
{
	//allocate enough space for large strings
	Luint8 u8Buffer[1024];
	Luint8 u8Counter;
	u8Counter = 0;

	//copy over while we are not at the end of the string
	do
	{
		u8Buffer[u8Counter] = pu8String[u8Counter];
		u8Counter++;
	}while(pu8String[u8Counter] != 0x00);

	pDebugFunc((const char *)pu8String);
}


#endif //
