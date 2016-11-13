/**
 * @file		PI_COMMS.C
 * @brief		Main Pi Communictions module file.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM656R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS__CORE
 * @ingroup PI_COMMS
 * @{ */

#include "pi_comms.h"
#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

//main structure
struct _strPICOMMS sPC;


void vPICOMMS__Init(void)
{
	//init the transmitter system
	PICOMMS_TX_Init();
	PICOMMS_RX_Init();

}

//process the picomms layer
void vPICOMMS__Process(void)
{

}

#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
