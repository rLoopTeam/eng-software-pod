//Blends the position, accel and veloc from lower layers and gives a
//single point of interface to the flight layer with our primary measurements
//also allows the track profile to dictate what sensors are used for what measurements.


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

void vFCU_FCTL_BLENDER__Init(void)
{
	//todo: init flight conditions
	sFCU.sFlightControl.sBlender.sWorking.s32Accel_mmss = 0;
	sFCU.sFlightControl.sBlender.sWorking.s32Veloc_mms = 0;
	sFCU.sFlightControl.sBlender.sWorking.s32Disp_mm = 0;
}


void vFCU_FCTL_BLENDER__Process(void)
{
	//todo
	//determine from the track database what sensors we need
	//add in any geometry offsets
	//check things like laser range as its not a displacement from the start of the track
	//determine 3 current values, A, V, D

}

//return the current values
Lint32 s32FCU_FCTL_BLENDER__Get_Accel_mmss(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Accel_mmss;
}

Lint32 s32FCU_FCTL_BLENDER__Get_Veloc_mms(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Veloc_mms;
}

Lint32 s32FCU_FCTL_BLENDER__Get_Displacement_mm(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Disp_mm;
}

//update the velocity from the accelometer subystems
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}

//update the velocity from the LRF
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}

//Update the velocity from the contrast sensor system
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}


//update the Acceleration from the accelometer subystems
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}

//update the Acceleration from the LRF
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}

//Update the Acceleration from the contrast sensor system
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}


//update the Displacement from the accelometer subystems
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}

//update the Displacement from the LRF
//Note: LRF may be distance remaining, need to blend properly
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}

//Update the Displacement from the contrast sensor system
//Note this may be track elapsed position
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif


