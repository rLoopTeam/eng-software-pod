/**
 * @file		AUXPROP__THROTTLE.C
 * @brief		Throttle and direction control
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.006
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP__THROTTLE
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_APU__MAIN sAPU;

/***************************************************************************//**
 * @brief
 * Init the throttles
 * 
 * @st_funcMD5		95B216A7663D18DBE6E204A91AFC15E8
 * @st_funcID		LCCM720R0.FILE.006.FUNC.001
 */
void vAPU_THROTTLE__Init(void)
{
	
	sAPU.sThrottle.eDirection = THROTTLE_DIR__FORWARD;
	sAPU.sThrottle.u32Frequency = 0U;

#ifndef WIN32

	//direction is on A0
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 0U, GIO_DIRECTION__OUTPUT);

	//Enable is on A1
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 1U, GIO_DIRECTION__OUTPUT);

	//PWM is on HET1:2
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 2U);

	//vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, 1U);
	//vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, 0U);

	//switch off N2HET before adding program
	vRM4_N2HET__Disable(N2HET_CHANNEL__1);

	//clear any old programs from the RAM
	vN2HET_PROG_DYNAMIC__Clear(N2HET_CHANNEL__1, 0xABCD1234);

	//add the N2HET program
	sAPU.sThrottle.u16N2HET_Index = u16N2HET_PROG_DYNAMIC__Add_PWM(N2HET_CHANNEL__1, 2U, 0U);

	//re-enable
	vRM4_N2HET__Enable(N2HET_CHANNEL__1);

	//set speed 0
	vAPU_THROTTLE__Set_Velocity_mms(0U);

	//all motors forward
	vAPU_THROTTLE__Forward();

	//all motors disabled
	vAPU_THROTTLE__Disable();

#endif

}

/***************************************************************************//**
 * @brief
 * Process any throttle tasks
 * 
 * @st_funcMD5		CC3ECF35746BBD3ECC3130220E396FAB
 * @st_funcID		LCCM720R0.FILE.006.FUNC.002
 */
void vAPU_THROTTLE__Process(void)
{
	
	//do nothing.
}



/***************************************************************************//**
 * @brief
 * Sets the velocity
 * 
 * @param[in]		u32Veloc_mms		Veloc in mm/sec
 * @st_funcMD5		DBF39EC993F3F976F8FE7DA3FCD67825
 * @st_funcID		LCCM720R0.FILE.006.FUNC.007
 */
void vAPU_THROTTLE__Set_Velocity_mms(Luint32 u32Veloc_mms)
{
	Lfloat32 f32Period_uS;
	Lfloat32 f32Freq;

	//convert the mm/s to a PWM with range
	//period is in uS, so 25us = 40KHZ.

	//lets assume we have 1khz = 0.2*1000mm/s
	f32Freq = (Lfloat32)u32Veloc_mms*0.2F;

	sAPU.sThrottle.u32Frequency = (Luint32)f32Freq;

	//convert to time
	f32Period_uS = 1.0F / f32Freq;

	//convert to us
	f32Period_uS *= 100000.0F;

#ifndef WIN32
	//Set frequency
	vRM4_N2HET_PWM__Dyanmic_SetPeriod(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index, f32Period_uS);

	//50% duty cycle
	vRM4_N2HET_PWM__Dyanmic_SetDutyCycle(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index, 0.5F);

	//start the PWM
	vRM4_N2HET_PWM__Dyanmic_Start(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index);

#endif

}


/***************************************************************************//**
 * @brief
 * Set direction forward
 * 
 * @st_funcMD5		A94C4E22E13B755B2FBD72B17913DB8F
 * @st_funcID		LCCM720R0.FILE.006.FUNC.003
 */
void vAPU_THROTTLE__Forward(void)
{
#ifndef WIN32
	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 1U);
#endif

	//set the state
	sAPU.sThrottle.eDirection = THROTTLE_DIR__FORWARD;

#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}

/***************************************************************************//**
 * @brief
 * Set direction in reverse
 * 
 * @st_funcMD5		C3CCD4DB59AE6CF746A901B85FA4DC63
 * @st_funcID		LCCM720R0.FILE.006.FUNC.004
 */
void vAPU_THROTTLE__Reverse(void)
{
#ifndef WIN32
	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);
#endif
	//set the state
	sAPU.sThrottle.eDirection = THROTTLE_DIR__REVERSE;

#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}


/***************************************************************************//**
 * @brief
 * Enable the motor
 * 
 * @st_funcMD5		9F19C707642E67D5DF1D7736BDF1DFDE
 * @st_funcID		LCCM720R0.FILE.006.FUNC.005
 */
void vAPU_THROTTLE__Enable(void)
{
#ifndef WIN32
	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 1U);
#endif
	//set the state
	sAPU.sThrottle.eEnable = THROTTLE_ENA__ENABLED;

#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}


/***************************************************************************//**
 * @brief
 * Disable the motor
 * 
 * @st_funcMD5		DA3A68EBFEBAAF31186C99D255BC42B4
 * @st_funcID		LCCM720R0.FILE.006.FUNC.006
 */
void vAPU_THROTTLE__Disable(void)
{
#ifndef WIN32
	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 0U);
#endif
	//set the state
	sAPU.sThrottle.eEnable = THROTTLE_ENA__DISABLED;

#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}


#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

