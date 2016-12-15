/**
 * @file		BASIC_TYPES.H
 * @brief		Basic Type Def's for RM4 Systems
 * @note
 * MISRA-C Compliance
 * Rule 13 (Advisory)
 * This rule states that an application should not directly use basic types such as char, 
 * int, float etc. Instead specific-length equivalents should be typedefed for the 
 * specific compiler, and these type names should be used in the code. The reason is 
 * that different compilers could use different underlying representation for the basic 
 * types. The most common case is the type int that could be seen as 16 bit wide by one 
 * compiler and 32 bit wide by another.

 * Rule 10.6 (required):
 * A “U” suffix shall be applied to all constants of unsigned type.
 * The type of an integer constant is a potential source of confusion, because it is dependent on a
 * complex combination of factors including:
 * * The magnitude of the constant
 * * The implemented sizes of the integer types
 * * The presence of any suffixes
 * * The number base in which the value is expressed (i.e. decimal, octal or hexadecimal).

 * For example, the integer constant “40000” is of type int in a 32-bit environment but of type
 * long in a 16-bit environment. The value 0x8000 is of type unsigned int in a 16-bit environment, but of
 * type (signed) int in a 32-bit environment.

 * Note the following:
 * Any value with a “U” suffix is of unsigned type
 * An unsuffixed decimal value less than 2^31 is of signed type
 * But:
 * An unsuffixed hexadecimal value greater than or equal to 2^15 may be of signed or unsigned type
 * An unsuffixed decimal value greater than or equal to 2^ 31 may be of signed or unsigned type

 * Signedness of constants should be explicit. Consistent signedness is an important principle in
 * constructing well formed expressions. If a constant is of an unsigned type, it is helpful to avoid
 * ambiguity by applying a “U” suffix. When applied to larger values, the suffix may be redundant
 * (in the sense that it does not influence the type of the constant); however its presence is a valuable
 * contribution towards clarity.
 * 
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 */

#ifndef _BASIC_TYPES_H_
#define _BASIC_TYPES_H_
	
		/** This is needed by the FLASH API */
		#define _LITTLE_ENDIAN
		
		/** SIL3 define especially for use in Numerical Library */
		#define _WE_ARE_ON_RM4_

		#ifdef PCLINT_ENABLED
			/** For FLASH API on PCLINT */
			#define __TI_COMPILER_VERSION__
		#endif

		/** For Win32 DLL exporting */
		#ifdef WIN32
			#define DLL_DECLARATION extern "C" __declspec(dllexport)
		#else
			#define DLL_DECLARATION
		#endif

		/** Our local defined types 
		* PREFIX all our variable types with an "L"
		*/
		#ifdef WIN32
			//define these because we are no-longer on a RM4 platform
			#define Lint8 char
			#define Luint8 unsigned char
			#define Lint16 short int
			#define Luint16 unsigned short int
			#define Lint32 int
			#define Luint32 unsigned int
			#define Luint64 unsigned long long
			#define Lfloat32 float
			#define Lfloat64 double

		#else
			//RM4 Platform
			typedef unsigned char Luint8;
			typedef char Lint8;
			typedef unsigned short Luint16;
			typedef short Lint16;
			typedef unsigned int Luint32;
			typedef int Lint32;
			typedef float Lfloat32;
			typedef double Lfloat64;
			typedef unsigned long long Luint64;
			typedef signed long long Lint64;

		#endif

#endif//_BASIC_TYPES_H_
