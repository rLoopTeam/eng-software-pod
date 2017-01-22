/**
 * @file		numerical__structs.h
 * @brief		Numerical structure types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM118R0.FILE.004
 */


#ifndef NUMERICAL__STRUCTS_H_
#define NUMERICAL__STRUCTS_H_

	/*******************************************************************************
	Structures
	*******************************************************************************/

	/** Spherical coordinates (r, theta, phi) as often used in mathematics:
	 * radial distance r, azimuthal angle theta, and polar angle phi.
	 * The meanings of theta and phi have been swapped compared to the physics convention.
	 * https://en.wikipedia.org/wiki/Spherical_coordinate_system
	 * */
	typedef struct tsNUM_SphericalCoord
	{
		/** The length R is the distance along the point (0,0,0) to (r,theta,phi) */
		Lfloat32 f32R;

		/** Azimuth angle theta is the angle between the X,Y coordinate.*/
		Lfloat32 f32Azimuth;

		/** The polar angle is the angle from the Z axis */
		Lfloat32 f32Polar;

	}NUMERICAL__SPHERICAL_COORD_T;


	typedef struct tsNUM_u16Point_2D
	{
		Luint16 u16X;
		Luint16 u16Y;

	}sNUM_u16Point_2D;

	typedef struct tsNUM_s16Point_2D
	{
		Lint16 s16X;
		Lint16 s16Y;
	}sNUM_s16Point_2D;


	typedef struct tsNUM_s16Rect_2D
	{
		Lint16 s16X1;
		Lint16 s16Y1;
		Lint16 s16X2;
		Lint16 s16Y2;
	}sNUM_s16Rect_2D;


	typedef struct tsNUM_f32Point_2D
	{
		Lfloat32 f32X;
		Lfloat32 f32Y;

	}sNUM_f32Point_2D;



	typedef struct tsNUM_Edge_2D
	{
		sNUM_u16Point_2D start;
		sNUM_u16Point_2D end;
		Lint32 s32Slope;
		Lfloat32 f32Slope;
	}sNUM_Edge_2D;


	//3D Vector
	typedef struct tsNUM_f32Vector_3D
	{

		Lfloat32 f32X;
		Lfloat32 f32Y;
		Lfloat32 f32Z;
		
	}sNUM_f32Vector_3D;


	typedef struct tsNUM_s32Vector_3D
	{

		Lint32 s32X;
		Lint32 s32Y;
		Lint32 s32Z;

	}sNUM_s32Vector_3D;

	//3D Vector
	typedef struct tsNUM_f64Vector_3D
	{

		Lfloat64 f64X;
		Lfloat64 f64Y;
		Lfloat64 f64Z;
		
	}sNUM_f64Vector_3D;

#endif /* NUMERICAL__STRUCTS_H_ */
