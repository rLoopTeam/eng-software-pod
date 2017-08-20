#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;



/////////////////////////////////////////////////////////////////////
//  Timers and timeouts
/////////////////////////////////////////////////////////////////////

TS_FCTL__TIMEOUT_T create_timeout(Luint32 duration_ms)
{
	TS_FCTL__TIMEOUT_T t;
	t.u32Duration_x10ms = duration_ms;
	t.u32Elapsed_x10ms = 0;
	t.u8IsStarted = 0U;
	return t;
}

void vFCU_FCTL_MAINSM_TIMER__Init(TS_FCTL__TIMEOUT_T *pTimeout, Luint32 u32Duration_x10ms)
{
	pTimeout->u32Duration_x10ms = u32Duration_x10ms;
	pTimeout->u32Elapsed_x10ms = 0;
	pTimeout->u8IsStarted = 0U;
}

void vFCU_FCTL_MAINSM_TIMER__Restart(TS_FCTL__TIMEOUT_T *pTimeout)
{
	// Call this to start or restart a timeout
	pTimeout->u32Elapsed_x10ms = 0U;
	pTimeout->u8IsStarted = 1;
}

void vFCU_FCTL_MAINSM_TIMER__Reset(TS_FCTL__TIMEOUT_T *pTimeout)
{
	pTimeout->u32Elapsed_x10ms = 0U;
	pTimeout->u8IsStarted = 0U;
}

void timeout_ensure_started(TS_FCTL__TIMEOUT_T *pTimeout)
{
	if ( ! pTimeout->u8IsStarted ) {
		// If we're not started, make sure we are and reset our elapsed time
		vFCU_FCTL_MAINSM_TIMER__Restart(pTimeout);
	} else {
		// We're already started; nothing to do
	}
}

Luint8 u8FCU_FCTL_MAINSM_TIMER__Is_Expired(TS_FCTL__TIMEOUT_T *timeout)
{
	return timeout->u32Elapsed_x10ms >= timeout->u32Duration_x10ms;
}

void vFCU_FCTL_MAINSM_TIMER__Update_x10ms(TS_FCTL__TIMEOUT_T *pTimeout)
{
	pTimeout->u32Elapsed_x10ms += 1U;
}



#endif //
#endif //

