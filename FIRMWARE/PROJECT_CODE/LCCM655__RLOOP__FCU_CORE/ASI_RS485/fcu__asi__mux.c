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
 * @st_funcMD5		A6500A22CEB4BD0E15374C4FF64FF812
 * @st_funcID		LCCM655R0.FILE.070.FUNC.001
 */
void vFCU_ASI_MUX__Init(void)
{

	#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U

		//init the MCP23S17
		vSIL3_MCP23S17__Init(0U);


		//PortA is data enabled
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x00U);
		vSIL3_MCP23S17__Set_PortDirection_Output(0, MCP23S17_PORT__A);
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x00U);


		//Port B is nRE
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__B, 0xFFU);
		vSIL3_MCP23S17__Set_PortDirection_Output(0, MCP23S17_PORT__B);
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__B, 0xFFU);
	#endif //C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE


	//default us to channel 0
	vFCU_ASI_MUX__SelectChannel_DE(0, 1U);

#ifdef WIN32
	sFCU.sASI.u8MuxChannel = 0U;
#endif

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
 * @param[in]		u8DeValue				1 = DE on
 * @param[in]		u8ChannelIndex			The ASI channel index
 * @st_funcMD5		786987109CD90A5702222FC24E19D899
 * @st_funcID		LCCM655R0.FILE.070.FUNC.003
 */
void vFCU_ASI_MUX__SelectChannel_DE(Luint8 u8ChannelIndex, Luint8 u8DeValue)
{
	Luint8 u8MaskA;
	Luint8 u8MaskB;

	//there are two parts to this
	//PortA has the DEx
	//PortB has the nREx

	//To transmit we need DE = 1 and NRE = 0

	//hack for single channel system
	if(u8DeValue == 1)
	{

		//DE = 1
		//nRE = 1
		#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U
			vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x01);
			vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__B, 0x01);
		#endif //C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE

	}
	else
	{
		//DE = 0
		//nRE = 0
		#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U
			vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__A, 0x00);
			vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__B, 0x00);
		#endif //C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE
	}

/*
	u8MaskA = u8DeValue;
	u8MaskA <<= u8ChannelIndex;

	u8MaskB = u8MaskA;
	u8MaskB ^= 0xFFU;

	#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__A, u8MaskA);

		//for now always receive enable.
		vSIL3_MCP23S17__Set_Port(0, MCP23S17_PORT__B, u8MaskB);
	#endif //C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE
*/
#ifdef WIN32
	sFCU.sASI.u8MuxChannel = u8ChannelIndex;
#endif
}

#ifdef WIN32

/***************************************************************************//**
 * @brief
 * Get the current selected channel
 * 
 * @st_funcMD5		1EACC82B84035C7ED121A9C581DDABFF
 * @st_funcID		LCCM655R0.FILE.070.FUNC.004
 */
Luint8 u8FCU_ASI_MUX_WIN32__Get(void)
{
	return sFCU.sASI.u8MuxChannel;
}

#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
