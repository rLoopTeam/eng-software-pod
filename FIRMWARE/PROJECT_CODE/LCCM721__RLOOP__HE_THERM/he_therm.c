/**
 * @file		HE_THERM.C
 * @brief		Hover Engine Thermal management system.
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.000
 */


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
 * Init the HE thermal system
 * 
 * @st_funcMD5		A8D73F006B09664F71BEA2CC99FC9A71
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

	//on RM57 Launch, need this pin high
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 3U, GIO_DIRECTION__OUTPUT);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 3U, 1U);

	vRM4_DELAYS__Delay_mS(250);

	//test LED
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 6, GIO_DIRECTION__OUTPUT);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 0U);
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 1U);


	//CPU Load monitoring
	vRM4_CPULOAD__Init();
		
	//get the I2C up for the networked sensors
	vRM4_I2C_USER__Init(RM4_I2C_CH__1);

#endif //WIN32		
	
	//init ethernet
	vHETHERM_ETH__Init();
	
	//init thermocouples
	vHETHERM_TC__Init();

	//solenoids
	vHETHERM_SOL__Init();

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
 * Process any HE thermal tasks.
 * 
 * @st_funcMD5		7195AD6FA2AC38B07BBADC93B11065D8
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
	vHETHERM_ETH__Process();
	
	//process the thermocouples
	vHETHERM_TC__Process();
	
	//Process solenoids
	vHETHERM_SOL__Process();

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

