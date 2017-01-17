/**
 * @file		LGU__SERIAL_COMMS.H
 * @brief		Serial Comms link to FCU
 * @author		Lachlan, Frank
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup LGU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup LGU__SERIAL_COMMS
 * @ingroup LGU
 * @{ */
 
 
#include "../lgu.h"

#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM667__LGU_SERIAL == 1U

void vLGU_SERCOMMS__Init(void)
{
	
}

void vLGU_SERCOMMS__Process(void)
{
	
}

#endif //C_LOCALDEF__LCCM667__LGU_SERIAL
#ifndef C_LOCALDEF__LCCM667__LGU_SERIAL
	#error
#endif
#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
