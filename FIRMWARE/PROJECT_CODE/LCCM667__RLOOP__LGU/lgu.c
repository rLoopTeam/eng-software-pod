/**
 * @file		LGU.C
 * @brief		Landing Gear Unit
 * @note
 * IO PIN MAPPING
 *
 * N2HET1:2					PWM_1
 * N2HET1:18				DIR_A1
 * N2HET1:16				PWM_2
 * N2HET1:14				DIR_A2
 * N2HET1:12				PWM_3
 * N2HET1:6					DIR_B1
 * N2HET1:13				DIR_B2
 * N2HET1:4					DIR_A3
 * N2HET1:9					PWM_4
 * N2HET1:22				DIR_A4
 * N2HET1:27				DIR_B3
 * N2HET1:29				DIR_B4
 *
 *
 * GIOA:5					RETRACT_2
 * GIOA:2					EXTEND_2
 * GIOA:1					RETRACT_1
 * GIOA:0					EXTEND_1
 * GIOA:7					RETRACT_3
 * GIOA:6					EXTEND_3
 * GIOB:3					RETRACT_4
 * GIOB:2					EXTEND_4
 * @author		Lachlan Grogan
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.000
 */

/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup LGU__CORE
 * @ingroup LGU
 * @{ */
 
#include "lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

//Main structure
TS_LGU__MAIN sLGU;

/***************************************************************************//**
 * @brief
 * Init the landing gear unit
 * 
 * @st_funcMD5		B98A41297BC9D7630674FF7C2521E1E5
 * @st_funcID		LCCM667R0.FILE.000.FUNC.001
 */
void vLGU__Init(void)
{
	//setup flash memory access
#ifndef WIN32
	vRM4_FLASH__Init();

	//int the RM4's EEPROM
	#if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U
		vRM4_EEPROM__Init();
	#endif
#endif

	//init the EEPROM Params
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U
		vSIL3_EEPARAM__Init();
	#endif

#ifndef WIN32
	//init the DMA
	vRM4_DMA__Init();

	//GIO
	vRM4_GIO__Init();

	//on RM57 Launch, need this pin high
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 3U, GIO_DIRECTION__OUTPUT);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 3U, 1U);

	vRM4_DELAYS__Delay_mS(250);

	//test LED
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 6, GIO_DIRECTION__OUTPUT);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 0U);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 1U);


	//Setup the ADC
	#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U
		vRM4_ADC_USER__Init();
	#endif
#endif
	//CPU load monitoring
	vRM4_CPULOAD__Init();

#ifndef WIN32
	//setup the N2HET's
	vRM4_N2HET__Init(N2HET_CHANNEL__1, 0U, HR_PRESCALE__1, LR_PRESCALE__32);
	vRM4_N2HET_PINS__Init(N2HET_CHANNEL__1);

	#if C_LOCALDEF__LCCM240__ENABLE_N2HET2 == 1U
		vRM4_N2HET__Init(N2HET_CHANNEL__2, 0U, HR_PRESCALE__1, LR_PRESCALE__32);
		vRM4_N2HET_PINS__Init(N2HET_CHANNEL__2);
	#endif


	//configure the limit switches
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___RETRACT_1, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___EXTEND_1, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___RETRACT_2, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___EXTEND_2, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___RETRACT_3, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___EXTEND_3, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___RETRACT_4, GIO_DIRECTION__INPUT);
	vRM4_GIO__Set_BitDirection(C_LOCALDEF__LCCM667___EXTEND_4, GIO_DIRECTION__INPUT);

	//configure interrupts
/*
	vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_0);
	vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_1);

	//setup the interrupts
	vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_0);
	vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_1);
*/

	//init the user layer
	vRM4_ADC_USER__Init();

	//start the first conversion
	vRM4_ADC_USER__StartConversion();

#endif //win32

	//Init the MLP interface
	vLGU_MLP__Init();

	//Setup the lift control
	vLGU_LIFT__Init();

	//bring up the ethernet
	vLGU_ETH__Init();

	//start some timers if we need them
#ifndef WIN32
	//init the RTI
	vRM4_RTI__Init();

	//start the relevant RTI interrupts going.
	//100ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(0U);
	//10ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(1U);

	vRM4_RTI__Start_Interrupts();
	//Starts the counter zero
	vRM4_RTI__Start_Counter(0U);
	//counter 1 needed for 64bit timer.
	vRM4_RTI__Start_Counter(1U);
#endif //WIN32


#ifdef WIN32
	//for win32 DLL
	DEBUG_PRINT("LGU - Init()");
#endif

}

/***************************************************************************//**
 * @brief
 * Main Landing Gear Process Function
 * 
 * @st_funcMD5		964DF03CCFB853A03BF6BDF521C5F70F
 * @st_funcID		LCCM667R0.FILE.000.FUNC.002
 */
void vLGU__Process(void)
{

	//MLP interface
	vLGU_MLP__Process();

	//Ethernet
	vLGU_ETH__Process();

	//process the lifting actuators
	vLGU_LIFT__Process();
}



#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
