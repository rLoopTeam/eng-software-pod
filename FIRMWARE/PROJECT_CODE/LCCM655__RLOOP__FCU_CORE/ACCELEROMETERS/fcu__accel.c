/**
 * @file		FCU__ACCEL.C
 * @brief		Accelerometer Subsystem
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__ACCELEROMETER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the accel subsystem layer
 * 
 * @st_funcMD5		228023E6C160A7BB877AE0116DB9D297
 * @st_funcID		LCCM655R0.FILE.010.FUNC.001
 */
void vFCU_ACCEL__Init(void)
{
	Luint32 u32Temp;
	Luint8 u8Counter;
	Luint8 u8Device;

	//accel subsystem
	vSIL3_FAULTTREE__Init(&sFCU.sAccel.sFaultFlags);

	//init the ethernet systems
	vFCU_ACCEL_ETH__Init();

	//init the valid checks
	vFCU_ACCEL_VALID__Init();

	//setup the thresholding
	vFCU_ACCEL_THRESH__Init();

	//init vars
	for(u8Device = 0U; u8Device < C_FCU__NUM_ACCEL_CHIPS; u8Device++)
	{
		for(u8Counter = 0U; u8Counter < MMA8451_AXIS__MAX; u8Counter++)
		{
			sFCU.sAccel.sChannels[u8Device].s16LastSample[u8Counter] = 0;

		}//for(u8Counter = 0U; u8Counter < C_FCU__NUM_ACCEL_CHIPS; u8Counter++)

		//clear the computed varaiables.
		sFCU.sAccel.sChannels[u8Device].u8NewSampleAvail = 0U;
		sFCU.sAccel.sChannels[u8Device].s32CurrentAccel_mm_ss = 0;
		sFCU.sAccel.sChannels[u8Device].s32CurrentVeloc_mm_s = 0;
		sFCU.sAccel.sChannels[u8Device].s32PrevVeloc_mm_s = 0;
		sFCU.sAccel.sChannels[u8Device].s32CurrentDisplacement_mm = 0;
		sFCU.sAccel.sChannels[u8Device].s32PrevDisplacement_mm = 0;

		//clear the filtering.
		sFCU.sAccel.sChannels[u8Device].u16FilterCounter = 0U;
		for(u8Counter = 0U; u8Counter < C_FCU__ACCEL_FILTER_WINDOW; u8Counter++)
		{
			sFCU.sAccel.sChannels[u8Device].s16FilterValues[u8Counter] = 0;
		}
		sFCU.sAccel.sChannels[u8Device].s16FilteredResult = 0;

	}//for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Device++)



#ifndef WIN32

	//get some interrupts going for channel 0
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 6U, GIO_DIRECTION__INPUT);
	vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_6);
	vRM4_GIO__Set_Port_Pullup(RM4_GIO__PORT_A, 6U);

	//enable
	vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_6);
#endif //win32

	//init the MMA devices
	//device 0
	vSIL3_MMA8451__Init(0U);

	//check
	u32Temp = u32SIL3_MMA8451__Get_FaultFlags(0U);
	if(u32Temp != 0x00000000U)
	{
		//we had a fault with sensor 0
		//we have a fault, so propergate the fault to our internal fault flags
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
	}
	else
	{
		//do nothing
	}


	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2
#ifndef WIN32
		//get some interrupts going for channel 1
		vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 7U, GIO_DIRECTION__INPUT);
		vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_7);
		vRM4_GIO__Set_Port_Pullup(RM4_GIO__PORT_A, 7U);

		//enable
		vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_7);
#endif

		//device 1
		vSIL3_MMA8451__Init(1U);

		//check
		u32Temp = u32SIL3_MMA8451__Get_FaultFlags(1U);
		if(u32Temp != 0x00000000U)
		{
			//we had a fault with sensor 1
			//we have a fault, so propergate the fault to our internal fault flags
			vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
			vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
		}
		else
		{
			//do nothing
		}
	#endif


}

/***************************************************************************//**
 * @brief
 * Process the accel's
 * Call as fast as possible from the main loop
 * 
 * @st_funcMD5		0C7EE7686E457B1E4BDF1E8304B97461
 * @st_funcID		LCCM655R0.FILE.010.FUNC.002
 */
void vFCU_ACCEL__Process(void)
{
	Luint32 u32Temp[2];
	Luint8 u8Test;
	Luint8 u8Counter;
	MMA8451__AXIS_E eTargetAxis;
	Lint32 s32Axis_To_ms;
	Lint32 s32Temp;
	Lfloat32 f32Temp;

	//depending on the orientation of the hardware
	eTargetAxis = MMA8451_AXIS__Y;

	//we have an axis in the range of +/- C_LOCALDEF__LCCM418__G_FORCE_RANGE
	#if C_LOCALDEF__LCCM418__G_FORCE_RANGE == 2U
		s32Axis_To_ms = 4096;
	#elif C_LOCALDEF__LCCM418__G_FORCE_RANGE == 4U
		s32Axis_To_ms = 2048;
	#elif C_LOCALDEF__LCCM418__G_FORCE_RANGE == 8U
		s32Axis_To_ms = 1024;
	#else
		#error
	#endif


	//loop through each device
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Counter++)
	{

		//process the device
		vSIL3_MMA8451__Process(u8Counter);

		u32Temp[u8Counter] = u32SIL3_MMA8451__Get_FaultFlags(u8Counter);
		if(u32Temp[u8Counter] != 0x00000000U)
		{
			//we had a fault with sensor 0
			vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
			vSIL3_FAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
		}
		else
		{
			//no faults, good to process
			u8Test = u8SIL3_MMA8451__Get_NewSampleReady(u8Counter);
			if(u8Test == 1U)
			{
				//no faults on sensor 0, safe to process accel data
				sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__X] = s16SIL3_MMA8451_FILTERING__Get_Average(u8Counter, MMA8451_AXIS__X);
				sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Y] = s16SIL3_MMA8451_FILTERING__Get_Average(u8Counter, MMA8451_AXIS__Y);
				sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Z] = s16SIL3_MMA8451_FILTERING__Get_Average(u8Counter, MMA8451_AXIS__Z);

				#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
					sFCU.sAccel.sChannels[u8Counter].f32LastG[MMA8451_AXIS__X] = f32MMA8451_MATH__Get_GForce(u8Counter, MMA8451_AXIS__X);
					sFCU.sAccel.sChannels[u8Counter].f32LastG[MMA8451_AXIS__Y] = f32MMA8451_MATH__Get_GForce(u8Counter, MMA8451_AXIS__Y);
					sFCU.sAccel.sChannels[u8Counter].f32LastG[MMA8451_AXIS__Z] = f32MMA8451_MATH__Get_GForce(u8Counter, MMA8451_AXIS__Z);
				#endif


				//Filter, I will just use a very basic filter here until someone gives me a more advanced one
				sFCU.sAccel.sChannels[u8Counter].s16FilteredResult = s16SIL3_NUM_FILTERING__Add_S16(sFCU.sAccel.sChannels[u8Counter].s16LastSample[(Luint8)eTargetAxis],
																									&sFCU.sAccel.sChannels[u8Counter].u16FilterCounter,
																									C_FCU__ACCEL_FILTER_WINDOW,
																									&sFCU.sAccel.sChannels[u8Counter].s16FilterValues[0]);

				//Get the current filtered value in accel units
				f32Temp = (Lfloat32)sFCU.sAccel.sChannels[u8Counter].s16FilteredResult;

				//convert this raw value into G-Force
				f32Temp /= (Lfloat32)s32Axis_To_ms;

				//todo
				//pitch angle offset in data.

				//convert g-force into meters / sec^2
				f32Temp *= 9.80665F;

				//convert m/s into mm/sec
				f32Temp *= 1000.0F;

				//assign
				sFCU.sAccel.sChannels[u8Counter].s32CurrentAccel_mm_ss = (Lint32)f32Temp;

				//at this point here we have raw acceleration units updating every 1/freq

				//convert to mm/100th's (or what-ever the data rate is)
				//This is the same as a*t where T = 1/Freq
				//Assume this value is 100HZ
				f32Temp /= (Lfloat32)C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ;

				//v = u + at
				//where u = prev sample and t = time slice
				f32Temp += (Lfloat32)sFCU.sAccel.sChannels[u8Counter].s32PrevVeloc_mm_s;

				//assign
				sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s = (Lint32)f32Temp;

				//assing prev (u)
				sFCU.sAccel.sChannels[u8Counter].s32PrevVeloc_mm_s = sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s;

				//compute poition
				//pos = posPrev + T * veloc
				sFCU.sAccel.sChannels[u8Counter].s32CurrentDisplacement_mm = sFCU.sAccel.sChannels[u8Counter].s32PrevDisplacement_mm + sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s;

				//update the previous
				sFCU.sAccel.sChannels[u8Counter].s32PrevDisplacement_mm = sFCU.sAccel.sChannels[u8Counter].s32CurrentDisplacement_mm;

				//handle the Daq
				#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_ACCELS == 1U
				switch(u8Counter)
				{
					case 0:
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0X_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__X]);
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Y_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Y]);
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Z_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Z]);

						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_ACCEL_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentAccel_mm_ss);
						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_VELOC_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s);
						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_DISP_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentDisplacement_mm);
						break;

					case 1:
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1X_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__X]);
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1Y_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Y]);
						vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1Z_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Z]);

						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_ACCEL_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentAccel_mm_ss);
						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_VELOC_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s);
						vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_DISP_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentDisplacement_mm);
						break;

					default:
						//fall on
						break;
				}
				#endif

				//done with the sample now
				vSIL3_MMA8451__Clear_NewSampleReady(u8Counter);

				sFCU.sAccel.sChannels[u8Counter].u8NewSampleAvail = 1U;

			}
			else
			{
				//no new sample avail yet
			}
		}

	}//for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM418__NUM_DEVICES; u8Counter++)


	//finally process the valid checks.
	vFCU_ACCEL_VALID__Process();

	//process the thresholding detection
	vFCU_ACCEL_THRESH__Process();

}

Luint8 u8FCU_ACCEL__Get_New_Sample_Avail(Luint8 u8Channel)
{
	return sFCU.sAccel.sChannels[u8Channel].u8NewSampleAvail;
}

void vFCU_ACCEL__Clear_New_Sample_Avail(Luint8 u8Channel)
{
	if(u8Channel < C_FCU__NUM_ACCEL_CHIPS)
	{
		sFCU.sAccel.sChannels[u8Channel].u8NewSampleAvail = 0U;
	}
	else
	{
		//error
	}
}


/***************************************************************************//**
 * @brief
 * Return the current velocity as most recently computed in mm/sec
 * 
 * @param[in]		u8Channel				Accel Channel
 * @st_funcMD5		7CC447262C7735B3DB7A39CB6E245D56
 * @st_funcID		LCCM655R0.FILE.010.FUNC.005
 */
Lint32 s32FCU_ACCELL__Get_CurrentAccel_mmss(Luint8 u8Channel)
{
	return sFCU.sAccel.sChannels[u8Channel].s32CurrentAccel_mm_ss;
}


/***************************************************************************//**
 * @brief
 * Return the current velocity as most recently computed in mm/sec
 * 
 * @param[in]		u8Channel				Accel Channel
 * @st_funcMD5		CC098E0A4FB3D5872E08D26CA11396CA
 * @st_funcID		LCCM655R0.FILE.010.FUNC.006
 */
Lint32 s32FCU_ACCELL__Get_CurrentVeloc_mms(Luint8 u8Channel)
{
	return sFCU.sAccel.sChannels[u8Channel].s32CurrentVeloc_mm_s;
}

/***************************************************************************//**
 * @brief
 * Return the current displacement
 * 
 * @param[in]		u8Channel				Accel channel
 * @st_funcMD5		5B659BF07323FD3334B5C7C0E93D8AAD
 * @st_funcID		LCCM655R0.FILE.010.FUNC.007
 */
Lint32 s32FCU_ACCELL__Get_CurrentDisplacement_mm(Luint8 u8Channel)
{
	return sFCU.sAccel.sChannels[u8Channel].s32CurrentDisplacement_mm;
}

/***************************************************************************//**
 * @brief
 * Get the last recorded sample from the Accels
 *
 * @note
 * If the accels fault out, this value wont update.
 * 
 * @param[in]		u8Axis					The axis index
 * @param[in]		u8Index					The accel device index
 * @return			The S16 last accel value
 * @st_funcMD5		8BA7DA408E22C09AEF1CAEFD11E12ACF
 * @st_funcID		LCCM655R0.FILE.010.FUNC.003
 */
Lint16 s16FCU_ACCEL__Get_LastSample(Luint8 u8Index, Luint8 u8Axis)
{
	return sFCU.sAccel.sChannels[u8Index].s16LastSample[u8Axis];
}


/***************************************************************************//**
 * @brief
 * Get the last G-Force calculated value
 * 
 * @param[in]		u8Axis					The axis index
 * @param[in]		u8Index					The accel device index
 * @return			The F32 last computed G-Force from each sensor
 * @st_funcMD5		D4DC470315C624685712D0F05788CC8C
 * @st_funcID		LCCM655R0.FILE.010.FUNC.004
 */
Lfloat32 f32FCU_ACCEL__Get_LastG(Luint8 u8Index, Luint8 u8Axis)
{
	#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
		return sFCU.sAccel.sChannels[u8Index].f32LastG[u8Axis];
	#else
		return 0.0F;
	#endif
}


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		448A3FE6733707EEBF70C29A5E02E632
 * @st_funcID		LCCM655R0.FILE.010.FUNC.008
 */
void vFCU_ACCEL__10MS_ISR(void)
{
	//pass off to thrreshold detection system.
	vFCU_ACCEL_THRESH__10MS_ISR();
}

//make sure both sensors are in the same range
#if C_LOCALDEF__LCCM418__DEV0__DATA_RATE_HZ != C_LOCALDEF__LCCM418__DEV1__DATA_RATE_HZ
	#error
#endif

#ifndef C_FCU_DAQ_SET__ENABLE__DAQ_FOR_ACCELS
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

