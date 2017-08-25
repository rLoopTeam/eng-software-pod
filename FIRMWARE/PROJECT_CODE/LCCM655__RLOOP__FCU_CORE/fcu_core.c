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
 * @st_funcMD5		2C8E60FCEAD2D5CB34C0611CC751565F
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

#ifdef WIN32
	//for win32 DLL
	DEBUG_PRINT("FCU - Init()");
#endif

}


/***************************************************************************//**
 * @brief
 * Process any FCU tasks.
 * 
 * @st_funcMD5		ACB21F42875995E707CB8B16C0F6F1AD
 * @st_funcID		LCCM655R0.FILE.000.FUNC.002
 */
void vFCU__Process(void)
{
	Luint8 u8Counter;

	//check the guarding
	if(sFCU.u32Guard1 != 0xAABBCCDDU)
	{
		//guarding error fault
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__01);
	}
	else
	{
		//fall on
	}

	if(sFCU.u32Guard2 != 0x12345678U)
	{
		//guarding error fault
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__00);
		vSIL3_FAULTTREE__Set_Flag(&sFCU.sFaults.sTopLevel, C_LCCM655__CORE__FAULT_INDEX__01);
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
#ifndef WIN32
			#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U
				vRM4_FLASH__Init();
			#endif

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

			//GIO
			vRM4_GIO__Init();

			//Setup the ADC
			#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U
				vRM4_ADC_USER__Init();
			#endif
#endif
			#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U
				//CPU load monitoring
				vRM4_CPULOAD__Init();
			#endif

			//change state
			sFCU.eInitStates = INIT_STATE__INIT_IO;
			break;

		case INIT_STATE__INIT_IO:

#ifndef WIN32
			//setup the N2HET's
			#if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U
				vRM4_N2HET__Init(N2HET_CHANNEL__1, 0U, HR_PRESCALE__1, LR_PRESCALE__32);
				vRM4_N2HET_PINS__Init(N2HET_CHANNEL__1);
			#endif

			#if C_LOCALDEF__LCCM240__ENABLE_N2HET2 == 1U
				vRM4_N2HET__Init(N2HET_CHANNEL__2, 0U, HR_PRESCALE__1, LR_PRESCALE__32);
				vRM4_N2HET_PINS__Init(N2HET_CHANNEL__2);
			#endif


			//brakes outputs
			//already done in stepper init

			//setup the dynamic programs for
			//1. pusher interlock edges
			//2. contrast lasers
			//setup the pins
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 4U);
				vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 5U);
			#endif
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 9U);
				vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 22U);
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
			//laser contrast sensors
			vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 6U);
			vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 7U);
			vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 13U);
			#endif

			#if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U
				//must disable N2HET before adding programs.
				vRM4_N2HET__Disable(N2HET_CHANNEL__1);
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				//N2HET programs for the edge interrupts for pusher
				sFCU.sPusher.sSwitches[0].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 4U, EDGE_TYPE__BOTH, 1U);
				sFCU.sPusher.sSwitches[1].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 5U, EDGE_TYPE__BOTH, 1U);
			#endif

			//programs for right brake limit switches
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 9U, EDGE_TYPE__BOTH, 1U);
				sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 22U, EDGE_TYPE__BOTH, 1U);
				sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog = 0U;
				sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog = 0U;
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

				//setup the contrast sensor programs
				//FWD laser on both edge triggeers.
				sFCU.sContrast.sSensors[LASER_CONT__FWD].u16N2HET_Index = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 6U, EDGE_TYPE__BOTH, 1U);
				sFCU.sContrast.sSensors[LASER_CONT__MID].u16N2HET_Index = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 7U, EDGE_TYPE__RISING, 1U);
				sFCU.sContrast.sSensors[LASER_CONT__AFT].u16N2HET_Index = u16N2HET_PROG_DYNAMIC__Add_Edge(N2HET_CHANNEL__1, 13U, EDGE_TYPE__RISING, 1U);
			#endif

			#if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U
				//once all the programs are added, enable the N2HET:1
				vRM4_N2HET__Enable(N2HET_CHANNEL__1);
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				//brake left inputs
				vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 0U, GIO_DIRECTION__INPUT);
				vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 1U, GIO_DIRECTION__INPUT);

				//configure the interrupts
				vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_0);
				vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__BOTH, GIO_ISR_PIN__GIOA_1);

				//setup the interrupts
				vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_0);
				vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_1);
			#endif
#endif //win32
			sFCU.eInitStates = INIT_STATE__INIT_COMMS;
			break;

		case INIT_STATE__INIT_COMMS:

#ifndef WIN32
			//setup UART, SCI2 = Pi Connection
			#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U
				vRM4_SCI__Init(SCI_CHANNEL__2);
				vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 57600U);
			#endif

			#if C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE == 1U
				//setup our SPI channels.
				//ASI Interface
				vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

				//Serial channel's A
				vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__3);

				//SPI5 needed for some pin functions
				vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__5);


				//set the WDT pulse output which is used for RM57 reset.
				vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3);
				vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3, 1U);
				vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3, 0U);
			#endif

			//serial subsystem B
			#if C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE == 1U
				vRM4_SPI24__Init(SPI24_CHANNEL__2);
			#endif

			//I2C Channel
			#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U
				vRM4_I2C_USER__Init(RM4_I2C_CH__1);
			#endif
/*
			//Testing damaged FCU pins
			vRM4_I2C_PINS__Set_SCL_Tris(RM4_I2C_CH__1, 0);
			vRM4_I2C_PINS__Set_SCL_Latch(RM4_I2C_CH__1, 1);
			vRM4_I2C_PINS__Set_SCL_Latch(RM4_I2C_CH__1, 0);

			vRM4_I2C_PINS__Set_SDA_Tris(RM4_I2C_CH__1, 0);
			vRM4_I2C_PINS__Set_SDA_Latch(RM4_I2C_CH__1, 1);
			vRM4_I2C_PINS__Set_SDA_Latch(RM4_I2C_CH__1, 0);
*/
#endif //win32
			//init the I2C
			sFCU.eInitStates = INIT_STATE__INIT_SPI_UARTS;
			break;

		case INIT_STATE__INIT_SPI_UARTS:

			#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
#ifndef WIN32
			//give us some interrupts going
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 2U, GIO_DIRECTION__INPUT);
			//caution on RM57, this pin is needed for the MAC
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 3U, GIO_DIRECTION__INPUT);
			//caution on RM57, this pin is needed for the MAC
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 4U, GIO_DIRECTION__INPUT);

			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 1U, GIO_DIRECTION__INPUT);
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 3U, GIO_DIRECTION__INPUT);
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 6U, GIO_DIRECTION__INPUT);
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 0U, GIO_DIRECTION__INPUT);
			//ASI
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 7U, GIO_DIRECTION__INPUT);


			//configure the interrupts
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_2);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_3);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOA_4);

			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOB_1);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOB_3);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOB_6);
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOB_0);
			//ASI
			vRM4_GIO_ISR__Set_InterruptPolarity(GIO_POLARITY__FALLING, GIO_ISR_PIN__GIOB_7);


			//setup the interrupts
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_2);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_3);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOA_4);

			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOB_1);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOB_3);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOB_6);
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOB_0);
			//ASI
			vRM4_GIO_ISR__EnableISR(GIO_ISR_PIN__GIOB_7);
#endif //WIN32

			//init all 7 of our uarts
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
			{
				//init the device
				vSIL3_SC16__Init(u8Counter);

				//check the fault tree

				//configure for our baud if we are good
				if(u8Counter == C_FCU__SC16_ASI_INDEX)
				{
					//ASI IF
					vSIL3_SC16_BAUD__Set_BaudRate(u8Counter, 1U, 9600U, 1U);

				}
				else if(u8Counter == C_FCU__SC16_FWD_LASER_INDEX)
				{
					//NOPTEL
					vSIL3_SC16_BAUD__Set_BaudRate(u8Counter, 1U, 9600U, 1U);
				}
				else
				{
					//optoNCDT's
					vSIL3_SC16_BAUD__Set_BaudRate(u8Counter, 1U, 19200U, 1U);

				}


				//8bits, noparity
				vSIL3_SC16_BAUD__Set_Wordlength(u8Counter, 8U);
				vSIL3_SC16_FLOWCONTROL__Enable_Parity(u8Counter, 0U);

				//set to 1 stop bits.
				vSIL3_SC16_BAUD__Set_Stopbits(u8Counter, 0U);


				//set the Rx trig level to prevent software overhead.
				//todo: this will have problems with some devices that are waiting on a reply
				//such as the ASI system


				//configure for our baud if we are good
				if(u8Counter == C_FCU__SC16_ASI_INDEX)
				{
					//ASI IF
					//use FIFO mode
					vSIL3_SC16_FIFO___Enable_FIFOs(u8Counter, 1U);

					//reset
					vSIL3_SC16_FIFO__Reset_Rx_FIFO(u8Counter, 1U);
					vSIL3_SC16_FIFO__Reset_Tx_FIFO(u8Counter, 1U);

					//small trigger level.
					vSIL3_SC16_FLOWCONTROL__Set_RxTrigger_Level(u8Counter, 8U);

				}
				else if(u8Counter == C_FCU__SC16_FWD_LASER_INDEX)
				{
					//NOPTEL
					//use FIFO mode
					vSIL3_SC16_FIFO___Enable_FIFOs(u8Counter, 1U);

					//reset
					vSIL3_SC16_FIFO__Reset_Rx_FIFO(u8Counter, 1U);
					vSIL3_SC16_FIFO__Reset_Tx_FIFO(u8Counter, 1U);

					vSIL3_SC16_FLOWCONTROL__Set_RxTrigger_Level(u8Counter, 16U);
				}
				else
				{
					//optoNCDT's
					//use FIFO mode
					vSIL3_SC16_FIFO___Enable_FIFOs(u8Counter, 1U);

					//reset
					vSIL3_SC16_FIFO__Reset_Rx_FIFO(u8Counter, 1U);
					vSIL3_SC16_FIFO__Reset_Tx_FIFO(u8Counter, 1U);

					vSIL3_SC16_FLOWCONTROL__Set_RxTrigger_Level(u8Counter, 16U);

				}


				//Rx Int
				vSIL3_SC16_INT__Enable_Rx_DataAvalibleInterupt(u8Counter, 1U);
			}
			#endif //#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

			//todo:
			//setup the baud for the lasers only



			//move state
			sFCU.eInitStates = INIT_STATE__LOWER_SYSTEMS;
			break;

		case INIT_STATE__LOWER_SYSTEMS:

			//start DAQ
			#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
				vSIL3_DAQ__Init();
			#endif

			//start the network
			#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
				vFCU_NET__Init();
			#endif

			sFCU.eInitStates = INIT_STATE__START_TIMERS;
			break;


		case INIT_STATE__START_TIMERS:

#ifndef WIN32
			#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U
			//int the RTI
			vRM4_RTI__Init();

			//start the relevant RTI interrupts going.
			//100ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(0U);
			//10ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(1U);
			//10uS timer for the stepper system
			vRTI_COMPARE__Enable_CompareInterrupt(2U);


			vRM4_RTI__Start_Interrupts();
			//Starts the counter zero
			vRM4_RTI__Start_Counter(0U);
			//counter 1 needed for 64bit timer.
			vRM4_RTI__Start_Counter(1U);
			#endif //C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE
#endif //WIN32


			//move state
			sFCU.eInitStates = INIT_STATE__START_POD_SYSTEMS;
			break;

		case INIT_STATE__START_POD_SYSTEMS:

			//init the acclerometer system
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL__Init();
			#endif

			//laser distance
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
				vFCU_LASERDIST__Init();
			#endif

			//Init the throttles
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
				vFCU_THROTTLE__Init();
			#endif

			//laser contrast sensors
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
				vFCU_LASERCONT__Init();
			#endif

			//init the brake systems
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES__Init();
			#endif

			//init the ASI RS485 interface
			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
				vFCU_ASI__Init();
			#endif

			//laser opto's
			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				vFCU_LASEROPTO__Init();
			#endif

			//pusher
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vFCU_PUSHER__Init();
			#endif

			//the final thing to start is the flight controller
			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				vFCU_FCTL__Init();
			#endif

			//release RM57 boards from reset.
			vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3, 1U);

			//move state
			sFCU.eInitStates = INIT_STATE__RUN;
			break;

		case INIT_STATE__RUN:

			#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U
				//CPU load processing
				vRM4_CPULOAD__Process();

				//start of while entry point
				vRM4_CPULOAD__While_Entry();
			#endif

			#ifndef WIN32
			#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U
				//Handle the ADC conversions
				vRM4_ADC_USER__Process();
			#endif
			#endif //WIN32

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
				vFCU_LASERDIST__Process();
			#endif

			//process the SC16IS interface always
			#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
				for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM487__NUM_DEVICES; u8Counter++)
				{
					vSIL3_SC16__Process(u8Counter);
				}
			#endif

			// process the throttles
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U

				vFCU_THROTTLE__Process();

				// process the AMC7812
				vAMC7812__Process();
			#endif

			//process networking
			#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
				vFCU_NET__Process();
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				vFCU_LASEROPTO__Process();
			#endif

			//laser orientation
			#if C_LOCALDEF__LCCM655__ENABLE_ORIENTATION == 1U
				vFCU_LASER_ORIENTATION__Process();
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
				vFCU_LASERCONT__Process();
			#endif


			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vFCU_PUSHER__Process();
			#endif

			//process the brakes.
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES__Process();
			#endif

			//process the accel channels
			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vFCU_ACCEL__Process();
			#endif

			//ASI RS485 interface
			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
				vFCU_ASI__Process();
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
				vFCU_FCTL__Process();
			#endif

			//do the DAQ
			#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
				vSIL3_DAQ__Process();
			#endif

			//update any system fault flags.
			vFCU_FAULTS__Process();

			#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U
				//end of while loop
				vRM4_CPULOAD__While_Exit();
			#endif

			break;

	}//switch(sFCU.eInitStates)

}

/***************************************************************************//**
 * @brief
 * 100ms timer
 * 
 * @st_funcMD5		03503B3F34FAC7AC38ADD5C6CB0C49F6
 * @st_funcID		LCCM655R0.FILE.000.FUNC.003
 */
void vFCU__RTI_100MS_ISR(void)
{

	//OptoNCDT Timer
	#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
		vFCU_LASEROPTO__100MS_ISR();
	#endif

	//Laser Distance System
	#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
		vFCU_LASERDIST__100MS_ISR();
	#endif

	// Timer for throttle layer
	#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
		vFCU_THROTTLE__100MS_ISR();
	#endif

	//ethernet timed packets
	#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
		vFCU_NET_TX__100MS_ISR();
	#endif

	//brakes timed processes
	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vFCU_BRAKES__100MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__100MS_ISR();
	#endif
	#endif

}


/***************************************************************************//**
 * @brief
 * 10ms timer
 * 
 * @st_funcMD5		108C5BC0C716532C2EFC6CA606ACB925
 * @st_funcID		LCCM655R0.FILE.000.FUNC.004
 */
void vFCU__RTI_10MS_ISR(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
		vFCU_NET_TX__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_ACCEL
		vFCU_ACCEL__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
		//tell the pusher interface about us.
		vFCU_PUSHER__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
		vFCU_ASI__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
		vFCU_BRAKES__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_DRIVE_POD_CONTROL == 1U
		vFCU_FCTL_DRIVEPOD__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__10MS_ISR();
	#endif
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

