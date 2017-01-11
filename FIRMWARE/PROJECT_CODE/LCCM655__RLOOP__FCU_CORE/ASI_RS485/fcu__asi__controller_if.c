/**
 * @file		FCU__ASI__CONTROLLER.C
 * @brief		Command interface to ASI controller
 *
 * @note		This is the actual part that talks to the controller
 *
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
 * @addtogroup FCU__ASI__CONTROLLER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

//the structure
extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * Initialize ASI controller parameters
 * Broadcast to all devices
 *
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__Init(void)
{
	Lint16 i16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8 *)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	// Common for all these init commands
	sCmd.u8SlaveAddress = 0;
	sCmd.fncCode = C_ASI__WRITE_SINGLE_REGISTER;

	// set command control source as serial network
	sCmd.paramAddress = C_FCU_ASI__COMMAND_SOURCE;
	sCmd.paramValue = 0;	// sets to serial
	if ((i16Return = s16FCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}

	// set temperature thresholds
	sCmd.paramAddress = C_FCU_ASI__OVER_TEMP_THRESHOLD;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = s16FCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}
	sCmd.paramAddress = C_FCU_ASI__FOLDBACK_STARING_TEMP;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = s16FCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}
	sCmd.paramAddress = C_FCU_ASI__FOLDBACK_END_TEMP;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = s16FCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}

	// set motor rating?
	return i16Return;
}

/***************************************************************************//**
 * @brief
 * Read motor rpm
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate (1-8)
 * @param[out]		u16Rpm			Parameter to store rpm
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__ReadMotorRpm(Luint8 u8ASIDevNum, Luint16 *u16Rpm)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8*)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__MOTOR_RPM;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Rpm;
	sCmd.eDestVarType = E_UINT16;
	s16Return=s16FCU_ASI__SendCommand(&sCmd);
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Read motor rpm
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate (1-8)
 * @param[out]		u16Current		Parameter to store rpm
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__ReadMotorCurrent(Luint8 u8ASIDevNum, Luint16 *u16Current)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8*)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__MOTOR_CURRENT;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Current;
	sCmd.eDestVarType = E_UINT16;
	s16Return=s16FCU_ASI__SendCommand(&sCmd);
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Read controller's base plate temperature
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate (1-8)
 * @param[out]		u16Temp			Parameter to store temperature in Celsius
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__ReadControllerTemperature(Luint8 u8ASIDevNum, Luint16 *u16Temp)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8*)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__CONT_TEMP;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Temp;
	sCmd.eDestVarType = E_UINT16;
	s16Return = s16FCU_ASI__SendCommand(&sCmd);
	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Save ASI controller settings
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate (1-8)
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__SaveSettings(Luint8 u8ASIDevNum)
{
	// cannot do this when controller is in the RUN state
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8*)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__WRITE_SINGLE_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__SAVE_SETTINGS;
	sCmd.paramValue = 32767;
	s16Return = s16FCU_ASI__SendCommand(&sCmd);
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Get faults from ASI controller
 *
 * @param[in]		u8ASIDevNum		ASI controler device to communicate (1-8)
 * @param[out]		u16Faults		Parameter to store faults bit array
 * @return			-1 = error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__GetFaults(Luint8 u8ASIDevNum, Luint16 *u16Faults)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	vFCU_ASI__MemSet((Luint8*)&sCmd, 0, (Luint32)sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__FAULTS;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Faults;
	sCmd.eDestVarType = E_UINT16;

	s16Return = s16FCU_ASI__SendCommand(&sCmd);

	// TODO: create a log message with all faults, defined in fcu_core_defines.h
	return s16Return;
}



/***************************************************************************//**
 * @brief
 * Process reply from ASI device
 *
 * @param[in]	pCmd		Command being processed in command queue
 * @return			-1 = crc error
 * 					0 = success
 */
Lint16 s16FCU_ASI_CTRL__ProcessReply(struct _strASICmd *pCmd)
{
	Lint16 s16Return;

	if (pCmd)
	{
		// check CRC
		s16Return = s16FCU_ASI_CRC__CheckCRC(pCmd->response, C_ASI__RW_FRAME_SIZE);
		if(s16Return < 0)
		{
			pCmd->eErrorType = E_CRC_CHECK_FAILED;
			return -1;
		}
		else
		{
			// check return slave address vs sent slave address, they should match
			if (pCmd->framedCmd[0] != pCmd->response[0])
			{
				pCmd->eErrorType = E_SLAVE_MISMATCH;
				return -1;
			}
			// check function code in response, if it's error reply, process error
			if (pCmd->response[1] & 0x80)
			{
				pCmd->eErrorType = E_ERROR_RESPONSE;
				return -1;
			}

			vFCU_ASI__SetVar(pCmd);
		}


	}

	return 0;
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
