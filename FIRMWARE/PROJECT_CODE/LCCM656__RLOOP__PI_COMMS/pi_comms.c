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
	vPICOMMS_TX__Init();

}

void vPICOMMS_DoTelemetry()
{
	Luint16 u16Length;

	rI2CTX_beginFrame();
	rI2CTX_addParameter_int16((Luint16)0U, 20);
	u16Length = rI2CTX_endFrame();

	vRM4_SCI__TxByteArray(SCI_CHANNEL__2,u16Length,pu8I2CTx__Get_BufferPointer());
}

void vPICOMMS__Process(void)
{
	if (u32RM4_SCI__Is_TxReady(SCI_CHANNEL__2)){
		vPICOMMS_DoTelemetry();
	}

}




#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
