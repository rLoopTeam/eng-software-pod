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

//locals
static Luint8 u8ATA6870_BALANCE__Handle(Luint8 u8DeviceIndex, Luint8 u8CellCounter, Luint8 u8CellIndex);
static void vATA6870_BALANCE__Do(void);

/***************************************************************************//**
 * @brief
 * Init any balancer systems
 * 
 * @st_funcMD5		A46B577F82793C959687DE3130CB78CD
 * @st_funcID		LCCM650R0.FILE.012.FUNC.001
 */
void vATA6870_BALANCE__Init(void)
{
	Luint8 u8Counter;

	//init the variables
	sATA6870.sBalance.eState = BALANCE_STATE__IDLE;

	//allow a max of 3 cells, but this can be changed later on.
	sATA6870.sBalance.u8MaxBalanceCells = 3U;
	//0.025v, can change this later.
	sATA6870.sBalance.f32BalanceTolerance = 0.025F;

	//clear the resistor on values
	for(u8Counter = 0U; u8Counter < C_ATA6870__TOTAL_CELLS; u8Counter++)
	{
		sATA6870.sBalance.u8ResistorOn[u8Counter] = 0U;
	}

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
	sATA6870.u8AverageUpdated = 0U;
	sATA6870.sBalance.eState = BALANCE_STATE__WAIT_VOLTAGE_UPDATE;
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
	Luint8 u8Counter;

	// for each ATA6870 device
	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8DeviceCounter++)
	{
		vATA6870_RES__TurnAllOff(u8DeviceCounter);
	}

	//clear the resistor on values
	for(u8Counter = 0U; u8Counter < C_ATA6870__TOTAL_CELLS; u8Counter++)
	{
		sATA6870.sBalance.u8ResistorOn[u8Counter] = 0U;
	}

	//put the state back to idle
	sATA6870.sBalance.eState = BALANCE_STATE__IDLE;
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

	if(sATA6870.sBalance.eState == BALANCE_STATE__IDLE)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
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

	Luint8 u8Counter;


	//handle the balancer states
	switch(sATA6870.sBalance.eState)
	{
		case BALANCE_STATE__IDLE:
			//do nothing.
			break;

		case BALANCE_STATE__WAIT_VOLTAGE_UPDATE:

			//only move on when the pack voltage average is done
			if(sATA6870.u8AverageUpdated == 1U)
			{
				//change state
				sATA6870.sBalance.eState = BALANCE_STATE__START_BALANCING;

				//clear the last flag, it will be upsted in the averager.
				sATA6870.u8AverageUpdated = 0U;
			}
			else
			{
				//stay here until the next voltage scan.
			}
			break;

		case BALANCE_STATE__START_BALANCING:

			//do the balancing process.
			vATA6870_BALANCE__Do();

			//Move state
			sATA6870.sBalance.eState = BALANCE_STATE__CHECK_BALANCED;

			break;

		case BALANCE_STATE__CHECK_BALANCED:

			//default state
			sATA6870.sBalance.eState = BALANCE_STATE__BALANCED;

			for(u8Counter = 0; u8Counter < C_ATA6870__TOTAL_CELLS; u8Counter++)
			{

				//if we are still balancing, come back in a bit
				if(sATA6870.sBalance.u8ResistorOn[u8Counter] == 1U)
				{
					//wait for the next voltage update before re-balancing.
					sATA6870.sBalance.eState = BALANCE_STATE__WAIT_VOLTAGE_UPDATE;
				}
				else
				{
					//keep looking.
				}
			}
			break;

		case BALANCE_STATE__BALANCED:
			// Balancing has finished; turn off all discharge resistors.
			vATA6870_BALANCE__Stop();
			break;

	}//switch(sATA6870.sBalance.eState)

}

//return 1 if we are resistors on
Luint8 u8ATA6870_BALANCE__Handle(Luint8 u8DeviceIndex, Luint8 u8CellCounter, Luint8 u8CellIndex)
{
	Luint8 u8Temp;
	Luint8 u8Return;

	u8Return = 0U;

	//If one cell voltage is above average
	//Note: this could induce a bias.
	u8Temp = u8NUMERICAL_TOLERANCE__F32(sATA6870.f32Voltage[u8CellIndex], sATA6870.f32AverageCellVoltage, sATA6870.sBalance.f32BalanceTolerance);
	if(u8Temp == 0U)
	{
		//make sure we are actually greater
		if(sATA6870.f32Voltage[u8CellIndex] > sATA6870.f32AverageCellVoltage)
		{
			//inc the max cell count for this module
			u8Return = 1U;

			if(sATA6870.sBalance.u8ResistorOn[u8CellIndex] == 0U)
			{
				//turn on this resistor
				vATA6870_RES__TurnOn(u8DeviceIndex, u8CellCounter);

				//update the flag
				sATA6870.sBalance.u8ResistorOn[u8CellIndex] = 1U;
			}
			else
			{
				//res was already set on.
			}

		}
		else
		{
			//not within tolerance, but lower, so no need to do anything but check the prev resistor state
			if(sATA6870.sBalance.u8ResistorOn[u8CellIndex] == 1U)
			{
				// cell has reached the setpoint, turn off discharge
				vATA6870_RES__TurnOff(u8DeviceIndex, u8CellCounter);

				//update the flag
				sATA6870.sBalance.u8ResistorOn[u8CellIndex] = 0U;
			}

		}
	}
	else
	{
		//the cell and average is close, no point in balancing.
	}

	return u8Return;
}


void vATA6870_BALANCE__Do(void)
{

	Luint8 u8MaxCellCount;
	Luint8 u8DeviceCounter;
	Luint8 u8CellCounter;
	Lfloat32 f32Max;
	Luint8 u8CellIndex;
	Luint8 u8CellMax;
	Luint8 u8CellMaxCell;

	//clear the cell index
	u8CellIndex = 0U;


	// for each ATA6870 device
	for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8DeviceCounter++)
	{
		//clear the max count
		u8MaxCellCount = 0U;

		//find the highest voltage attached to the current device.
		//we would want to discharge this one first.
		u8CellMax = 0xFFU;
		f32Max = 0.0F;
		for(u8CellCounter = 0U; u8CellCounter < C_ATA6870__MAX_CELLS; u8CellCounter++)
		{
			//calc the current index
			u8CellIndex = (u8DeviceCounter * C_ATA6870__MAX_CELLS) + u8CellCounter;

			//simply choose the highest cell.
			if(sATA6870.f32Voltage[u8CellIndex] > f32Max)
			{

				//record it.
				f32Max = sATA6870.f32Voltage[u8CellIndex];
				u8CellMax = u8CellIndex;
				u8CellMaxCell = u8CellCounter;
			}
			else
			{
				//keep sorting
			}

		}//for(u8CellCounter = 0U; u8CellCounter < C_ATA6870__MAX_CELLS; u8CellCounter++)


		//balance the highest cell first
		if(u8CellMax != 0xFFU)
		{

			//we have the max voltage in this cell already, so discharge it
			//handle the balance decision and if needed update the count;
			u8MaxCellCount += u8ATA6870_BALANCE__Handle(u8DeviceCounter, u8CellMaxCell, u8CellMax);

		}
		else
		{
			//no max cell found (which is strange)
		}


		//fall on and check for any other cells attached to this device that might need balancing.

		// for each 6P module connected to that device
		for(u8CellCounter = 0U; u8CellCounter < C_ATA6870__MAX_CELLS; u8CellCounter++)
		{
			//calc the current index
			u8CellIndex = (u8DeviceCounter * C_ATA6870__MAX_CELLS) + u8CellCounter;

			//thermal limiting
			if(u8MaxCellCount < sATA6870.sBalance.u8MaxBalanceCells)
			{

				//handle the balance decision and if needed update the count;
				u8MaxCellCount += u8ATA6870_BALANCE__Handle(u8DeviceCounter, u8CellCounter, u8CellIndex);


			}//if(u8MaxCellCount < sATA6870.sBalance.u8MaxBalanceCells)
			else
			{
				//not able to do any more on this device

			}//else if(u8MaxCellCount < sATA6870.sBalance.u8MaxBalanceCells)

		}//for(u8CellCounter = 0U; u8CellCounter < C_ATA6870__MAX_CELLS; u8CellCounter++)


	}//for(u8DeviceCounter = 0U; u8DeviceCounter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8DeviceCounter++)


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

