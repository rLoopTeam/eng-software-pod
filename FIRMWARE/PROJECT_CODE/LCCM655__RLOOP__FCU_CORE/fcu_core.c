/**
 * @file		FCU_CORE.C
 * @brief		Core of the flight control unit
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__CORE
 * @ingroup FCU
 * @{ */

#include "fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//main FCU structure;
struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the FCU. Call this first thing.
 * 
 * @st_funcMD5		CC1CE932DF70839CDB882B5F32B8106A
 * @st_funcID		LCCM655R0.FILE.000.FUNC.001
 */
void vFCU__Init(void)
{

	//init any FCU variabes
	sFCU.eInitStates = INIT_STATE__RESET;

	//setup some guarding, prevents people lunching the memory
	sFCU.u32Guard1 = 0xAABBCCDDU;
	sFCU.u32Guard2 = 0x12345678U;

	//setup the fault flags
	vFCU_FAULTS__Init();

}


/***************************************************************************//**
 * @brief
 * Process any FCU tasks.
 * 
 * @st_funcMD5		05CF3F7820A29ABF562E522CC9365071
 * @st_funcID		LCCM655R0.FILE.000.FUNC.002
 */
void vFCU__Process(void)
{
	Luint8 u8Counter;

	//check the guarding
	if(sFCU.u32Guard1 != 0xAABBCCDDU)
	{
		//guarding error fault
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}

	if(sFCU.u32Guard2 != 0x12345678U)
	{
		//guarding error fault
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}

	//process the states
	switch(sFCU.eInitStates)
	{
		case INIT_STATE__RESET:
			//first state after reset, handle some RM4 tasks

			//setup flash memory access
			vRM4_FLASH__Init();

			//int the RM4's EEPROM
			vRM4_EEPROM__Init();

			//init the EEPROM Params
			vEEPARAM__Init();

			//init the DMA
			vRM4_DMA__Init();

			//GIO
			vRM4_GIO__Init();

			//change state
			sFCU.eInitStates = INIT_STATE__INIT_IO;
			break;

		case INIT_STATE__INIT_IO:

			//setup the N2HET's
			vRM4_N2HET__Init(N2HET_CHANNEL__1, 0, LR_PRESCALE__32);
			vRM4_N2HET_PINS__Init(N2HET_CHANNEL__1);

			vRM4_N2HET__Init(N2HET_CHANNEL__2, 0, LR_PRESCALE__32);
			vRM4_N2HET_PINS__Init(N2HET_CHANNEL__2);


			//brakes outputs
			//already done in stepper init

			//setup the dynamic programs for
			//1. pusher interlock edges
			//2. contrast lasers
			//setup the pins
			vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 4U);
			vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 5U);

			//interrupts
			//Channel A1, A2
			vRM4_N2HET__Disable(N2HET_CHANNEL__1);
			//N2HET programs for the edge interrupts for pusher
			sFCU.sPusher.sSwitches[0].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 4U, EDGE_TYPE__BOTH, 1U);
			sFCU.sPusher.sSwitches[1].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 5U, EDGE_TYPE__BOTH, 1U);

			//programs for right brake limit switches
			sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 9U, EDGE_TYPE__BOTH, 1U);
			sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 22U, EDGE_TYPE__BOTH, 1U);
			sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog = 0U;
			sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog = 0U;

			vRM4_N2HET__Enable(N2HET_CHANNEL__1);

			//brake left inputs
			vRM4_GIO__Set_BitDirection(gioPORTA, 0U, GIO_DIRECTION__INPUT);
			vRM4_GIO__Set_BitDirection(gioPORTA, 1U, GIO_DIRECTION__INPUT);

			//configure the interrupts
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_0);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_1);

			//setup the interrupts
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_0);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_1);



			sFCU.eInitStates = INIT_STATE__INIT_COMMS;
			break;

		case INIT_STATE__INIT_COMMS:

			//setup UART, SCI2 = Pi Connection
			vRM4_SCI__Init(SCI_CHANNEL__2);
			vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600U);

			//setup our SPI channels.
			//ASI Interface
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

			//Serial channel's A
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__3);

			//serial subsystem B
			vRM4_SPI24__Init(SPI24_CHANNEL__2);

			//I2C Channel
			vRM4_I2C_USER__Init();

			//init the I2C
			sFCU.eInitStates = INIT_STATE__LOWER_SYSTEMS; //INIT_STATE__INIT_SPI_UARTS;
			break;

		case INIT_STATE__INIT_SPI_UARTS:

			//init all 7 of our uarts
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
			{
				//init the device
				vSC16__Init(u8Counter);

				//check the fault tree

				//configure for our baud if we are good
				vSC16_BAUD__Set_BaudRate(u8Counter, 1U, 192600U, 4U);

				//set to 1 stop bits.
				vSC16_BAUD__Set_Stopbits(u8Counter, 0U);

			}

			//move state
			sFCU.eInitStates = INIT_STATE__LOWER_SYSTEMS;
			break;

		case INIT_STATE__LOWER_SYSTEMS:

			//get our main SM operational
			vFCU_MAINSM__Init();

			sFCU.eInitStates = INIT_STATE__START_TIMERS;
			break;


		case INIT_STATE__START_TIMERS:

			//start the relevant RTI interrupts going.
			//100ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(0);
			//10ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(1);
			//10uS timer for the stepper system
			vRTI_COMPARE__Enable_CompareInterrupt(2);

			//int the RTI
			vRM4_RTI__Init();
			vRM4_RTI_ISR__Enable_Interrupts();
			//Starts the counter zero
			vRM4_RTI__Start_Counter(0);

			//move state
			sFCU.eInitStates = INIT_STATE__RUN;
			break;

		case INIT_STATE__RUN:

			//process the main state machine
			vFCU_MAINSM__Init();

			break;

	}//switch(sFCU.eInitStates)

}





//100ms timer
void vFCU__RTI_100MS_ISR(void)
{


}

//10ms timer
void vFCU__RTI_10MS_ISR(void)
{

	//tell the pusher interface about us.
	vFCU_PUSHER__10MS_ISR();
}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

