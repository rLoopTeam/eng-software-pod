#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U

//the structure
extern struct _strFCU sFCU;


//init the thresholding detection system
void vFCU_ACCEL_THRESH__Init(void)
{
	sFCU.sAccel.sThresh.u8ThresholdTrue = 0U;
	sFCU.sAccel.sThresh.u32ThreshTime_x10ms = 0U;
	sFCU.sAccel.sThresh.s32Thresh_Accel_mm_ss = 0;
	sFCU.sAccel.sThresh.u3210MS_Counter = 0U;
}

//process the thresholds
void vFCU_ACCEL_THRESH__Process(void)
{
	Luint8 u8True;
	Luint8 u8Test;
	Lint32 s32Test;

	//make sure we have valid data
	u8Test = u8FCU_ACCEL_VALID__Get_IsValid();
	if(u8Test == 1U)
	{
		//we have valid accel data
		s32Test = sFCU_ACCEL_VALID__Get_Accel_mm_ss();

		//WARNING: ONLY POSITIVE ACCEL POSSIBLE HERE

		//check if we are over the threshold
		if(s32Test > sFCU.sAccel.sThresh.s32Thresh_Accel_mm_ss)
		{
			//we are over our threshold, keep the timer going

			//check the timer
			if(sFCU.sAccel.sThresh.u3210MS_Counter > sFCU.sAccel.sThresh.u32ThreshTime_x10ms)
			{
				//ok so we are over our valid range for the time period, we are valid
				u8True = 1U;
			}
			else
			{
				//we have not reached the time yet, but we have excced the threshold, keep
				//the timer going
				u8True = 0U;
			}
		}
		else
		{
			//not quite at the threshold yet, clear the timer.
			sFCU.sAccel.sThresh.u3210MS_Counter = 0U;
			u8True = 0U;
		}

	}
	else
	{
		//accel subsystem not valid
		u8True = 0U;
	}

	//finally set the threshold
	sFCU.sAccel.sThresh.u8ThresholdTrue = u8True;

}

//Returns 1 when the threshold conditions have been ment
Luint8 u8FCU_ACCEL_THRES__Is_Threshold_Met(void)
{
	return sFCU.sAccel.sThresh.u8ThresholdTrue;
}

//allows our upper layer to set the thresholding time and mm ss accel value
void vFCU_ACCEL_THRESH__Set_Threshold(Luint32 u32Time_x10ms, Lint32 s32Accel_mm_ss)
{
	//set the user params
	sFCU.sAccel.sThresh.u32ThreshTime_x10ms = u32Time_x10ms;
	sFCU.sAccel.sThresh.s32Thresh_Accel_mm_ss = s32Accel_mm_ss;
}


//10ms isr used for thresh detection.
void vFCU_ACCEL_THRESH__10MS_ISR(void)
{
	//inc the interrupt counter;
	sFCU.sAccel.sThresh.u3210MS_Counter += 1U;
}

#endif //
#endif //
