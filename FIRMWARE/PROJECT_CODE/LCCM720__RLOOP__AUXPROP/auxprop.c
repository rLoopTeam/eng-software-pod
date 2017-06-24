/**
 * @file		AUXPROP.C
 * @brief		Core File
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.000
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
 * @addtogroup AUXPROP__CORE
 * @ingroup AUXPROP
 * @{
*/

/* RM57 Launchpad Connections
 * See: http://www.ti.com/lit/ml/spnu616/spnu616.pdf
 *
 * J4:1		N2HET1:2		LEFT_CLUTCH
 * J4:2		N2HET1:18		RIGHT_CLUTCH
 * J4:3		N2HET1:16		LEFT_DIR
 * J4:4		N2HET1:30		RIGHT_DIR
 * J4:5		N2HET1:14		LEFT_PWM
 * J4:6		N2HET1:13		RIGHT_PWM
 *
 */


#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
TS_APU__MAIN sAPU;

/***************************************************************************//**
 * @brief
 * Init the APU
 * 
 * @st_funcMD5		9F3032F0BF6440DE53B0790362A22787
 * @st_funcID		LCCM720R0.FILE.000.FUNC.001
 */
void vAPU__Init(void)
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

	//CPU Load minitoring
	vRM4_CPULOAD__Init();

	//setup UART, SCI2 = Pi Connection
	//vRM4_SCI__Init(SCI_CHANNEL__2);
	//vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 57600U);
	
	//N2HET needed for IO
	vRM4_N2HET__Init(N2HET_CHANNEL__1, 1U, HR_PRESCALE__1, LR_PRESCALE__32);
#endif	

	//configure the clutch control
	vAPU_CLUTCH__Init();

	vAPU_ETH__Init();

	vAPU_THROTTLE__Init();
	
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
		vAPU_DAQ__Init();
	#endif

#ifndef WIN32
	//int the RTI
	vRM4_RTI__Init();

	//start the relevant RTI interrupts going.
	//100ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(0);
	
	
	vRM4_RTI__Start_Interrupts();
	//Starts the counter zero
	vRM4_RTI__Start_Counter(0);
	vRM4_RTI__Start_Counter(1);
#endif
	
	#ifdef WIN32
		vAPU_WIN32__Send_Generic_Update();
	#endif
	
	
}

/***************************************************************************//**
 * @brief
 * Process any APU tasks
 * 
 * @st_funcMD5		8EF605122727951038A1777EAA22BEB7
 * @st_funcID		LCCM720R0.FILE.000.FUNC.002
 */
void vAPU__Process(void)
{
	
	//process the clutch systems
	vAPU_CLUTCH__Process();

	
}

#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

