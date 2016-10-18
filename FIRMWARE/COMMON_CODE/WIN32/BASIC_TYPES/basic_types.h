//(C) SIL3 P/L, All Rights Reserved
//WIN32 Emulation basic type defs.
#ifndef _BASIC_TYPES_H_
#define _BASIC_TYPES_H_
	
	#define DLL_DECLARATION extern "C" __declspec(dllexport)

	//https://msdn.microsoft.com/en-us/library/cc953fe1.aspx
	#define Lint8 char
	#define Luint8 unsigned char
	#define Lint16 short int
	#define Luint16 unsigned short int
	#define Lint32 int
	#define Luint32 unsigned int
	#define Lfloat32 float
	#define Lfloat64 double
	#define Luint64 unsigned long long
	#define Lint64 signed long long

#endif//_BASIC_TYPES_H_
