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
 * @st_funcMD5		70C3D19B744ABC24BDA133C0DD27A1BE
 * @st_funcID		LCCM653R0.FILE.000.FUNC.002
 */
void vPWRNODE__Process(void)
{

	Luint8 u8Test;

	//handle the init states here
	switch(sPWRNODE.sInit.sState)
	{


		case INIT_STATE__START:
			//We have been put into Init Start state, bring up the basic low level
			//RM4 systems that do not return error codes

			//setup flash memory access
			vRM4_FLASH__Init();

			//GIO
			vRM4_GIO__Init();

			//setup UART
			vRM4_SCI__Init(SCI_CHANNEL__2);
			vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600U);

			//move to next state
			sPWRNODE.sInit.sState = INIT_STATE__COMMS;

			break;


		case INIT_STATE__COMMS:
			//init any comms channels

			//get the SPI up for the BMS system
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

			//get the I2C up for the networked sensors
			vRM4_I2C_USER__Init();

			//move to next state
			sPWRNODE.sInit.sState = INIT_STATE__1_WIRE_START;
			break;


		case INIT_STATE__1_WIRE_START:
			//bring up the 1-wire interface(s)
			vDS2482S__Init();

			//check the result of the status flags for this system and if there is an
			//error decide what to do, either keep going or change to an error state

			//We have a choice here to re-scan each power up or supply the addresses via the network
			//for each sensor. For now we'll search

			sPWRNODE.sInit.sState = INIT_STATE__1_WIRE_SEARCH;
			break;

		case INIT_STATE__1_WIRE_SEARCH:
			//process the search
			vDS18B20_ADDX__SearchSM_Process();

			//check the satate
			u8Test = u8DS18B20_ADDX__SearchSM_IsBusy();
			if(u8Test == 1U)
			{
				//stay in the search state
				//ToDo: Update Timeout
			}
			else
			{
				//change state
				sPWRNODE.sInit.sState = INIT_STATE__1_WIRE_DONE;
			}
			break;

		case INIT_STATE__1_WIRE_DONE:
			//done searching 1-wire interface,
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

