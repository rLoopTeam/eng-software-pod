/**
 * @file		POWER_CORE__BMS.C
 * @brief		Battery Management Interface Layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.008
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BMS
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the battery management system
 * 
 * @st_funcMD5		1CA544E68E3E338A54F4E1ADAFB54227
 * @st_funcID		LCCM653R0.FILE.008.FUNC.001
 */
void vPWRNODE_BMS__Init(void)
{

#ifndef WIN32
	//init the ATA6870 driver
	vATA6870__Init();
#endif

	//setup any ethernet systems.
	vPWR_BMS_ETH__Init();

}

/***************************************************************************//**
 * @brief
 * Process any battery management system items
 * 
 * @st_funcMD5		15B2FAA1BAD482B0EC323B1CBE361248
 * @st_funcID		LCCM653R0.FILE.008.FUNC.002
 */
void vPWRNODE_BMS__Process(void)
{
#ifndef WIN32
	//process any ATA6870 tasks
	vATA6870__Process();
#endif
}

/***************************************************************************//**
 * @brief
 * Get the highest cell voltage
 * 
 * @st_funcMD5		CCDA9D0AA2A185CC2B0AED32C6C65C05
 * @st_funcID		LCCM653R0.FILE.008.FUNC.003
 */
Lfloat32 f32PWRNODE_BMS__Cell_Get_HighestVoltage(void)
{
	return f32ATA6870_CELL__Get_HighestVoltage();
}

/***************************************************************************//**
 * @brief
 * Returns the last computed lowest cell voltage.
 * 
 * @st_funcMD5		71C954368FC27625363D95A446DA7B32
 * @st_funcID		LCCM653R0.FILE.008.FUNC.007
 */
Lfloat32 f32PWRNODE_BMS__Cell_Get_LowestVoltage(void)
{
	return f32ATA6870_CELL__Get_LowestVoltage();
}

/***************************************************************************//**
 * @brief
 * Returns the entire pack voltage
 * 
 * @st_funcMD5		1FEB2A9DBECB7ED0651F480855A300D6
 * @st_funcID		LCCM653R0.FILE.008.FUNC.004
 */
Lfloat32 f32PWRNODE_BMS__Get_PackVoltage(void)
{
	return f32ATA6870_CELL__Get_PackVoltage();
}


/***************************************************************************//**
 * @brief
 * Start the balance process.
 * 
 * @st_funcMD5		A4A94DAE9A680CCCF72DBE546F52ED5F
 * @st_funcID		LCCM653R0.FILE.008.FUNC.005
 */
void vPWRNODE_BMS__Balance_Start(void)
{
	vATA6870_BALANCE__Start();
}


/***************************************************************************//**
 * @brief
 * Is the balancer busy?
 * 
 * @st_funcMD5		4B308ED45EA0D643CDA7B851220C95A7
 * @st_funcID		LCCM653R0.FILE.008.FUNC.006
 */
Luint8 u8PWRNODE_BMS__Balance_IsBusy(void)
{
	return u8ATA6870_BALANCE__Is_Busy();
}


//stop balance immediate
void vPWRNODE_BMS__Balance_Stop(void)
{
	vATA6870_BALANCE__Stop();
}

void vPWRNODE_BMS__Balance_Manual(Luint8 u8CellIndex, Luint8 u8Enable)
{
	vATA6870_BALANCE__Manual(u8CellIndex, u8Enable);
}

Luint32 u32PWRNODE_BMS__Get_VoltsUpdateCount(void)
{
	return u32ATA6870__Get_VoltsUpdateCount();
}


#endif //C_LOCALDEF__LCCM653__ENABLE_BMS

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

