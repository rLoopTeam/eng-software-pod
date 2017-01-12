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
 * @st_funcMD5		809972C08E10832306B77DABFAEAA1D2
 * @st_funcID		LCCM655R0.FILE.010.FUNC.001
 */
void vFCU_ACCEL__Init(void)
{
	Luint32 u32Temp;
	Luint8 u8Counter;

	//accel subsystem
	vFAULTTREE__Init(&sFCU.sAccel.sFaultFlags);

	vFCU_ACCEL_ETH__Init();

	//init vars
	for(u8Counter = 0U; u8Counter < 3U; u8Counter++)
	{
		sFCU.sAccel.sChannels[0].s16LastSample[u8Counter] = 0;
		sFCU.sAccel.sChannels[1].s16LastSample[u8Counter] = 0;
	}

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
	vMMA8451__Init(0U);

	//check
	u32Temp = u32MMA8451__Get_FaultFlags(0U);
	if(u32Temp != 0x00000000U)
	{
		//we had a fault with sensor 0
		//we have a fault, so propergate the fault to our internal fault flags
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
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
		vMMA8451__Init(1U);

		//check
		u32Temp = u32MMA8451__Get_FaultFlags(1U);
		if(u32Temp != 0x00000000U)
		{
			//we had a fault with sensor 1
			//we have a fault, so propergate the fault to our internal fault flags
			vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
			vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
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
 * @st_funcMD5		CC85D859A7DAFE2A9EC3DBE59C6E5665
 * @st_funcID		LCCM655R0.FILE.010.FUNC.002
 */
void vFCU_ACCEL__Process(void)
{
	Luint32 u32Temp0;
	Luint32 u32Temp1;

	//process device 0
	vMMA8451__Process(0U);

	//after processing check for any fault flags
	u32Temp0 = u32MMA8451__Get_FaultFlags(0U);
	if(u32Temp0 != 0x00000000U)
	{
		//we had a fault with sensor 0
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
	}
	else
	{
		//do nothing
	}

	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2U
	//do sensor 1
	vMMA8451__Process(1U);

	//after processing check for any fault flags
	u32Temp1 = u32MMA8451__Get_FaultFlags(0U);
	if(u32Temp1 != 0x00000000U)
	{
		//we had a fault with sensor 0
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sAccel.sFaultFlags, C_LCCM655__ACCEL__FAULT_INDEX__01);
	}
	else
	{
		//do nothing
	}
	#endif

	if(u32Temp0 == 0U)
	{
		//no faults on sensor 0, safe to process accel data
		sFCU.sAccel.sChannels[0].s16LastSample[0] = s16MMA8451_FILTERING__Get_Average(0U, AXIS_X);
		sFCU.sAccel.sChannels[0].s16LastSample[1] = s16MMA8451_FILTERING__Get_Average(0U, AXIS_Y);
		sFCU.sAccel.sChannels[0].s16LastSample[2] = s16MMA8451_FILTERING__Get_Average(0U, AXIS_Z);

		sFCU.sAccel.sChannels[0].f32LastG[0] = f32MMA8451_MATH__Get_GForce(0U, AXIS_X);
		sFCU.sAccel.sChannels[0].f32LastG[1] = f32MMA8451_MATH__Get_GForce(0U, AXIS_Y);
		sFCU.sAccel.sChannels[0].f32LastG[2] = f32MMA8451_MATH__Get_GForce(0U, AXIS_Z);


	}
	else
	{
		//lost accel data on this sensor
	}

	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2U
	if(u32Temp1 == 0U)
	{
		//no faults on sensor 1, safe to process accel data
		sFCU.sAccel.sChannels[1].s16LastSample[0] = s16MMA8451_FILTERING__Get_Average(1U, AXIS_X);
		sFCU.sAccel.sChannels[1].s16LastSample[1] = s16MMA8451_FILTERING__Get_Average(1U, AXIS_Y);
		sFCU.sAccel.sChannels[1].s16LastSample[2] = s16MMA8451_FILTERING__Get_Average(1U, AXIS_Z);


		sFCU.sAccel.sChannels[1].f32LastG[0] = f32MMA8451_MATH__Get_GForce(1U, AXIS_X);
		sFCU.sAccel.sChannels[1].f32LastG[1] = f32MMA8451_MATH__Get_GForce(1U, AXIS_Y);
		sFCU.sAccel.sChannels[1].f32LastG[2] = f32MMA8451_MATH__Get_GForce(1U, AXIS_Z);

	}
	else
	{
		//lost accel data on this sensor
	}
	#endif

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
 * @st_funcMD5		A1292B6EC9CD5190837BCF3CF23D23F6
 * @st_funcID		LCCM655R0.FILE.010.FUNC.004
 */
Lfloat32 f32FCU_ACCEL__Get_LastG(Luint8 u8Index, Luint8 u8Axis)
{
	return sFCU.sAccel.sChannels[u8Index].f32LastG[u8Axis];
}

#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

