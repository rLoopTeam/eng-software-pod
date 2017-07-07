/**
 * @file		HE_THERM.C
 * @brief		
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM721R0.FILE.000
 */
/**
 * @addtogroup PROJECT_NAME
 * @{
 */
/**
 * @addtogroup PROJECT_NAME
 * @ingroup MODULE_NAME
 * @{
 */
/**
 * @addtogroup MODULE_NAME__CORE
 * @ingroup MODULE_NAME
 * @{
 */
/** @} */
/** @} */
/** @} */


/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__CORE
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U

//Main structure
TS_HET__MAIN sHET;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		F4492C61D013C42D30961A4D252B285A
 * @st_funcID		LCCM721R0.FILE.000.FUNC.001
 */
void vHETHERM__Init(void)
{
	
#ifndef WIN32
	//setup flash memory access
	vRM4_FLASH__Init();

	//int the RM4's EEPROM
	#if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U
		vRM4_EEPROM__Init();
	#endif

	//init the EEPROM Params
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U
		vSIL3_EEPARAM__Init();
	#endif
	
	//GIO
	vRM4_GIO__Init();

	//CPU Load monitoring
	vRM4_CPULOAD__Init();
		
	//get the I2C up for the networked sensors
	vRM4_I2C_USER__Init();

#endif //WIN32		
	
	//init ethernet
	vHETHERM_ETH__Init();
	
	//init thermocouples
	vHETHERM_TC__Init();

#ifndef WIN32
	//int the RTI
	vRM4_RTI__Init();

	//start the relevant RTI interrupts going.
	//100ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(0);
	//10ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(1);

	vRM4_RTI__Start_Interrupts();
	//Starts the counter zero
	vRM4_RTI__Start_Counter(0);
	vRM4_RTI__Start_Counter(1);
	
#endif //WIN32

}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		BA3D111D252139939973969EBA907DB7
 * @st_funcID		LCCM721R0.FILE.000.FUNC.002
 */
void vHETHERM__Process(void)
{

#ifndef WIN32
	//CPU load monitoring processing.
	vRM4_CPULOAD__Process();

	//mark the entry point
	vRM4_CPULOAD__While_Entry();
#endif

	//process ethernet
	vHETHERM_ETH__Init();
	
	//process the thermocouples
	vHETHERM_TC__Process();
	
#ifndef WIN32
	//mark the exit point
	vRM4_CPULOAD__While_Exit();	
#endif
}


#endif //#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

