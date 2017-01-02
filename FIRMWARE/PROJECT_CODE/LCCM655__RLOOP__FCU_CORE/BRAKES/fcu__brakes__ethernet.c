/**
 * @file		FCU__BRAKES__ETHERNET.C
 * @brief		Eth diagnostics for brakes system
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
 * @addtogroup FCU__BRAKES__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the stepper interface
 *
 * @st_funcMD5		789F80370F1D1EEB00F64DD61C585732
 * @st_funcID		LCCM655R0.FILE.025.FUNC.001
 */
void vFCU_BRAKES_STEP__Init(void)
{
	Luint8 u8Test;

	//init any IO as neede

	//setup the stepper drive system
	vSTEPDRIVE__Init();

	//reload the memory
	//check the CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
										C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);
	if(u8Test == 1U)
	{
		//valid
		sFCU.sBrakes[0].sMove.s32LinearVeloc = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC);
		sFCU.sBrakes[0].sMove.s32LinearAccel = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL);
		sFCU.sBrakes[1].sMove.s32LinearVeloc = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC);
		sFCU.sBrakes[1].sMove.s32LinearAccel = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL);

	}//if(u8Test == 1U)
	else
	{
		//CRC is invalid
		vEEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC, 100U, 1U);
		vEEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL, 100U, 1U);
		vEEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC, 100U, 1U);
		vEEPARAM__WriteS32(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL, 100U, 0U);

		//redo the CRC;
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL,
												C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP_CRC);

		//1. Reload the structures.
		sFCU.sBrakes[0].sMove.s32LinearVeloc = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_VELOC);
		sFCU.sBrakes[0].sMove.s32LinearAccel = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP0_ACCEL);
		sFCU.sBrakes[1].sMove.s32LinearVeloc = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_VELOC);
		sFCU.sBrakes[1].sMove.s32LinearAccel = s32EEPARAM__Read(C_LOCALDEF__LCCM655__EEPROM_OFFSET__STEP1_ACCEL);

		//set the flags for a general fault and cal data reload fault.
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[0].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[0].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[1].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__00);
		vFAULTTREE__Set_Flag(&sFCU.sBrakes[1].sFaultFlags, C_LCCM655__BRAKES__FAULT_INDEX__03);


	}//else if(u8Test == 1U)

}

/***************************************************************************//**
 * @brief
 * Process any brake commands
 *
 * @st_funcMD5		792382B2C7B93024D59EDDDE0DBD345D
 * @st_funcID		LCCM655R0.FILE.025.FUNC.002
 */
void vFCU_BRAKES_STEP__Process(void)
{


}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET

#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

