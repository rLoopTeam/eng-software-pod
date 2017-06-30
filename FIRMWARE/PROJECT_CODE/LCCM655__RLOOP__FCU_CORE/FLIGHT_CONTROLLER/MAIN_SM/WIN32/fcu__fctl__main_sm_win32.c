/*
 * fcu__fctl__main_sm_win32.c
 *
 *  Created on: Jan 27, 2017
 *      Author: rutayanpatro
 */
#include "../../../fcu_core.h"

#ifdef WIN32
// Pointer to callback to a function in python simulator
pDEBUG_RECORD_Callback_FuncType pSimulatorCallback;
#endif // WIN32

#ifdef WIN32
/***************************************************************************//**
 * @brief
 * Function used by python simulation to register a callback in fcu core
 *
 * @st_funcMD5
 * @st_funcID
 */
void vDEBUG_RECORD_WIN32__Set_MissionPhaseCallback(pDEBUG_RECORD_Callback_FuncType pFunc)
{
	pSimulatorCallback = pFunc;
}

/***************************************************************************//**
 * @brief
 * FCU core calls this function to call the python callback function
 *
 * @st_funcMD5
 * @st_funcID
 */
void vDEBUG_RECORD_WIN32__MissionPhaseCallback(E_FCU__MISSION_PHASE_T eMissionPhase)
{
	// call the python function. Python can see this missionphase now
	pSimulatorCallback( (Luint8 )eMissionPhase);
}

#endif  // WIN32



