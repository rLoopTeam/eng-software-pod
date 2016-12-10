#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

void vFCU_LASERCONT__Init(void)
{

	//at the entry point here the N2HET should have created 3 programs for either
	//edge capture, or HTU.

}

void vFCU_LASERCONT__Process(void)
{

	//laser contrast will have a few states.
	//we can't really start timing until we are moving.
	//moving should be notified, and confirmed on the first marker.

}


//inerrupt from the RM4 notification system
void vFCU_LASERCONT__ISR(E_FCU__LASER_CONT_INDEX_T eLaser)
{

}


#endif
