#include "LaserOrientation.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

//All units in mm
//The math doesn't care as long as you're consistent

//For the laser positions Z should be the reading when
//the HDK is sitting flat on the 4 hover engines

//Laser Position Near Engine 1
float Laser1X = -100, Laser1Y = 100, Laser1Z = 75;

//Laser Position Near Engine 4
float Laser2X = -100, Laser2Y = -100, Laser2Z = 75;

//Laser Position Near Engine 3
float Laser3X = 100, Laser3Y = -100, Laser3Z = 75;

//Hover Engine Top Left from above
float HE1X = -150, HE1Y=150, HE1Z=0;

//Hover Engine Top Right from above
float HE2X=150, HE2Y=150, HE2Z=0;

//Hover Engine Bottom Right from above
float HE3X=150, HE3Y=-150, HE3Z=0;

//Hover Engine Bottom Left from above
float HE4X=-150, HE4Y=-150, HE4Z=0;

//Basically the vehicle is a static reference
//and we recalculate the orientation of the
//ground plane relative to the vehicle
//and the hover engines
float PlaneA, PlaneB, PlaneC, PlaneD;

void RecalcRoll();
void RecalcPitch();

float PointToPlaneDistance(float x, float y, float z)
{
	return (PlaneA * x + PlaneB * y + PlaneC*z + PlaneD) / sqrt((double)(PlaneA*PlaneA + PlaneB*PlaneB + PlaneC*PlaneC));
}

//After the laser readings are updated this function
//will recalculate the orientation and engine heights
void RecalcOrientation()
{
	CalculateGroundPlane(Laser1X, Laser1Y, Laser1Z - Laser1Reading, Laser2X, Laser2Y, Laser2Z - Laser2Reading, Laser3X, Laser3Y, Laser3Z - Laser3Reading);
	HE1HeightAboveTrack = PointToPlaneDistance(HE1X, HE1Y, HE1Z);
	HE2HeightAboveTrack = PointToPlaneDistance(HE2X, HE2Y, HE2Z);
	HE3HeightAboveTrack = PointToPlaneDistance(HE3X, HE3Y, HE3Z);
	HE4HeightAboveTrack = PointToPlaneDistance(HE4X, HE4Y, HE4Z);
	RecalcPitch();
	RecalcRoll();
}

//The angle between two planes that yields the roll
void RecalcRoll()
{
	//Normal vector of the other plane
	float vec1x = 1, vec1y = 0, vec1z = 0;

	//Angle between two planes
	Roll = acos((double)((vec1x*PlaneA + vec1y*PlaneB + vec1z * PlaneC) / sqrt((double)(PlaneA*PlaneA + PlaneB*PlaneB + PlaneC*PlaneC))))*180/PI;
}

//The angle between two planes that yields the pitch
void RecalcPitch()
{
	//Normal vector of the other plane
	float vec1x = 0, vec1y = 1, vec1z = 0;

	//Angle between two planes
	Pitch = acos((double)((vec1x*PlaneA + vec1y*PlaneB + vec1z * PlaneC) / sqrt((double)(PlaneA*PlaneA + PlaneB*PlaneB + PlaneC*PlaneC)))) * 180 / PI;
}

void PrintPlane()
{
	printf("A:%f B:%f C:%f D:%f\n", PlaneA, PlaneB, PlaneC, PlaneD);
}

//Calculate the ground plane given three points
//Ax + By + Cz + D = 0
void CalculateGroundPlane(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3)
{
	float Vec1X, Vec1Y, Vec1Z;
	float Vec2X, Vec2Y, Vec2Z;
	float XProductX, XProductY, XProductZ;
	float d;

	//Calculate two vectors in the plane
	Vec1X = X1 - X2;
	Vec1Y = Y1 - Y2;
	Vec1Z = Z1 - Z2;
	Vec2X = X2 - X3;
	Vec2Y = Y2 - Y3;
	Vec2Z = Z2 - Z3;

	//Calculate the cross product of the vectors
	//to get a vector normal to the plane
	XProductX = Vec1Y*Vec2Z - Vec1Z*Vec2Y;
	XProductY = Vec1Z*Vec2X - Vec1X*Vec2Z;
	XProductZ = Vec1X*Vec2Y - Vec1Y*Vec2X;

	//The normal vector should be pointed in the +Z direction
	//It affects which side of the plane has negative distances
	if (XProductZ < 0){
		XProductX *= -1;
		XProductY *= -1; 
		XProductZ *= -1;
	}

	//Plane in 3D: Ax + By + Cz + D = 0
	//A, B, C is the vector normal to the plane
	//Use one of our original points to calculate D
	d = -1 * (XProductX*X1 + XProductY*Y1 + XProductZ*Z1);

	PlaneA = XProductX;
	PlaneB = XProductY;
	PlaneC = XProductZ;
	PlaneD = d;
}