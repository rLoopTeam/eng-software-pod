#pragma once

//The Z origin should be the bottom of the hover engines.
//The X&Y origin is the average of the X,Y positions of the 4
//hover engines, basically the middle of the vehicle.
//Positive Z is up.

float Laser1Reading, Laser2Reading, Laser3Reading;
float HE1HeightAboveTrack, HE2HeightAboveTrack, HE3HeightAboveTrack, HE4HeightAboveTrack;
float Roll, Pitch;

void RecalcOrientation();
void CalculateGroundPlane(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3);
float PointToPlaneDistance(float x, float y, float z);
void PrintPlane();
