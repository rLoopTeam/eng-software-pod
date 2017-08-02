/**
 * @file		LGU__LIFT_MECH.C
 * @brief		Lift Mechanism Functions
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.007
 */


/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup LGU__LIFT
 * @ingroup LGU
 * @{ */
 
 #include "../lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

extern TS_LGU__MAIN sLGU;

/***************************************************************************//**
 * @brief
 * Init the lift mechanism
 * 
 * @st_funcMD5		9934EC34BD356EAD39EDBB6DF5C2B968
 * @st_funcID		LCCM667R0.FILE.007.FUNC.001
 */
void vLGU_LIFT__Init(void)
{
	
#ifndef WIN32
	//configure the IO ports
	//H-Bridges
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___PWM_1);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___PWM_2);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___PWM_3);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___PWM_4);

	//direction ports
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_A1);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_B1);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_A2);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_B2);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_A3);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_B3);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_A4);
	vRM4_N2HET_PINS__Set_PinDirection_Output(C_LOCALDEF__LCCM667___DIR_B4);

	//make some programs
	//switch off N2HET before adding program
	vRM4_N2HET__Disable(N2HET_CHANNEL__1);

	//clear any old programs from the RAM
	vN2HET_PROG_DYNAMIC__Clear(N2HET_CHANNEL__1, 0xABCD1234U);

	//add the N2HET program
	sLGU.sPWM[0].u16ProgIndex = u16N2HET_PROG_DYNAMIC__Add_PWM(C_LOCALDEF__LCCM667___PWM_1, 0U);
	sLGU.sPWM[1].u16ProgIndex = u16N2HET_PROG_DYNAMIC__Add_PWM(C_LOCALDEF__LCCM667___PWM_2, 0U);
	sLGU.sPWM[2].u16ProgIndex = u16N2HET_PROG_DYNAMIC__Add_PWM(C_LOCALDEF__LCCM667___PWM_3, 0U);
	sLGU.sPWM[3].u16ProgIndex = u16N2HET_PROG_DYNAMIC__Add_PWM(C_LOCALDEF__LCCM667___PWM_4, 0U);

	//re-enable
	vRM4_N2HET__Enable(N2HET_CHANNEL__1);
#else
	//fake on WIN32
	sLGU.sPWM[0].u16ProgIndex = 0U;
	sLGU.sPWM[1].u16ProgIndex = 0U;
	sLGU.sPWM[2].u16ProgIndex = 0U;
	sLGU.sPWM[3].u16ProgIndex = 0U;
#endif //WIN32

	vLGU_LIFT__Set_Direction(0U, LIFT_DIR__EXTEND);
	vLGU_LIFT__Set_Direction(1U, LIFT_DIR__RETRACT);
	vLGU_LIFT__Set_Direction(2U, LIFT_DIR__RETRACT);
	vLGU_LIFT__Set_Direction(3U, LIFT_DIR__RETRACT);


	vLGU_LIFT__Set_Speed(0U, 0.9F);
	vLGU_LIFT__Set_Speed(1U, 0.5F);
	vLGU_LIFT__Set_Speed(2U, 0.5F);
	vLGU_LIFT__Set_Speed(3U, 0.5F);


}

/***************************************************************************//**
 * @brief
 * Process any lift tasks
 * 
 * @st_funcMD5		36799778BA999C2F66C54E752A4BF7D9
 * @st_funcID		LCCM667R0.FILE.007.FUNC.002
 */
void vLGU_LIFT__Process(void)
{
}


//Set the speed of the actuator in a percentage
void vLGU_LIFT__Set_Speed(Luint8 u8Actuator, Lfloat32 f32Percent)
{
	Lfloat32 f32Period_us;
	Lfloat32 f32Freq;

	//some default frequency of 5KHZ
	f32Freq = 5000.0F;

	//compute the period
	f32Period_us = 1.0F / f32Freq;

	//convert to us
	f32Period_us *= 1000000.0F;

	//protect the duty cycle
	if(f32Percent < 0.0F)
	{
		f32Percent = 0.0F;
	}
	else
	{
		if(f32Percent > 1.0F)
		{
			f32Percent = 1.0F;
		}
		else
		{
			//safe
		}

	}
	//update
	if(u8Actuator < C_LGU__NUM_ACTUATORS)
	{

#ifndef WIN32

		//update the frequency
		vRM4_N2HET_PWM__Dyanmic_SetPeriod(N2HET_CHANNEL__1, sLGU.sPWM[u8Actuator].u16ProgIndex, f32Period_us);

		//update the duty cycle
		vRM4_N2HET_PWM__Dyanmic_SetDutyCycle(N2HET_CHANNEL__1, sLGU.sPWM[u8Actuator].u16ProgIndex, f32Percent);

		//start the PWM
		vRM4_N2HET_PWM__Dyanmic_Start(N2HET_CHANNEL__1, sLGU.sPWM[u8Actuator].u16ProgIndex);
#endif //WIN32

	}
	else
	{
		//error
	}

}


//Sets the direction of an actuator
void vLGU_LIFT__Set_Direction(Luint8 u8Actuator, TE_LGU__LIFT_DIRECTIONS eDir)
{
	if(u8Actuator < C_LGU__NUM_ACTUATORS)
	{

		switch(eDir)
		{
			/** Actuator Off */
			case LIFT_DIR__NONE:

				//determine which actuator we are using
				switch(u8Actuator)
				{
					case 0:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A1, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B1, 0U);
#endif
						break;

					case 1:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A2, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B2, 0U);
#endif
						break;

					case 2:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A3, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B3, 0U);
#endif
						break;

					case 3:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A4, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B4, 0U);
#endif
						break;

					default:
						//error
						break;
				}//switch(u8Actuator)
				break;

			/** Raise the actuator */
			case LIFT_DIR__RETRACT:
				//determine which actuator we are using
				switch(u8Actuator)
				{
					case 0:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A1, 1U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B1, 0U);
#endif
						break;

					case 1:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A2, 1U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B2, 0U);
#endif
						break;

					case 2:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A3, 1U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B3, 0U);
#endif
						break;

					case 3:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A4, 1U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B4, 0U);
#endif
						break;

					default:
						//error
						break;
				}//switch(u8Actuator)
				break;

			/** Lower the actuator*/
			case LIFT_DIR__EXTEND:
				//determine which actuator we are using
				switch(u8Actuator)
				{

					case 0:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A1, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B1, 1U);
#endif
						break;

					case 1:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A2, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B2, 1U);
#endif
						break;

					case 2:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A3, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B3, 1U);
#endif
						break;

					case 3:
#ifndef WIN32
						//A
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_A4, 0U);
						//B
						vRM4_N2HET_PINS__Set_Pin(C_LOCALDEF__LCCM667___DIR_B4, 1U);
#endif
						break;

					default:
						//error
						break;
				}//switch(u8Actuator)
				break;

			default:
				//do nothing.
				break;
		}//switch(eDir)


	}
	else
	{
		//error
	}
}



#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


