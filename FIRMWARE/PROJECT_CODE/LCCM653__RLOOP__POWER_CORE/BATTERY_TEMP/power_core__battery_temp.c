/**
 * @file		POWER_CORE__BATTERY_TEMP.C
 * @brief		Battery Temperature Sensor, Bus Bars and Cells
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.009
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BATTERY_TEMP
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U

/***************************************************************************//**
 * @brief
 * Init the battery temperature measurement devices
 * 
 * @st_funcMD5		125710767486723A58326AAA59E627DA
 * @st_funcID		LCCM653R0.FILE.009.FUNC.001
 */
void vPWRNODE_BATTTEMP__Init(void)
{
#ifndef WIN32
	//bring up the 1-wire interface(s)
	vDS2482S__Init();

	//check the result of the status flags for this system and if there is an
	//error decide what to do, either keep going or change to an error state

	//We have a choice here to re-scan each power up or supply the addresses via the network
	//for each sensor. For now we'll search

	//start the temp sensor driver
	vDS18B20__Init();
#endif
}


/***************************************************************************//**
 * @brief
 * Process any battery temp measurement tasks
 * 
 * @st_funcMD5		716F10371EC26421C99A1DD629ED9105
 * @st_funcID		LCCM653R0.FILE.009.FUNC.002
 */
void vPWRNODE_BATTTEMP__Process(void)
{
#ifndef WIN32
	//process any search tasks
	vDS18B20_ADDX__SearchSM_Process();
#endif
}


/***************************************************************************//**
 * @brief
 * Start a search of any devices on the network
 * 
 * @st_funcMD5		44524ACD1CAC2160BEBA831938D2122E
 * @st_funcID		LCCM653R0.FILE.009.FUNC.003
 */
void vPWRNODE_BATTTEMP__Start_Search(void)
{
#ifndef WIN32
	//start the search state machine
	vDS18B20_ADDX__SearchSM_Start();
#endif
}


/***************************************************************************//**
 * @brief
 * Check to see if the batt temp sensor search process is busy
 * 
 * @return			0 = not busy\n
 *					1 = busy
 * @st_funcMD5		CF96C635BC6184E9E3C82972F7EFA099
 * @st_funcID		LCCM653R0.FILE.009.FUNC.004
 */
Luint8 u8PWRNODE_BATTTEMP__Search_IsBusy(void)
{
#ifndef WIN32
	return u8DS18B20_ADDX__SearchSM_IsBusy();
#else
	return 0U;
#endif
}

#endif //C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

