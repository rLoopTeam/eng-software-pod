#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>
	#include <WIN32/DEBUG_PRINTF/debug_printf.h>

	//some placeholders
	#define SAFETOOL_BRANCH(stFuncID)

/*******************************************************************************
RLOOP - PI COMMUNICATIONS MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

			//arch
		#define C_LOCALDEF__LCCM656__USE_ON_RM4								(0U)
		#define C_LOCALDEF__LCCM656__USE_ON_WIN32							(1U)


			/** Testing Options */
		#define C_LOCALDEF__LCCM656__ENABLE_TEST_SPEC						(0U)

			/** Main include file */
		#include <LCCM656__RLOOP__PI_COMMS/pi_comms.h>
	#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

#endif //LOCALDEF
