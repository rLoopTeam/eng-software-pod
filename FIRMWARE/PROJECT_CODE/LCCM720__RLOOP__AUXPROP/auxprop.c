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
 */


#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
TS_APU__MAIN sAPU;

/***************************************************************************//**
 * @brief
 * Init the APU
 * 
 * @st_funcMD5		CE306F4306ED8C9AA58B61DC5B1BA2B9
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
		//vSIL3_EEPARAM__Init();
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

	//CPU Load minitoring
	vRM4_CPULOAD__Init();

	//N2HET needed for IO
	vRM4_N2HET__Init(N2HET_CHANNEL__1, 1U, HR_PRESCALE__1, LR_PRESCALE__32);
#endif	

	//configure the clutch control
	vAPU_CLUTCH__Init();

	//setup the ethernet
	vAPU_ETH__Init();

	//setup the throttle control channel
	vAPU_THROTTLE__Init();
	
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
		vAPU_DAQ__Init();
	#endif

#ifndef WIN32
	//int the RTI
	vRM4_RTI__Init();

	//100ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(0);
	//10ms timer
	vRTI_COMPARE__Enable_CompareInterrupt(1);

	
	
	vRM4_RTI__Start_Interrupts();
	//Starts the counter zero
	vRM4_RTI__Start_Counter(0);
	vRM4_RTI__Start_Counter(1);
#endif
	
	#ifdef WIN32
		DEBUG_PRINT("vAPU__Init()");
		vAPU_WIN32__Send_Generic_Update();
	#endif
	
	
}

/***************************************************************************//**
 * @brief
 * Process any APU tasks
 * 
 * @st_funcMD5		2EAED7B691DA64D86F2B0E6C5054E356
 * @st_funcID		LCCM720R0.FILE.000.FUNC.002
 */
void vAPU__Process(void)
{
	
#ifndef WIN32
	//CPU load monitoring processing.
	vRM4_CPULOAD__Process();

	//mark the entry point
	vRM4_CPULOAD__While_Entry();
#endif

	//process ethernet
	vAPU_ETH__Process();

	//process the clutch systems
	vAPU_CLUTCH__Process();

#ifndef WIN32
	//mark the exit point
	vRM4_CPULOAD__While_Exit();
#endif
	
}

#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

