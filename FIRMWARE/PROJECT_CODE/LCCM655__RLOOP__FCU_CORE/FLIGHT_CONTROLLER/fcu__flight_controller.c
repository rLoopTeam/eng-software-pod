/**
 * @file		FCU__FLIGHT_CONTROLLER.C
 * @brief		The actual flight control algo's
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__FLIGHT_CTL
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		61224CE144104FD40882DF507A463938
 * @st_funcID		LCCM655R0.FILE.035.FUNC.001
 */
void vFCU_FCTL__Init(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		//setup laser orientation module
		vFCU_FLIGHTCLT_LASERORIENT__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		//setup contrast sensor nav module
		vFCU_FLIGHTCTL_CONTRASTNAV__Init();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		//getting the track databse loaded configures our data
		vFCU_FCTL_TRACKDB__Init();
	#endif

	//now that the track database was loaded, we need to configure our settings
	vFCU_FCTL__Config_From_Database();

	//Configure the main state machine
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__Init();
	#endif

	//init the navigation system
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U
	vFCU_FCTL_NAV__Init();
#endif

}


/***************************************************************************//**
 * @brief
 * Process the flight controller
 * 
 * @st_funcMD5		905B1E3D5EF9A5AECFDF568F73F372C4
 * @st_funcID		LCCM655R0.FILE.035.FUNC.002
 */
void vFCU_FCTL__Process(void)
{

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
		vFCU_FLIGHTCLT_LASERORIENT__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV == 1U
		vFCU_FLIGHTCTL_CONTRASTNAV__Process();
	#endif

	#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
		vFCU_FCTL_TRACKDB__Process();
	#endif

	//process navigation
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U
	vFCU_FCTL_NAV__Process();
#endif

	//process the main state machine
	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
		vFCU_FCTL_MAINSM__Process();
	#endif

}


//based on our current track ID, configure all the subsystems from the
//track database
void vFCU_FCTL__Config_From_Database(void)
{

#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
	//accel system
	//enable the Accel system
	vFCU_ACCEL_VALID__Enable(u8FCU_FCTL_TRACKDB__Accel__Get_Use());

	//load up the thresholding
	vFCU_ACCEL_THRESH__Set_Threshold(s32FCU_FCTL_TRACKDB__Accel__Get_Threshold_mm_ss(), s32FCU_FCTL_TRACKDB__Accel__Get_ThresholdTime_x10ms());
#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL

	//fwd laser

	//contrast laser

	//state machine options


	//track options


}



#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

