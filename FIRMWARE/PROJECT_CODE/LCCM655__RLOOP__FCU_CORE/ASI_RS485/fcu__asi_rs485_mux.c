/**
 * @file		FCU__ASI_RS485_MUX.C
 * @brief		Multiplexer for the RS485
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
 * @addtogroup FCU__ASI_RS485_MUX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_ASI_MUX__Init(void)
{

	//init the MCP23S17
	vMCP23S17__Init(0U);

}

void vFCU_ASI_MUX__Process(void)
{

}

//selet the correct channel for the mux
void vFCU_ASI_MUX__SelectChannel(Luint8 u8ChannelIndex)
{



}



#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
