/**
 * @file		FCU__FCTL__TRACK_DATABASE.C
 * @brief		Track Management Database
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
 * @addtogroup FCU__FLIGHT_CTL__TRACK_DATABASE
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#include "fcu__fctl__track_database__types.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U

//the structure
extern struct _strFCU sFCU;

//The current working track database
struct _strTrackDatabases sTrackDB;

void vFCU_FCTL_TRACKDB__Init(void)
{

	vFAULTTREE__Init(&sFCU.sFlightControl.sTrackDB.sFaultFlags);

	//get the memory up
	vFCU_FCTL_TRACKDB_MEM__Init();

}



void vFCU_FCTL_TRACKDB__Process(void)
{
	vFCU_FCTL_TRACKDB_MEM__Process();

}



#endif //C_LOCALDEF__LCCM655__ENABLE_TRACK_DB
#ifndef C_LOCALDEF__LCCM655__ENABLE_TRACK_DB
	#error
#endif

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

