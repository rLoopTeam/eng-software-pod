#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U

//the structure
extern struct _strFCU sFCU;


//init the thresholding detection system
void vFCU_ACCEL_THRESH__Init(void)
{
	sFCU.sAccel.sAccelThresh.u8ThresholdTrue = 0U;
	sFCU.sAccel.sAccelThresh.u16ThreshTime_x10ms = 0U;
	sFCU.sAccel.sAccelThresh.s32Thresh_Accel_mm_ss = 0;
	sFCU.sAccel.sAccelThresh.u3210MS_Counter = 0U;

	sFCU.sAccel.sDecelThresh.u8ThresholdTrue = 0U;
	sFCU.sAccel.sDecelThresh.u16ThreshTime_x10ms = 0U;
	sFCU.sAccel.sDecelThresh.s32Thresh_Accel_mm_ss = 0;
	sFCU.sAccel.sDecelThresh.u3210MS_Counter = 0U;
}

//process the thresholds
void vFCU_ACCEL_THRESH__Process(void)
{
	Luint8 u8AccelTrue;
	Luint8 u8DecelTrue;
	Luint8 u8Test;
	Lint32 s32Test;

	//make sure we have valid data
	u8Test = u8FCU_ACCEL_VALID__Get_IsValid();
	if(u8Test == 1U)
	{
		//we have valid accel data
		s32Test = sFCU_ACCEL_VALID__Get_Accel_mm_ss();

		//WARNING: ONLY POSITIVE ACCEL POSSIBLE HERE  @todo: negative now implemented as 'decel'

		//check if we are over the accel threshold
		if(s32Test > sFCU.sAccel.sAccelThresh.s32Thresh_Accel_mm_ss)
		{
			//we are over our threshold, keep the timer going

			//check the timer
			if(sFCU.sAccel.sAccelThresh.u3210MS_Counter > sFCU.sAccel.sAccelThresh.u16ThreshTime_x10ms)
			{
				//ok so we are over our valid range for the time period, we are valid
				u8AccelTrue = 1U;
			}
			else
			{
				//we have not reached the time yet, but we have excced the threshold, keep
				//the timer going
				u8AccelTrue = 0U;
			}
		}
		else
		{
			//not quite at the threshold yet, clear the timer.
			sFCU.sAccel.sAccelThresh.u3210MS_Counter = 0U;
			u8AccelTrue = 0U;
		}

		//check if we are under the decel threshold
		if (s32Test < sFCU.sAccel.sDecelThresh.s32Thresh_Accel_mm_ss)
		{
			//we are under our threshold, keep the timer going

			//check the timer
			if (sFCU.sAccel.sDecelThresh.u3210MS_Counter > sFCU.sAccel.sDecelThresh.u16ThreshTime_x10ms)
			{
				//ok so we are over our valid range for the time period, we are valid
				u8DecelTrue = 1U;
			}
			else
			{
				//we have not reached the time yet, but we have excced the threshold, keep
				//the timer going
				u8DecelTrue = 0U;
			}
		}
		else
		{
			//not quite at the threshold yet, clear the timer.
			sFCU.sAccel.sDecelThresh.u3210MS_Counter = 0U;
			u8DecelTrue = 0U;
		}


	}
	else
	{
		//accel subsystem not valid
		u8AccelTrue = 0U;
		u8DecelTrue = 0U;
	}

	//finally set the thresholds
	sFCU.sAccel.sAccelThresh.u8ThresholdTrue = u8AccelTrue;
	sFCU.sAccel.sDecelThresh.u8ThresholdTrue = u8DecelTrue;

}

//Returns 1 when the accel threshold conditions have been ment
Luint8 u8FCU_ACCEL_THRES__Is_Accel_Threshold_Met(void)
{
	return sFCU.sAccel.sAccelThresh.u8ThresholdTrue;
}

//allows our upper layer to set the accel thresholding time and mm ss accel value
void vFCU_ACCEL_THRESH__Set_Accel_Threshold(Lint32 s32Accel_mm_ss, Luint16 u16Time_x10ms)
{
	//set the user params
	sFCU.sAccel.sAccelThresh.u16ThreshTime_x10ms = u16Time_x10ms;
	sFCU.sAccel.sAccelThresh.s32Thresh_Accel_mm_ss = s32Accel_mm_ss;
}


//Returns 1 when the decel threshold conditions have been ment
Luint8 u8FCU_ACCEL_THRES__Is_Decel_Threshold_Met(void)
{
	return sFCU.sAccel.sDecelThresh.u8ThresholdTrue;
}

//allows our upper layer to set the decel thresholding time and mm ss accel value
void vFCU_ACCEL_THRESH__Set_Decel_Threshold(Lint32 s32Accel_mm_ss, Luint16 u16Time_x10ms)
{
	//set the user params
	sFCU.sAccel.sDecelThresh.u16ThreshTime_x10ms = u32Time_x10ms;
	sFCU.sAccel.sDecelThresh.s32Thresh_Accel_mm_ss = s32Accel_mm_ss;
}


//10ms isr used for thresh detection.
void vFCU_ACCEL_THRESH__10MS_ISR(void)
{
	//inc the interrupt counter;
	sFCU.sAccel.sAccelThresh.u3210MS_Counter += 1U;
	sFCU.sAccel.sDecelThresh.u3210MS_Counter += 1U;
}

#endif //
#endif //
