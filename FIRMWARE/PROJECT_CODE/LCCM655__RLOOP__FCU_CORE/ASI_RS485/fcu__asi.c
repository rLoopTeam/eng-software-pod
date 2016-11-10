/**
 * @file		FCU__ASI.C
 * @brief		Command interface to ASI controller
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
 * @addtogroup FCU__ASI_RS485
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Transmit command structure to ASI
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate with
 * @param[in/out]	sCmdParams		Command structure with params and values
 * @return			-1 = error
 * 					0 = success
 */
Lint16 vFCU_ASI__Tx_Cmd(Luint8 u8ASIDevNum, struct _strASICmd *sCmdParams)
{
	Lint16 i16Return = 0;

	// need ASI MODBus protocol to send command

	return i16Return;
}

/***************************************************************************//**
 * @brief
 * Initialize ASI controller parameters
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate with
 * @return			-1 = error
 * 					0 = success
 */
Lint16 vFCU_ASI__Cmd_Init(Luint8 u8ASIDevNum)
{
	Lint16 i16Return = 0;
	struct _strASICmd sCmdParam;

	// set command control source as serial network
	sCmdParam.cmdAddx = C_FCU_ASI__COMMAND_SOURCE;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_WRITE;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return i16Return;
	}

	// set temperature thresholds
	sCmdParam.cmdAddx = C_FCU_ASI__OVER_TEMP_THRESHOLD;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_WRITE;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return i16Return;
	}
	sCmdParam.cmdAddx = C_FCU_ASI__FOLDBACK_STARING_TEMP;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_WRITE;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return i16Return;
	}
	sCmdParam.cmdAddx = C_FCU_ASI__FOLDBACK_END_TEMP;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_WRITE;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return i16Return;
	}
}

/***************************************************************************//**
 * @brief
 * Set RPM for ASI controller
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate with
 * @param[in]		u32Rpm			RPM value to set
 * @return			-1 = error
 * 					0 = success
 */
Lint16 vFCU_ASI__SetRPM(Luint8 u8ASIDevNum, Luint32 u32Rpm)
{
	Lint16 i16Return = 0;

	return i16Return;
}

/***************************************************************************//**
 * @brief
 * Save RPM params on ASI controller
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate with
 * @return			-1 = error
 * 					0 = success
 */
Lint16 vFCU_ASI__SaveParams(Luint8 u8ASIDevNum)
{
	Lint16 i16Return = 0;
	struct _strASICmd sCmdParam;

	sCmdParam.cmdAddx = C_FCU_ASI__WRITE_PARAMS;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_WRITE;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return i16Return;
	}

	return i16Return;
}

/***************************************************************************//**
 * @brief
 * Get faults from ASI controller
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate with
 * @return			-1 = error
 * 					0 = success
 */
Luint16 vFCU_ASI__GetFaults(Luint8 u8ASIDevNum)
{
	Luint16 i16Return = 0;
	struct _strASICmd sCmdParam;

	sCmdParam.cmdAddx = C_FCU_ASI__FAULTS;
	sCmdParam.cmdValue = 0;
	sCmdParam.bRW = C_FCU_ASI__PARAM_READ;
	i16Return = vFCU_ASI__Tx_Cmd(u8ASIDevNum, &sCmdParam);
	if (i16Return != 0)
	{
		// report an error
		return (Luint16)i16Return;
	}

	return sCmdParam.cmdValue;
}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
