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

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_ACCEL__Init(void)
{
	Luint32 u32Temp;

	//init vars
	sFCU.sAccel.sChannels[0].s16LastSample = 0;
	sFCU.sAccel.sChannels[1].s16LastSample = 0;

	//get some interrupts going for channel 0
	vRM4_GIO__Set_BitDirection(gioPORTA, 6U, GIO_DIRECTION__INPUT);
	vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_6);
	vRM4_GIO__Set_Port_Pullup(gioPORTA, 6U);

	//enable
	vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_6);


	//init the MMA devices
	//device 0
	vMMA8451__Init(0U);

	//check
	u32Temp = u32MMA8451__Get_FaultFlags(0U);
	if(u32Temp != 0x00000000U)
	{
		//we had a fault with sensor 0
		//we have a fault, so propergate the fault to our internal fault flags
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__01);
	}
	else
	{
		//do nothing
	}


	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2
		//get some interrupts going for channel 1
		vRM4_GIO__Set_BitDirection(gioPORTA, 7U, GIO_DIRECTION__INPUT);
		vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_7);
		vRM4_GIO__Set_Port_Pullup(gioPORTA, 7U);

		//enable
		vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_7);


		//device 1
		vMMA8451__Init(1U);

		//check
		u32Temp = u32MMA8451__Get_FaultFlags(1U);
		if(u32Temp != 0x00000000U)
		{
			//we had a fault with sensor 1
			//we have a fault, so propergate the fault to our internal fault flags
			vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__00);
			vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__01);
		}
		else
		{
			//do nothing
		}
	#endif


}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 */
void vFCU_ACCEL__Process(void)
{
	Luint32 u32Temp0;
	Luint32 u32Temp1;

	//process device 0
	vMMA8451__Process(0);

	//after processing check for any fault flags
	u32Temp0 = u32MMA8451__Get_FaultFlags(0U);
	if(u32Temp0 != 0x00000000U)
	{
		//we had a fault with sensor 0
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__01);
	}
	else
	{
		//do nothing
	}

	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2
		//do sensor 1
		vMMA8451__Process(1U);

		//after processing check for any fault flags
		u32Temp1 = u32MMA8451__Get_FaultFlags(0U);
		if(u32Temp1 != 0x00000000U)
		{
			//we had a fault with sensor 0
			vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__00);
			vFAULTTREE__Set_Flag(&sFCU.sFaults.sAccel, C_LCCM655__ACCEL__FAULT_INDEX__01);
		}
		else
		{
			//do nothing
		}

	#endif

	if(u32Temp0 == 0U)
	{
		//no faults on sensor 0, safe to process accel data
		sFCU.sAccel.sChannels[0].s16LastSample = s16MMA8451_FILTERING__Get_Average(0U, AXIS_X);

	}
	else
	{
		//lost accel data on this sensor
	}

	#if C_LOCALDEF__LCCM418__NUM_DEVICES >= 2
		if(u32Temp1 == 0U)
		{
			//no faults on sensor 1, safe to process accel data
			sFCU.sAccel.sChannels[1].s16LastSample = s16MMA8451_FILTERING__Get_Average(1U, AXIS_X);
		}
		else
		{
			//lost accel data on this sensor
		}
	#endif

}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

