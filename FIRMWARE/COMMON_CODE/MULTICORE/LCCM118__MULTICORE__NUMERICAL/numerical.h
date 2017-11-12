/**
 * @file		numerical.h
 * @brief		Numerical main header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 * 				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 * 				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 * 				under a license from the Lockie Group of companies, and may be used, copied
 * 				and/or disclosed only pursuant to the terms of that license agreement.
 * 				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM118R0.FILE.002
 */


#ifndef _MULTI_NUMERICAL_H_
#define _MULTI_NUMERICAL_H_

	/*******************************************************************************
	Includes
	*******************************************************************************/
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical__structs.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#if defined(WIN32) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__CC1310 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__CC1350 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__CC2650 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__CC3200 == 1U) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5659 == 1U)
			#define C_NUM__IS_LE  1U
		#else
			#define C_NUM__IS_LE  0U
		#endif


		//convert degrees to radians
		#define C_NUMERICAL__DEGREES_TO_RADIANS					(0.01745329251994329577F)
		//convert radians to degrees = 180/pi
		#define C_NUMERICAL__RADIANS_TO_DEGREES 				(57.2957795F)
		//Pi constant
		#define C_NUMERICAL__PI									(3.14159265358979323846F)
		//2x pi
		#define C_NUMERICAL__PI_X2								(6.28318530717958647692F)
		//Multiply PSI by this value to get kilogram-force/square mm
		#define C_NUMERICAL__PSI_TO_KGFMM2 						(0.0007030695783F)
		//e
		#define C_NUMERICAL__E									(2.7182818284590452354F)
		//log 2e
		#define C_NUMERICAL__LOG2E 								(1.4426950408889634074F)
		//log 10e
		#define C_NUMERICAL__LOG10E 							(0.43429448190325182765F)
		//log e2
		#define C_NUMERICAL__LN2 								(0.69314718055994530942F)
		//log e10
		#define C_NUMERICAL__LN10 								(2.30258509299404568402F)
		//pi/2
		#define C_NUMERICAL__PI_2 								(1.57079632679489661923F)
		//pi/4
		#define C_NUMERICAL__PI_4 								(0.78539816339744830962F)
		//1/pi
		#define C_NUMERICAL__1_PI 								(0.31830988618379067154F)
		//2/pi
		#define C_NUMERICAL__2_PI 								(0.63661977236758134308F)
		//2/sqrt(pi)
		#define C_NUMERICAL__2_SQRTPI 							(1.12837916709551257390F)
		//sqrt(2)
		#define C_NUMERICAL__SQRT2 								(1.41421356237309504880F)
		//1/sqrt(2)
		#define C_NUMERICAL__SQRT1_2 							(0.70710678118654752440F)

		//gravity accel.
		#define C_NUMERICAL__GRAVITY							(9.80665F)

		//externals
		#if C_LOCALDEF__LCCM118__ENABLE_TRIG == 1U
			extern const Lint32 s32SIL3_NUM_TRIG__COS_Table_X1024[361*8];
			extern const Lint32 s32SIL3_NUM_TRIG__SIN_Table_X1024[361*8];
		#endif//C_LOCALDEF__LCCM118__ENABLE_TRIG

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vSIL3_NUM__Init(void);

		//abs
		DLL_DECLARATION Lint32 s32SIL3_NUM_ABS__S32(Lint32 s32Value);
		DLL_DECLARATION Lint16 s16SIL3_NUM_ABS__S16(Lint16 s16Value);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_ABS__F32(Lfloat32 f32Value);

		//points.c
		#if C_LOCALDEF__LCCM118__ENABLE_POINTS == 1U
			DLL_DECLARATION Lfloat32 f32SIL3_NUM_POINTS__Length_BetweenPoints_2DPoints(const struct tsNUM_f32Point_2D *pt1, const struct tsNUM_f32Point_2D *pt2);
			DLL_DECLARATION Lfloat32 f32SIL3_NUM_POINTS__Length_BetweenPoints_S16(Lint16 s16AX, Lint16 s16AY, Lint16 s16BX, Lint16 s16BY);
			DLL_DECLARATION Lfloat32 f32SIL3_NUM_POINTS__Calculate_Mx_FromPoints_S16(Lint16 s16AX, Lint16 s16AY, Lint16 s16BX, Lint16 s16BY);
			void vSIL3_NUM_POINTS__Bounds_U162D(struct tsNUM_u16Point_2D *ptArray, Luint16 u16NumPoints, Luint16 *pu16MinX, Luint16 *pu16MinY, Luint16 *pu16MaxX, Luint16 *pu16MaxY);
			Luint16 u16SIL3_NUM_POINTS__Min(Luint16 u16A, Luint16 u16B);
			Lint16 s16SIL3_NUM_POINTS__Min(Lint16 s16A, Lint16 s16B);
			Luint16 u16SIL3_NUM_POINTS__Max(Luint16 u16A, Luint16 u16B);
			Lint16 s16SIL3_NUM_POINTS__Max(Lint16 s16A, Lint16 s16B);
			Luint8 u8SIL3_NUM_POINTS__Point_BetweenTwoS16(Lint16 s16A, Lint16 s16B, Lint16 s16TestPoint);
		#endif

		//power
        #if C_LOCALDEF__LCCM118__ENABLE_POWER == 1U
		    DLL_DECLARATION Lfloat32 f32SIL3_NUM_POWER__F32(Lfloat32 f32X, Lfloat32 f32Y);
		    DLL_DECLARATION Lfloat64 f64SIL3_NUM_POWER__F64(Lfloat64 f64X, Lfloat64 f64Y);
        #endif

		//conversions
		
		DLL_DECLARATION Luint16 u16SIL3_NUM_CONVERT__Array_LITTLEENDIAN(const Luint8 *pu8Array);
		DLL_DECLARATION Luint16 u16SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
		Luint16 u16SIL3_NUM_CONVERT__Array_2(const Luint8 * pu8Array);
		DLL_DECLARATION Lint16 s16SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
		Lint16 s16SIL3_NUM_CONVERT__Array_2(const Luint8 *pu8Array);
		DLL_DECLARATION Luint32 u32SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
		Luint32 u32SIL3_NUM_CONVERT__Array_2(const Luint8 *pu8Array);
		DLL_DECLARATION Luint32 u32SIL3_NUM_CONVERT__Array_LITTLEENDIAN(const Luint8 *pu8Array);
		DLL_DECLARATION Luint32 u32SIL3_NUM_CONVERT__Array_BIGENDIAN(const Luint8 *pu8Array);
		DLL_DECLARATION Lint32 s32SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_CONVERT__Array_BIGENDIAN(const Luint8 *pu8Array);
		#if C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U64 == 0U
			Lfloat64 f64SIL3_NUM_CONVERT__Array(const Luint8 *pu8Array);
			void vSIL3_NUM_CONVERT__Array_U64(Luint8 *pu8Array, Luint64 u64Value);
		#endif
	
		//arrays
		void vSIL3_NUM_ARRAY__Insert_U8(Luint8 *pu8Array, Luint8 u8ArrayLength, Luint8 u8InsertPosition, Luint8 u8InsertValue);

		//binary
		void vSIL3_NUM_BINARY__ToBitArray_U8(Luint8 u8Value, Luint8 *pu8Array);
		void vSIL3_NUM_BINARY__ToBitArray_U16(Luint16 u16Value, Luint8 *pu8Array);
		void vSIL3_NUM_BINARY__ToBitArray_U32(Luint32 u32Value, Luint8 *pu8Array);
		Luint8 u8SIL3_NUM_BINARY__FromBitArray(Luint8 *pu8Array);
		Luint16 u16SIL3_NUM_BINARY__FromBitArray(Luint8 *pu8Array);
		Luint32 u32SIL3_NUM_BINARY__FromBitArray(Luint8 *pu8Array);

		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U16(Luint8 *pu8Array, Luint16 u16Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U16_LITTLEENDIAN(Luint8 *pu8Array, Luint16 u16Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U16_BIGENDIAN(Luint8 *pu8Array, Luint16 u16Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_S16(Luint8 *pu8Array, Lint16 s16Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U32(Luint8 *pu8Array, Luint32 u32Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U32_BIGENDIAN(Luint8 *pu8Array, Luint32 u32Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_U32_LITTLEENDIAN(Luint8 *pu8Array, Luint32 u32Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_S32(Luint8 *pu8Array, Lint32 s32Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_F32(Luint8 *pu8Array, Lfloat32 f32Value);
		DLL_DECLARATION void vSIL3_NUM_CONVERT__Array_F32_LITTLEENDIAN(Luint8 *pu8Array, Lfloat32 f32Value);
		void vSIL3_NUM_CONVERT__Array_F64(Luint8 *pu8Array, Lfloat64 f64Value);
	
		//linear equations
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_LINEAR__CalculateM(Lint32 s32Rise, Lint32 s32Run);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_LINEAR__CalculateC(Lfloat32 f32M, Lint32 s32X, Lint32 s32Y);
	
		//mac
		DLL_DECLARATION Luint8 u8SIL3_NUM_MAC__Compare_MAC8(Luint8 *pu8MAC1, Luint8 *pu8MAC2);
		DLL_DECLARATION Luint8 u8SIL3_NUM_MAC__Compare_MAC6(Luint8 *pu8MAC1, Luint8 *pu8MAC2);
		DLL_DECLARATION Luint8 u8SIL3_NUM_MAC__Compare_MAC4(Luint8 *pu8MAC1, Luint8 *pu8MAC2);
		DLL_DECLARATION void vSIL3_NUM_MAC__Copy_MAC6(Luint8 *pu8SourceMAC6, Luint8 *pu8DestMAC6);
		void vSIL3_NUM_MAC__ASCII_To_MAC8(const Luint8 *pu8Array, Luint8 *pu8MAC);

		//vectors
		DLL_DECLARATION void vSIL3_NUM_VECTOR__CrossProduct(const struct tsNUM_f32Vector_3D *a, const struct tsNUM_f32Vector_3D *b, struct tsNUM_f32Vector_3D *out);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_VECTOR__Dot(const struct tsNUM_f32Vector_3D *a, const struct tsNUM_f32Vector_3D *b);
		DLL_DECLARATION void vSIL3_NUM_VECTOR__Normalize(struct tsNUM_f32Vector_3D *a);

		//filtering
		DLL_DECLARATION Lint16 s16SIL3_NUM_FILTERING__Add_S16(Lint16 s16Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lint16 *ps16Array);
		DLL_DECLARATION Luint16 u16SIL3_NUM_FILTERING__Add_U16(Luint16 u16Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Luint16 *pu16Array);
		DLL_DECLARATION Lint32 s32SIL3_NUM_FILTERING__Add_S32(Lint32 s32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lint32 *ps32Array);
		Luint32 u32SIL3_NUM_FILTERING__Add_U32(Luint32 u32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Luint32 *pu32Array);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_FILTERING__Add_F32(Lfloat32 f32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lfloat32 *pf32Array);

		//tolerance checks
		DLL_DECLARATION Luint8 u8SIL3_NUM_TOLERANCE__U16(Luint16 u16A, Luint16 u16B, Luint16 u16Tolerance);
		DLL_DECLARATION Luint8 u8SIL3_NUM_TOLERANCE__S16(Lint16 s16A, Lint16 s16B, Luint16 u16Tolerance);
		DLL_DECLARATION Luint8 u8SIL3_NUM_TOLERANCE__F32(Lfloat32 f32A, Lfloat32 f32B, Lfloat32 f32Tolerance);
		DLL_DECLARATION Luint8 u8SIL3_NUM_TOLERANCE__U32(Luint32 u32A, Luint32 u32B, Luint32 u32Tolerance);
		DLL_DECLARATION Luint8 u8SIL3_NUM_TOLERANCE__F64(Lfloat64 f64A, Lfloat32 f64B, Lfloat64 f64Tolerance);

		//trig
		DLL_DECLARATION void vSIL3_NUM_TRIG__Init_Tables(void);
		Lfloat32 f32SIL3_NUM_TRIG__ArcTan2(Lfloat32 y, Lfloat32 x);
		Lfloat32 f32SIL3_NUM_TRIG__Atan(Lfloat32 f32Radians);
		Lfloat32 f32SIL3_NUM_TRIG__Atan2(Lfloat32 f32A, Lfloat32 f32B);
		Lfloat32 f32SIL3_NUM_TRIG__Cosine(Lfloat32 f32Radians);
		Lfloat64 f64SIL3_NUM_TRIG__Cosine(Lfloat64 f64Radians);
		Lfloat32 f32SIL3_NUM_TRIG__Sine(Lfloat32 f32Radians);
		Lfloat64 f64SIL3_NUM_TRIG__Sine(Lfloat64 f64Radians);
		Lfloat32 f32SIL3_NUM_TRIG__ArcSine(Lfloat32 f32Radians);
		Lfloat64 f64SIL3_NUM_TRIG__Tan(Lfloat64 f64Radians);

		//float
		DLL_DECLARATION Luint8 u8SIL3_NUM_FLOAT__IsZero(Lfloat32 f32Test);
		DLL_DECLARATION Luint8 u8SIL3_NUM_FLOAT64__IsZero(Lfloat64 f64Test);
		DLL_DECLARATION Luint8 u8SIL3_NUM_FLOAT__Is_NAN(Lfloat32 f32Value);
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_FLOAT__ABS(Lfloat32 f32Value);
		DLL_DECLARATION Lfloat64 f64SIL3_NUM_FLOAT64__ABS(Lfloat64 f64Value);
		Lfloat32 f32SIL3_NUM_SQRT__F32(Lfloat32 f32Value);
		Lfloat64 f64SIL3_NUM_FLOAT__SQRT(Lfloat64 f64Value);
		Lfloat64 f64SIL3_NUM_FLOAT__Log(Lfloat64 f64Value);
	
		//polynomial
		DLL_DECLARATION Lfloat32 f32SIL3_NUM_POLY__PolyVal(Lfloat32 *pf32Poly, Luint32 u32PolySize, Lfloat32 f32X);
	
		//matrix
		void vSIL3_NUM_MATRIX__Mult(Luint32 aRows, Luint32 aCols_bRows, Luint32 bCols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
		void vSIL3_NUM_MATRIX__Mult_3X3(const Lfloat32 a[3][3], const Lfloat32 b[3][3], Lfloat32 mat[3][3]);
		void vSIL3_NUM_MATRIX__Add(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
		void vSIl3_NUM_MATRIX__Sub(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
		void vSIL3_NUM_MATRIX__Scale(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], Lfloat32 scaler, const Lfloat32 matrixA[]);
		void vSIL3_NUM_MATRIX__Transpose_3X3(Lfloat32 matrixC[9], const Lfloat32 matrixA[9]);
		void vSIL3_NUM_MATRIX__Inverse_3X3(Lfloat32 matrixC[9], const Lfloat32 matrixA[9]);
	
		//circle
		Lfloat32 f32SIL3_NUM_CIRCLE__Area_Radius(Luint16 u16Radius);
		Lfloat32 f32SIL3_NUM_CIRCLE__Area_Diameter(Luint16 u16Diameter);
	
		//strings
		#if C_LOCALDEF__LCCM118__ENABLE_STRINGS == 1U
			Luint8 u8SIL3_NUM_STRING__ToLower(Luint8 u8Char);
			Luint8 u8SIL3_NUM_STRING__ToUpper(Luint8 u8Char);
			Luint16 u16SIL3_NUM_STRING__Get_Length(const Luint8 *pString);
			Luint16 u16SIL3_NUM_STRING__Get_Length_ExcludeNewline(const Luint8 *pString);
			Lint16 s16SIL3_NUM_STRING__Compare(const Luint8 *pS1, const Luint8 *pS2);
			Luint8 u8SIL3_NUM_STRING__ASCII_To_Hex(Luint8 u8Char);
			Luint8 u8SIL3_NUM_STRING__Is_Digit(Luint8 u8Char);
			Lint16 s16SIL3_NUM_STRING__Scan_Format_S16(const Luint8 *cpu8String, const Luint8 *cpu8Format, Lint16 *p16ReturnArray, Luint16 u16MaxArray);
			Lint16 s16SIL3_NUM_STRING__String_Token(Luint16 u16StringLength, Luint8 *pu8InputString, Luint16 u16TokenLength, const Luint8 *pu8TokenString, Luint16 *pu16TokenPosition);
			Lint16 s16SIL3_NUM_STRING__String_Tokens(Luint8 *pu8InputString, const Luint8 *pu8TokenString, Luint16 *pu16TokenPositions, Luint16 u16MaxTokens);
			void vSIL3_NUM_STRING__Reverse(Luint8 *pu8Buffer, Luint16 u16Length);
			Luint16 u16SIL3_NUM_STRING__String_To_U8Array(Luint8 *pu8Buffer, Luint16 u16MaxLength, const Luint8 *cpu8String);

			Luint16 u16SIL3_NUM_STRING__S32_To_U8Array(Lint32 s32Value, Luint8 *pu8Buffer, Luint8 u16BufferLength, Luint8 u8DecimalPoints, Luint8 u8ForcePosNeg);
			#if C_LOCALDEF__LCCM118__ENABLE_POWER == 1U
				Luint16 u16SIL3_NUM_STRING__F32_To_U8Array(Lfloat32 f32Value, Luint8 *pu8Buffer, Luint8 u8BufferMax, Luint8 u8LeadingPoints, Luint8 u8DecimalPoints, Luint8 u8ForcePosNeg);
			#endif //C_LOCALDEF__LCCM118__ENABLE_POWER
		#endif

		//Min and Max functions
		Luint32 u32SIL3_NUM_MINMAX__Min(Luint32 u32A, Luint32 u32B);
		Luint32 u32SIL3_NUM_MINMAX__Max(Luint32 u32A, Luint32 u32B);

		#if C_LOCALDEF__LCCM118__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM118_TS_001(void);
			DLL_DECLARATION void vLCCM118_TS_002(void);
			DLL_DECLARATION void vLCCM118_TS_003(void);
			DLL_DECLARATION void vLCCM118_TS_004(void);
			DLL_DECLARATION void vLCCM118_TS_005(void);
			DLL_DECLARATION void vLCCM118_TS_006(void);
			DLL_DECLARATION void vLCCM118_TS_007(void);
			DLL_DECLARATION void vLCCM118_TS_008(void);
			DLL_DECLARATION void vLCCM118_TS_009(void);
			DLL_DECLARATION void vLCCM118_TS_010(void);
			DLL_DECLARATION void vLCCM118_TS_011(void);
			DLL_DECLARATION void vLCCM118_TS_012(void);
			DLL_DECLARATION void vLCCM118_TS_013(void);
			DLL_DECLARATION void vLCCM118_TS_014(void);
			DLL_DECLARATION void vLCCM118_TS_015(void);
			DLL_DECLARATION void vLCCM118_TS_016(void);
			DLL_DECLARATION void vLCCM118_TS_017(void);
			DLL_DECLARATION void vLCCM118_TS_018(void);
			DLL_DECLARATION void vLCCM118_TS_019(void);
			DLL_DECLARATION void vLCCM118_TS_020(void);
			DLL_DECLARATION void vLCCM118_TS_021(void);
			DLL_DECLARATION void vLCCM118_TS_022(void);
			DLL_DECLARATION void vLCCM118_TS_026(void);
			DLL_DECLARATION void vLCCM118_TS_027(void);
			DLL_DECLARATION void vLCCM118_TS_028(void);
			DLL_DECLARATION void vLCCM118_TS_029(void);
			DLL_DECLARATION void vLCCM118_TS_030(void);
			DLL_DECLARATION void vLCCM118_TS_031(void);
			DLL_DECLARATION void vLCCM118_TS_035(void);
			DLL_DECLARATION void vLCCM118_TS_036(void);
			DLL_DECLARATION void vLCCM118_TS_037(void);
			DLL_DECLARATION void vLCCM118_TS_038(void);
			DLL_DECLARATION void vLCCM118_TS_039(void);
			DLL_DECLARATION void vLCCM118_TS_040(void);
			DLL_DECLARATION void vLCCM118_TS_041(void);
			DLL_DECLARATION void vLCCM118_TS_042(void);
			DLL_DECLARATION void vLCCM118_TS_043(void);
			DLL_DECLARATION void vLCCM118_TS_044(void);
			DLL_DECLARATION void vLCCM118_TS_045(void);
			DLL_DECLARATION void vLCCM118_TS_046(void);
			DLL_DECLARATION void vLCCM118_TS_047(void);
			DLL_DECLARATION void vLCCM118_TS_048(void);
			DLL_DECLARATION void vLCCM118_TS_049(void);
			DLL_DECLARATION void vLCCM118_TS_050(void);
			DLL_DECLARATION void vLCCM118_TS_051(void);
			DLL_DECLARATION void vLCCM118_TS_052(void);
			DLL_DECLARATION void vLCCM118_TS_053(void);
			DLL_DECLARATION void vLCCM118_TS_054(void);
			DLL_DECLARATION void vLCCM118_TS_055(void);
			DLL_DECLARATION void vLCCM118_TS_056(void);
			DLL_DECLARATION void vLCCM118_TS_057(void);
			DLL_DECLARATION void vLCCM118_TS_058(void);
			DLL_DECLARATION void vLCCM118_TS_059(void);
			DLL_DECLARATION void vLCCM118_TS_060(void);
	
			DLL_DECLARATION void vLCCM118R0_TS_061(void);
			DLL_DECLARATION void vLCCM118R0_TS_062(void);
			DLL_DECLARATION void vLCCM118R0_TS_063(void);
			DLL_DECLARATION void vLCCM118R0_TS_064(void);
			DLL_DECLARATION void vLCCM118R0_TS_065(void);
			DLL_DECLARATION void vLCCM118R0_TS_066(void);
			DLL_DECLARATION void vLCCM118R0_TS_067(void);
			DLL_DECLARATION void vLCCM118R0_TS_068(void);
			DLL_DECLARATION void vLCCM118R0_TS_069(void);
			DLL_DECLARATION void vLCCM118R0_TS_070(void);
			DLL_DECLARATION void vLCCM118R0_TS_071(void);
			DLL_DECLARATION void vLCCM118R0_TS_072(void);
			DLL_DECLARATION void vLCCM118R0_TS_073(void);
			DLL_DECLARATION void vLCCM118R0_TS_074(void);
			DLL_DECLARATION void vLCCM118R0_TS_075(void);
			DLL_DECLARATION void vLCCM118R0_TS_076(void);
			DLL_DECLARATION void vLCCM118R0_TS_077(void);
			DLL_DECLARATION void vLCCM118R0_TS_078(void);
			DLL_DECLARATION void vLCCM118R0_TS_079(void);
			DLL_DECLARATION void vLCCM118R0_TS_080(void);
			DLL_DECLARATION void vLCCM118R0_TS_081(void);
			DLL_DECLARATION void vLCCM118R0_TS_082(void);
			DLL_DECLARATION void vLCCM118R0_TS_083(void);
			DLL_DECLARATION void vLCCM118R0_TS_084(void);
			DLL_DECLARATION void vLCCM118R0_TS_085(void);
			DLL_DECLARATION void vLCCM118R0_TS_086(void);
			DLL_DECLARATION void vLCCM118R0_TS_087(void);
			DLL_DECLARATION void vLCCM118R0_TS_088(void);
			DLL_DECLARATION void vLCCM118R0_TS_089(void);
			DLL_DECLARATION void vLCCM118R0_TS_090(void);
			DLL_DECLARATION void vLCCM118R0_TS_091(void);
			DLL_DECLARATION void vLCCM118R0_TS_092(void);
			DLL_DECLARATION void vLCCM118R0_TS_093(void);
			DLL_DECLARATION void vLCCM118R0_TS_094(void);
			DLL_DECLARATION void vLCCM118R0_TS_095(void);
			DLL_DECLARATION void vLCCM118R0_TS_096(void);
			DLL_DECLARATION void vLCCM118R0_TS_097(void);
			DLL_DECLARATION void vLCCM118R0_TS_098(void);
			DLL_DECLARATION void vLCCM118R0_TS_099(void);
			//DLL_DECLARATION void vLCCM118R0_TS_101(void); //numerical__poly.c funtion not working description in TS_101
			DLL_DECLARATION void vLCCM118R0_TS_102(void);
			DLL_DECLARATION void vLCCM118R0_TS_103(void);
			DLL_DECLARATION void vLCCM118R0_TS_104(void);
			DLL_DECLARATION void vLCCM118R0_TS_105(void);
			DLL_DECLARATION void vLCCM118R0_TS_106(void);
			DLL_DECLARATION void vLCCM118R0_TS_107(void);
			DLL_DECLARATION void vLCCM118R0_TS_108(void);
			DLL_DECLARATION void vLCCM118R0_TS_109(void);
			DLL_DECLARATION void vLCCM118R0_TS_110(void);
			DLL_DECLARATION void vLCCM118R0_TS_111(void);
			DLL_DECLARATION void vLCCM118R0_TS_112(void);
			DLL_DECLARATION void vLCCM118R0_TS_113(void);
			DLL_DECLARATION void vLCCM118R0_TS_114(void);
			DLL_DECLARATION void vLCCM118R0_TS_115(void);
		#endif

	//safetys
	#ifndef C_LOCALDEF__LCCM118__ENABLE_TRIG
		#error
	#endif
	
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE
#endif
