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
 * @addtogroup FCU__ASI
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
Lint16 vFCU_ASI__Controller_Init(void)
{
	Lint16 i16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	// Common for all these init commands
	sCmd.u8SlaveAddress = 0;
	sCmd.fncCode = C_ASI__WRITE_SINGLE_REGISTER;

	// set command control source as serial network
	sCmd.paramAddress = C_FCU_ASI__COMMAND_SOURCE;
	sCmd.paramValue = 0;	// sets to serial
	if ((i16Return = vFCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}

	// set temperature thresholds
	sCmd.paramAddress = C_FCU_ASI__OVER_TEMP_THRESHOLD;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = vFCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}
	sCmd.paramAddress = C_FCU_ASI__FOLDBACK_STARING_TEMP;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = vFCU_ASI__SendCommand(&sCmd)) != 0)
	{
		// report an error
		return i16Return;
	}
	sCmd.paramAddress = C_FCU_ASI__FOLDBACK_END_TEMP;
	sCmd.paramValue = 0;	// TODO: what value?
	if ((i16Return = vFCU_ASI__SendCommand(&sCmd)) != 0)
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
Lint16 s16FCU_ASI__ReadMotorRpm(Luint8 u8ASIDevNum, Luint16 *u16Rpm)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__MOTOR_RPM;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Rpm;
	sCmd.eDestVarType = E_UINT16;
	s16Return=vFCU_ASI__SendCommand(&sCmd);
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
Lint16 s16FCU_ASI__ReadMotorCurrent(Luint8 u8ASIDevNum, Luint16 *u16Current)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__MOTOR_CURRENT;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Current;
	sCmd.eDestVarType = E_UINT16;
	s16Return=vFCU_ASI__SendCommand(&sCmd);
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
Lint16 s16FCU_ASI__ReadControllerTemperature(Luint8 u8ASIDevNum, Luint16 *u16Temp)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__CONT_TEMP;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Temp;
	sCmd.eDestVarType = E_UINT16;
	s16Return = vFCU_ASI__SendCommand(&sCmd);
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
Lint16 s16FCU_ASI__SaveSettings(Luint8 u8ASIDevNum)
{
	// cannot do this when controller is in the RUN state
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__WRITE_SINGLE_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__SAVE_SETTINGS;
	sCmd.paramValue = 32767;
	s16Return = vFCU_ASI__SendCommand(&sCmd);
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
Lint16 s16FCU_ASI__GetFaults(Luint8 u8ASIDevNum, Luint16 *u16Faults)
{
	Lint16 s16Return = 0;
	struct _strASICmd sCmd;

	memset(sCmd,0,sizeof(struct _strASICmd));
	sCmd.u8SlaveAddress = u8ASIDevNum;
	sCmd.fncCode = C_ASI__READ_INPUT_REGISTER;
	sCmd.paramAddress = C_FCU_ASI__FAULTS;
	sCmd.paramValue = 1;	// we just want to read one register
	sCmd.destVar = (void*)u16Faults;
	sCmd.eDestVarType = E_UINT16;

	s16Return = vFCU_ASI__SendCommand(&sCmd);

	// TODO: create a log message with all faults, defined in fcu_core_defines.h
	return s16Return;
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
