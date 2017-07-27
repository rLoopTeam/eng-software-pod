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
 * @st_funcMD5		87A73A82BFE6B5B9A8E3E6E5B37651B5
 * @st_funcID		LCCM720R0.FILE.006.FUNC.001
 */
void vAPU_THROTTLE__Init(void)
{
	
	sAPU.sThrottle.eDirection = THROTTLE_DIR__FORWARD;

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

	//set speed low
	vAPU_THROTTLE__Set_Velocity_mms(500U);

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
 * @st_funcMD5		BF7F67473C5A06EBB874D952714D35E2
 * @st_funcID		LCCM720R0.FILE.006.FUNC.007
 */
void vAPU_THROTTLE__Set_Velocity_mms(Luint32 u32Veloc_mms)
{
	Lfloat32 f32Period_uS;
	Lfloat32 f32Freq;

	//convert the mm/s to a PWM with range
	//period is in uS, so 25us = 40KHZ.

	//lets assume we have 1khz = 1000m/s
	f32Freq = (Lfloat32)u32Veloc_mms;

	//convert to time
	f32Period_uS = 1.0F / f32Freq;

	//convert to us
	f32Period_uS *= 100000.0F;

	vRM4_N2HET_PWM__Dyanmic_SetPeriod(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index, f32Period_uS);
	vRM4_N2HET_PWM__Dyanmic_SetDutyCycle(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index, 0.5F);

	//start the PWM
	vRM4_N2HET_PWM__Dyanmic_Start(N2HET_CHANNEL__1, sAPU.sThrottle.u16N2HET_Index);


}


/***************************************************************************//**
 * @brief
 * Set direction forward
 * 
 * @st_funcMD5		ADCAD8B592BB5D9743AB5113471541BE
 * @st_funcID		LCCM720R0.FILE.006.FUNC.003
 */
void vAPU_THROTTLE__Forward(void)
{

	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 1U);

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
 * @st_funcMD5		00F1EFAD2D0FB25609A0B35A16CF8EE0
 * @st_funcID		LCCM720R0.FILE.006.FUNC.004
 */
void vAPU_THROTTLE__Reverse(void)
{

	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);

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
 * @st_funcMD5		0CFE9413650B3DBFC02297CB55529079
 * @st_funcID		LCCM720R0.FILE.006.FUNC.005
 */
void vAPU_THROTTLE__Enable(void)
{

	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 1U);

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
 * @st_funcMD5		3B0D6C4E589C54C2A59A5895C0FC2457
 * @st_funcID		LCCM720R0.FILE.006.FUNC.006
 */
void vAPU_THROTTLE__Disable(void)
{

	//set the bit
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 0U);

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

