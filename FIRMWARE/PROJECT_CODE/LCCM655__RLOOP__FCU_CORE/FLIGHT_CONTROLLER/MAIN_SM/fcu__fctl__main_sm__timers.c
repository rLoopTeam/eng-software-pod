#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;

void vFCU_FCTL__TIMEOUT__Init(TS_FCTL__TIMEOUT_T *pTimeout, Luint32 u32Duration_x10ms)
{
	pTimeout->u32Duration_x10ms = u32Duration_x10ms;
	pTimeout->u32Elapsed_x10ms = 0;
	pTimeout->u8IsStarted = 0U;
}

void vFCU_FCTL__TIMEOUT__Restart(TS_FCTL__TIMEOUT_T *pTimeout)
{
	// Call this to start or restart a timeout
	pTimeout->u32Elapsed_x10ms = 0U;
	pTimeout->u8IsStarted = 1U;
}

void vFCU_FCTL__TIMEOUT__Reset(TS_FCTL__TIMEOUT_T *pTimeout)
{
	pTimeout->u32Elapsed_x10ms = 0U;
	pTimeout->u8IsStarted = 0U;
}



Luint8 u8FCU_FCTL__TIMEOUT__Is_Expired(TS_FCTL__TIMEOUT_T *pTimeout)
{
	return pTimeout->u32Elapsed_x10ms >= pTimeout->u32Duration_x10ms;
}

void vFCU_FCTL__TIMEOUT__Update_x10ms(TS_FCTL__TIMEOUT_T *pTimeout)
{
	pTimeout->u32Elapsed_x10ms += 1U;
}

void vFCU_FCTL__TIMEOUT__Ensure_Started(TS_FCTL__TIMEOUT_T *pTimeout)
{
	if ( ! pTimeout->u8IsStarted ) {
		// If we're not started, make sure we are and reset our elapsed time
		vFCU_FCTL__TIMEOUT__Restart(pTimeout);
	} else {
		// We're already started; nothing to do
	}
}


//safetys
#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
