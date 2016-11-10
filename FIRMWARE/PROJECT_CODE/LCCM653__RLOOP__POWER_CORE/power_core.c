/**
 * @file		POWER_CORE.C
 * @brief		Top Level for the Power Node Core systems
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__CORE
 * @ingroup POWER_NODE
 * @{ */

#include "power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the power node, this should be the first call
 * 
 * @st_funcMD5		EB03B89D86A4E961B7C982E89CA4A3EA
 * @st_funcID		LCCM653R0.FILE.000.FUNC.001
 */
void vPWRNODE__Init(void)
{
	//setup the power node basic states and allow the process function to bring all the devices and
	//subsystems on line.
	sPWRNODE.sInit.sState = INIT_STATE__START;

}


/***************************************************************************//**
 * @brief
 * Process the power node states, this should be called as quick as possible from
 * the main program loop.
 * 
 * @st_funcMD5		050D52427C2B119643AE863198B0965D
 * @st_funcID		LCCM653R0.FILE.000.FUNC.002
 */
void vPWRNODE__Process(void)
{

	Luint8 u8Test;

	//handle the init states here
	/**
	\dot
	 digraph G {
	 INIT_STATE__START -> INIT_STATE__COMMS [label = "After Setup"];
	 INIT_STATE__COMMS -> INIT_STATE__BATT_TEMP_START [label = "After configure serial comms devices"];
	 INIT_STATE__CELL_TEMP_START -> INIT_STATE__CELL_TEMP_SEARCH;
	 INIT_STATE__CELL_TEMP_SEARCH -> INIT_STATE__CELL_TEMP_SEARCH [label = "u8DS18B20_ADDX__SearchSM_IsBusy() == 1"];
	 INIT_STATE__CELL_TEMP_SEARCH -> INIT_STATE__CELL_TEMP_SEARCH_DONE  [label = "u8DS18B20_ADDX__SearchSM_IsBusy() == 0"];
	 INIT_STATE__CELL_TEMP_SEARCH_DONE -> INIT_STATE__BMS
	 }
	 \enddot
	 */
	switch(sPWRNODE.sInit.sState)
	{

		case INIT_STATE__UNKNOWN:
			//todo
			//should never get here.
			break;

		case INIT_STATE__START:
#ifndef WIN32
			//We have been put into Init Start state, bring up the basic low level
			//RM4 systems that do not return error codes

			//setup flash memory access
			vRM4_FLASH__Init();

			//DMA
			vRM4_DMA__Init();

			//GIO
			vRM4_GIO__Init();

			//setup UART, SCI2 = Pi Connection
			vRM4_SCI__Init(SCI_CHANNEL__2);
			vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 57600);


#else
			//Init any win32 variables
			vPWRNODE_WIN32__Init();

			//emit a message
			DEBUG_PRINT("INIT_STATE__START");
#endif

			//start the pi comms layer
			vPWRNODE_PICOMMS__Init();

			//move to next state
			sPWRNODE.sInit.sState = INIT_STATE__COMMS;

			break;


		case INIT_STATE__COMMS:
#ifndef WIN32
			//init any comms channels

			//get the SPI up for the BMS system
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

			//get the I2C up for the networked sensors
			vRM4_I2C_USER__Init();
#endif
			//move to next state
			sPWRNODE.sInit.sState = INIT_STATE__CELL_TEMP_START;
			break;


		case INIT_STATE__CELL_TEMP_START:

			//start the battery temp system
			vPWRNODE_BATTTEMP__Init();

			//start a search
			vPWRNODE_BATTTEMP__Start_Search();

			sPWRNODE.sInit.sState = INIT_STATE__CELL_TEMP_SEARCH;
			break;

		case INIT_STATE__CELL_TEMP_SEARCH:
			//process the search
			vPWRNODE_BATTTEMP__Process();

			//check the satate
			u8Test = u8PWRNODE_BATTTEMP__Search_IsBusy();
			if(u8Test == 1U)
			{
				//stay in the search state
				//ToDo: Update Timeout
			}
			else
			{
				//change state
				sPWRNODE.sInit.sState = INIT_STATE__CELL_TEMP_SEARCH_DONE;
			}
			break;

		case INIT_STATE__CELL_TEMP_SEARCH_DONE:
			//done searching 1-wire interface,

			//todo, handle any results from the search

			//next get the BMS going
			sPWRNODE.sInit.sState = INIT_STATE__BMS;
			break;

		case INIT_STATE__BMS:

			//init the BMS layer
			vPWRNODE_BMS__Init();

			//start the TSYS01 temp sensor
			sPWRNODE.sInit.sState = INIT_STATE__TSYS01;
			break;


		case INIT_STATE__TSYS01:
			// ONLY NEEDS TO BE RUN ONCE
		
			// init TSYS01 ambient PV Temperature Sensor
			vTSYS01__Init();

			//change to run state
			sPWRNODE.sInit.sState = INIT_STATE__RUN;
			break;


		case INIT_STATE__RUN:

			//normal run state

			vPWRNODE_PICOMMS__Process();

			//process any BMS tasks
			vPWRNODE_BMS__Process();

			//process any temp sensor items
			vPWRNODE_BATTTEMP__Process();

			//process the TSYS01 device
			vTSYS01__Process();

			break;



		default:
			//todo:
			break;

	}//switch(sPWRNODE.sInit.sState)


}



#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

