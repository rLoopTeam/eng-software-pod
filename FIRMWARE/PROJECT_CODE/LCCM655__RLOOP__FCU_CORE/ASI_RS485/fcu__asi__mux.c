/**
 * @file		FCU__ASI__MUX.C
 * @brief		Multiplexer for the RS485 channels.
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
 * @addtogroup FCU__ASI__MUX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Init the multiplexer
 * 
 * @st_funcMD5		6B8A45FE3D8E2D389766DAF910F9E450
 * @st_funcID		LCCM655R0.FILE.070.FUNC.001
 */
void vFCU_ASI_MUX__Init(void)
{

	//init the MCP23S17
	vMCP23S17__Init(0U);

	vMCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x00U);
	vMCP23S17__Set_Port(0, MCP23S17_PORT__B, 0xFFU);

	//set all the pins output
	vMCP23S17__Set_PinDirection_Output(0, MCP23S17_PORT__A, 0xFF);
	vMCP23S17__Set_PinDirection_Output(0, MCP23S17_PORT__B, 0xFF);

	vMCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x00U);
	vMCP23S17__Set_Port(0, MCP23S17_PORT__B, 0xFFU);


}

/***************************************************************************//**
 * @brief
 * Process any mux tasks
 * 
 * @st_funcMD5		E69B0009BD94BC2496CA44C7DFDE0154
 * @st_funcID		LCCM655R0.FILE.070.FUNC.002
 */
void vFCU_ASI_MUX__Process(void)
{
	//nothing here.
}


/***************************************************************************//**
 * @brief
 * Selet the correct channel for the mux
 * 
 * @param[in]		u8ChannelIndex			The channel index
 * @st_funcMD5		C6A02E67BB44F8C4BFA001D5F649A8EE
 * @st_funcID		LCCM655R0.FILE.070.FUNC.003
 */
void vFCU_ASI_MUX__SelectChannel(Luint8 u8ChannelIndex)
{
	Luint8 u8MaskA;
	Luint8 u8MaskB;
	//there are two parts to this
	//PortA has the DEx
	//PortB has the nREx

	//To transmit we need DE = 1 and NRE = 0
	u8MaskA = 0x01U;
	u8MaskA <<= u8ChannelIndex;

	u8MaskB = u8MaskA;
	u8MaskB ^= 0xFFU;


	vMCP23S17__Set_Port(0, MCP23S17_PORT__A, u8MaskA);
	vMCP23S17__Set_Port(0, MCP23S17_PORT__B, u8MaskB);
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
