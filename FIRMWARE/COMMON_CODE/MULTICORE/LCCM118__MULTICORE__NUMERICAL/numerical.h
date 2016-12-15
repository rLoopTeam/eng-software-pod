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
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM118R0.FILE.002
 */

//Math Type Defs and numerical helpers
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
		extern const Lint32 s32NUMERICAL__COS_Table_X1024[361*8];
		extern const Lint32 s32NUMERICAL__SIN_Table_X1024[361*8];
	#endif//C_LOCALDEF__LCCM118__ENABLE_TRIG

	/*******************************************************************************
	Function Prototypes
	*******************************************************************************/
	DLL_DECLARATION void vNUMERICAL__Init(void);
	
	//abs
	DLL_DECLARATION Lint32 s32NUMERICAL__ABS(Lint32 s32Value);
	DLL_DECLARATION Lint16 s16NUMERICAL__ABS(Lint16 s16Value);
	DLL_DECLARATION Lfloat32 f32NUMERICAL__ABS(Lfloat32 f32Value);
	
	//points.c
	DLL_DECLARATION Lfloat32 f32NUMERICAL_POINTS__Length_BetweenPoints_2DPoints(const struct tsNUM_f32Point_2D *pt1, const struct tsNUM_f32Point_2D *pt2);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_POINTS__Length_BetweenPoints_S16(Lint16 s16AX, Lint16 s16AY, Lint16 s16BX, Lint16 s16BY);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_POINTS__Calculate_Mx_FromPoints_S16(Lint16 s16AX, Lint16 s16AY, Lint16 s16BX, Lint16 s16BY);
	void vNUMERICAL_POINTS__Bounds_U162D(struct tsNUM_u16Point_2D *ptArray, Luint16 u16NumPoints, Luint16 *pu16MinX, Luint16 *pu16MinY, Luint16 *pu16MaxX, Luint16 *pu16MaxY);
	Luint16 u16NUMERICAL_POINTS__Min(Luint16 u16A, Luint16 u16B);
	Lint16 s16NUMERICAL_POINTS__Min(Lint16 s16A, Lint16 s16B);
	Luint16 u16NUMERICAL_POINTS__Max(Luint16 u16A, Luint16 u16B);
	Lint16 s16NUMERICAL_POINTS__Max(Lint16 s16A, Lint16 s16B);
	Luint8 u8NUMERICAL_POINTS__Point_BetweenTwoS16(Lint16 s16A, Lint16 s16B, Lint16 s16TestPoint);

	//power
	DLL_DECLARATION Lfloat32 f32NUMERICAL__Power(Lfloat32 f32X, Lfloat32 f32Y);
	DLL_DECLARATION Lfloat64 f64NUMERICAL__Power(Lfloat64 f64X, Lfloat64 f64Y);
	
	//conversions
	Luint8 u8NUMERICAL_CONVERT__ASCII_To_Hex(Luint8 u8Char);
	void vNUMERICAL_CONVERT__ASCIIArray_To_MAC8(const Luint8 *pu8Array, Luint8 *pu8MAC);
	DLL_DECLARATION Luint16 u16NUMERICAL_CONVERT__Array_LITTLEENDIAN(const Luint8 *pu8Array);
	DLL_DECLARATION Luint16 u16NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);
	Luint16 u16NUMERICAL_CONVERT__Array_2(const Luint8 * pu8Array);
	DLL_DECLARATION Lint16 s16NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);
	Lint16 s16NUMERICAL_CONVERT__Array_2(const Luint8 *pu8Array);
	DLL_DECLARATION Luint32 u32NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);
	Luint32 u32NUMERICAL_CONVERT__Array_2(const Luint8 *pu8Array);
	DLL_DECLARATION Luint32 u32NUMERICAL_CONVERT__Array_LITTLEENDIAN(const Luint8 *pu8Array);
	DLL_DECLARATION Luint32 u32NUMERICAL_CONVERT__Array_BIGENDIAN(const Luint8 *pu8Array);
	DLL_DECLARATION Lint32 s32NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_CONVERT__Array_BIGENDIAN(const Luint8 *pu8Array);
	Lfloat64 f64NUMERICAL_CONVERT__Array(const Luint8 *pu8Array);

	//arrays
	void vNUM_ARRAY__Insert_U8(Luint8 *pu8Array, Luint8 u8ArrayLength, Luint8 u8InsertPosition, Luint8 u8InsertValue);
	
	//binary
	void vNUM_BINARY__ToBitArray_U8(Luint8 u8Value, Luint8 *pu8Array);
	void vNUM_BINARY__ToBitArray_U16(Luint16 u16Value, Luint8 *pu8Array);
	void vNUM_BINARY__ToBitArray_U32(Luint32 u32Value, Luint8 *pu8Array);
	Luint8 u8NUM_BINARY__FromBitArray(Luint8 *pu8Array);
	Luint16 u16NUM_BINARY__FromBitArray(Luint8 *pu8Array);
	Luint32 u32NUM_BINARY__FromBitArray(Luint8 *pu8Array);
	
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U16(Luint8 *pu8Array, Luint16 u16Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U16_LITTLEENDIAN(Luint8 *pu8Array, Luint16 u16Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U16_BIGENDIAN(Luint8 *pu8Array, Luint16 u16Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_S16(Luint8 *pu8Array, Lint16 s16Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U32(Luint8 *pu8Array, Luint32 u32Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U32_BIGENDIAN(Luint8 *pu8Array, Luint32 u32Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_U32_LITTLEENDIAN(Luint8 *pu8Array, Luint32 u32Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_S32(Luint8 *pu8Array, Lint32 s32Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_F32(Luint8 *pu8Array, Lfloat32 f32Value);
	DLL_DECLARATION void vNUMERICAL_CONVERT__Array_F32_LITTLEENDIAN(Luint8 *pu8Array, Lfloat32 f32Value);
	void vNUMERICAL_CONVERT__Array_F64(Luint8 *pu8Array, Lfloat64 f64Value);

	//linear equations
	DLL_DECLARATION Lfloat32 f32NUMERICAL_LINEAR__CalculateM(Lint32 s32Rise, Lint32 s32Run);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_LINEAR__CalculateC(Lfloat32 f32M, Lint32 s32X, Lint32 s32Y);

	//mac
	DLL_DECLARATION Luint8 u8NUMERICAL_MAC__Compare_MAC8(Luint8 *pu8MAC1, Luint8 *pu8MAC2);

	//vectors
	DLL_DECLARATION void vNUMERICAL_VECTOR__CrossProduct(const struct tsNUM_f32Vector_3D *a, const struct tsNUM_f32Vector_3D *b, struct tsNUM_f32Vector_3D *out);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_VECTOR__Dot(const struct tsNUM_f32Vector_3D *a, const struct tsNUM_f32Vector_3D *b);
	DLL_DECLARATION void vNUMERICAL_VECTOR__Normalize(struct tsNUM_f32Vector_3D *a);
	
	//filtering
	DLL_DECLARATION Lint16 s16NUMERICAL_FILTERING__Add_S16(Lint16 s16Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lint16 *ps16Array);
	DLL_DECLARATION Luint16 u16NUMERICAL_FILTERING__Add_U16(Luint16 u16Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Luint16 *pu16Array);
	DLL_DECLARATION Lint32 s32NUMERICAL_FILTERING__Add_S32(Lint32 s32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lint32 *ps32Array);
	Luint32 u32NUMERICAL_FILTERING__Add_U32(Luint32 u32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Luint32 *pu32Array);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_FILTERING__Add_F32(Lfloat32 f32Sample, Luint16 *pu16AverageCounter, Luint16 u16MaxAverageSize, Lfloat32 *pf32Array);
	
	//tolerance checks
	DLL_DECLARATION Luint8 u8NUMERICAL_TOLERANCE__S16(Lint16 s16A, Lint16 s16B, Luint16 u16Tolerance);
	DLL_DECLARATION Luint8 u8NUMERICAL_TOLERANCE__F32(Lfloat32 f32A, Lfloat32 f32B, Lfloat32 f32Tolerance);
	DLL_DECLARATION Luint8 u8NUMERICAL_TOLERANCE__U32(Luint32 u32A, Luint32 u32B, Luint32 u32Tolerance);
	DLL_DECLARATION Luint8 u8NUMERICAL_TOLERANCE__F64(Lfloat64 f64A, Lfloat32 f64B, Lfloat64 f64Tolerance);
	
	//trig
	DLL_DECLARATION void vNUMERICAL__TRIGTABLES__Init(void);
	Lfloat32 f32NUMERICAL_Atan(Lfloat32 f32Radians);
	Lfloat32 f32NUMERICAL_Atan2(Lfloat32 f32A, Lfloat32 f32B);
	Lfloat32 f32NUMERICAL_Cosine(Lfloat32 f32Radians);
	Lfloat64 f64NUMERICAL_Cosine(Lfloat64 f64Radians);
	Lfloat32 f32NUMERICAL_Sine(Lfloat32 f32Radians);
	Lfloat64 f64NUMERICAL_Sine(Lfloat64 f64Radians);
	Lfloat32 f32NUMERICAL_Asine(Lfloat32 f32Radians);
	Lfloat64 f64NUMERICAL__Tan(Lfloat64 f64Radians);
	
	//float
	DLL_DECLARATION Luint8 u8NUMERICAL_FLOAT__IsZero(Lfloat32 f32Test);
	DLL_DECLARATION Luint8 u8NUMERICAL_FLOAT64__IsZero(Lfloat64 f64Test);
	DLL_DECLARATION Luint8 u8NUMERICAL_FLOAT__IsNAN(Lfloat32 f32Value);
	DLL_DECLARATION Lfloat32 f32NUMERICAL_FLOAT__ABS(Lfloat32 f32Value);
	DLL_DECLARATION Lfloat64 f64NUMERICAL_FLOAT64__ABS(Lfloat64 f64Value);
	Lfloat32 f32NUMERICAL_FLOAT__SQRT(Lfloat32 f32Value);
	Lfloat64 f64NUMERICAL_FLOAT__SQRT(Lfloat64 f64Value);
	Lfloat64 f64NUMERICAL_FLOAT__Log(Lfloat64 f64Value);

	//matrix
	void vNUMERICAL_MATRIX__Mult(Luint32 aRows, Luint32 aCols_bRows, Luint32 bCols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
	void vNUMERICAL_MATRIX__Mult_3X3(const Lfloat32 a[3][3], const Lfloat32 b[3][3], Lfloat32 mat[3][3]);
	void vNUMERICAL_MATRIX__Add(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
	void vNUMERICAL_MATRIX__Sub(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], const Lfloat32 matrixA[], const Lfloat32 matrixB[]);
	void vNUMERICAL_MATRIX__Scale(Luint32 rows, Luint32 cols, Lfloat32 matrixC[], Lfloat32 scaler, const Lfloat32 matrixA[]);
	void vNUMERICAL_MATRIX__Transpose_3X3(Lfloat32 matrixC[9], const Lfloat32 matrixA[9]);
	void vNUMERICAL_MATRIX__Inverse_3X3(Lfloat32 matrixC[9], const Lfloat32 matrixA[9]);

	//circle
	Lfloat32 f32NUMERICAL_CIRCLE__Area_Radius(Luint16 u16Radius);
	Lfloat32 f32NUMERICAL_CIRCLE__Area_Diameter(Luint16 u16Diameter);

	//strings
	Luint8 u8NUMERICAL_STRING__ToLower(Luint8 u8Char);
	Luint8 u8NUMERICAL_STRING__ToUpper(Luint8 u8Char);
	Luint16 u16NUMERICAL_STRING__Get_Length(const Luint8 *pString);
	Luint16 u16NUMERICAL_STRING__Get_Length_ExcludeNewline(const Luint8 *pString);
	Lint16 s16NUMERICAL_STRING__Compare(const Luint8 *pS1, const Luint8 *pS2);

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
	#endif

	//safetys
	#ifndef C_LOCALDEF__LCCM118__ENABLE_TRIG
		#error
	#endif
	
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE
#endif
