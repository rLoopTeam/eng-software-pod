/**
 * @file		ATA6870__BALANCE.C
 * @brief		Balancing subsystem
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.012
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__BALANCE
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

//main structure
extern struct _str6870 sATA6870;



/***************************************************************************//**
 * @brief
 * Init any balancer systems
 * 
 * @st_funcMD5		A46B577F82793C959687DE3130CB78CD
 * @st_funcID		LCCM650R0.FILE.012.FUNC.001
 */
void vATA6870_BALANCE__Init(void)
{

	//init the variables
	sATA6870.sBalance.eState = BALANCE_STATE__IDLE;

}


/***************************************************************************//**
 * @brief
 * Stop the blanacing process and terminate any discharging resistors
 * 
 * @st_funcMD5		61065840D03858CD5B16762899AED266
 * @st_funcID		LCCM650R0.FILE.012.FUNC.003
 */
void vATA6870_BALANCE__Stop(void)
{
	Luint8 u8DeviceCounter;
	// for each ATA6870 device
	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8DeviceCounter++)
	{
		vATA6870_RES__TurnAllOff(u8DeviceCounter);
	}
}

/***************************************************************************//**
 * @brief
 * Check if the balancer is busy
 * 
 * @return			0 = Not busy\n
 *					1 = Busy
 * @st_funcMD5		6C722EE0914ABA34FBAEB989E8D06209
 * @st_funcID		LCCM650R0.FILE.012.FUNC.004
 */
Luint8 u8ATA6870_BALANCE__Is_Busy(void)
{
	Luint8 u8Return;

	if(sATA6870.sBalance.eState == BALANCE_STATE__BALANCE)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

	return u8Return;
}

/***************************************************************************//**
 * @brief
 * Process the balancer state machine. Call this from main loop fast as possible.
 * 
 * @st_funcMD5		D30B7E456ED8751A1AF6618C581E75E6
 * @st_funcID		LCCM650R0.FILE.012.FUNC.005
 */
void vATA6870_BALANCE__Process(void)
{

	switch(sATA6870.sBalance.eState)
	{
		case BALANCE_STATE__IDLE:
			//do nothing.
			break;
		case BALANCE_STATE__BALANCE:
			vATA6870_BALANCE__Start();
			break;
		case BALANCE_STATE__BALANCED:
			// Balancing has finished; turn off all discharge resistors.
			vATA6870_BALANCE__Stop();
			break;

	}//switch(sATA6870.sBalance.eState)

}

/***************************************************************************//**
 * @brief
 * Start the balancing process.
 *
 * @st_funcMD5		0003B1996E14215C56A9FFF33E5D0590
 * @st_funcID		LCCM650R0.FILE.012.FUNC.002
 */
void vATA6870_BALANCE__Start(void)
{
	Luint8 u8DeviceCounter;
	Luint8 u8CellCounter;
	Luint8 u8Balanced;
	u8Balanced = 1U;

	// for each ATA6870 device
	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8DeviceCounter++)
	{
		// for each 6P module connected to that device
		for(u8CellCounter = 0U; u8CellCounter < C_ATA6870__MAX_CELLS; u8CellCounter++)
		{
			//todo: '9999' for safety, replace with smarter value 
			// (minimum module voltage at init? or maybe set allowable deviation from target 
			// 	e.g. if( (module_voltage - min module voltage) >= .1V){} )
			if (sATA6870.f32Voltage[u8CellCounter] <= 9999 ) 
				{
					// cell has reached the setpoint, turn off discharge
					vATA6870_RES__TurnOff(u8DeviceCounter, u8CellCounter);
				}
				else
				{
					// cell needs to discharge to reach voltage setpoint
					u8Balanced = 0U;
					vATA6870_RES__TurnOn(u8DeviceCounter, u8CellCounter);
				}
		}
	}

	if(u8Balanced == 1U)
	{
		// maybe do this via return instead
		sATA6870.sBalance.eState = BALANCE_STATE__BALANCED;
	}
	else
	{
		// do nothing, state should remain BALANCE_STATE__BALANCE until balancing is complete
	}
}


//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_CRC
	#error
#endif

#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif

