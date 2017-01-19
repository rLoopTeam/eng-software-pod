/**
 * @file		POWER_CORE__CHARGER.C
 * @brief		Implements the battery charger algo.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__CHARGER
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

extern struct _strPWRNODE sPWRNODE;



/***************************************************************************//**
 * @brief
 * Init the charger systems.
 * 
 * @st_funcMD5		725370926B9AB79FCE0E576F1D2647B5
 * @st_funcID		LCCM653R0.FILE.030.FUNC.001
 */
void vPWRNODE_CHG__Init(void)
{
	Luint16 u16CRC;
	Luint8 u8Test;

	//set to idle.
	sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__IDLE;

	//setup the charger relay
	vPWRNODE_CHG_RELAY__Init();

	//setup the current and voltage measurement
	vPWRNODE_CHG_IV__Init();

	//check the storage CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT,
										C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP,
										C_POWERCORE__EEPARAM_INDEX__CHARGER__CRC);

	if(u8Test == 1U)
	{
		//CRC was good
		sPWRNODE.sCharger.f32MaxHighestCell = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT);
		sPWRNODE.sCharger.f32MaxPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT);
		sPWRNODE.sCharger.f32MinPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT);
		sPWRNODE.sCharger.f32MaxCellTemp = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP);

	}
	else
	{

		//default the data
		vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT, 4.1F, 1U);
		vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT, 75.6F, 1U);
		vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT, 45.1F, 1U);
		vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP, 40.0F, C_LOCALDEF__LCCM188_IMMEDIATE_WRITE);


		sPWRNODE.sCharger.f32MaxHighestCell = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT);
		sPWRNODE.sCharger.f32MaxPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT);
		sPWRNODE.sCharger.f32MinPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT);
		sPWRNODE.sCharger.f32MaxCellTemp = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP);

		//update our CRC
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT,
												C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP,
												C_POWERCORE__EEPARAM_INDEX__CHARGER__CRC);

	}


}


/***************************************************************************//**
 * @brief
 * Process the charger
 * 
 * @note
 * http://confluence.rloop.org/display/SD/Charging
 *
 * @st_funcMD5		F5C060F07CD15EE910FD108F56897E5C
 * @st_funcID		LCCM653R0.FILE.030.FUNC.002
 */
void vPWRNODE_CHG__Process(void)
{
	Lfloat32 f32Temp;
	Luint8 u8Temp;

	//process charger relay control
	vPWRNODE_CHG_RELAY__Process();

	//process charger current and voltage measurement
	vPWRNODE_CHG_IV__Process();

	//handle the charger state machine.
	switch(sPWRNODE.sCharger.sAlgo.eState)
	{
		case CHG_STATE__IDLE:
			//we are in idle state, do nothing until we want to start charging.

			//need to ensure the charger is switched off.
			//do ths always
			vPWRNODE_CHG_RELAY__Off();
			break;

		case CHG_STATE__START:

			//Check the battery pack voltages. This is done autonomously
			//but should additionally be checked by operator.
			//If all cells are above 4.1V, pack is full, do not charge
			//If any cell is above 4.2V, throw an error, discharge that cell below 4.2V by balancing the pack, and do not charge
			//If any cell is below 2.5V, throw an error and do not charge

			f32Temp = f32PWRNODE_BMS__Cell_Get_HighestVoltage();
			if(f32Temp > sPWRNODE.sCharger.f32MaxHighestCell)
			{
				//run the balancer
				sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__START_BALANCE;
			}
			else
			{
				//check other pack conditions
				// 4.1 * 18 = 73.8
				f32Temp = f32PWRNODE_BMS__Get_PackVoltage();
				if(f32Temp > sPWRNODE.sCharger.f32MaxPackVoltage)
				{
					//our pack is charged, back to idle
					sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__ABORT;
				}
				else
				{
					//2.5 * 18 = 45.0
					if(f32Temp < sPWRNODE.sCharger.f32MinPackVoltage)
					{
						//too low to charge
						sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__ABORT;
					}
					else
					{
						//hmm, just right conditions to charge
						//move on and make sure we are allowed to charge
						sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__CHECK_PACK_TEMP;
					}

				}
			}
			break;

		case CHG_STATE__CHECK_PACK_TEMP:
			//Check that the battery temperatures are all below 40C.
			//If this is ever exceeded, stop charging. This is done autonomously,
			//but should additionally be checked by operator.
#if 0
			if(sPWRNODE.sTemp.u8NewTempAvail == 1U)
			{
#endif //0
				//check the temp ranges
				if(sPWRNODE.sTemp.f32HighestTemp < sPWRNODE.sCharger.f32MaxCellTemp)
				{
					//we are good to start charging
					sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__CLOSE_CONTACTOR_RELAY;
				}
				else
				{
					//we are above 40C, stop
					sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__ABORT;
				}

				//clear the flag, we are done
				sPWRNODE.sTemp.u8NewTempAvail = 0U;
#if 0
			}
			else
			{
				//stay in state, no new temp avail yet
			}
#endif //0
			break;

		case CHG_STATE__START_BALANCE:

			//5.b.If any cell is above 4.2V, throw an error,
			//discharge that cell below 4.2V by balancing the pack, and do not charge
			vPWRNODE_BMS__Balance_Start();

			//move to run the balancer
			sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__RUN_BALANCER;
			break;

		case CHG_STATE__RUN_BALANCER:

			//in this mode we are waiting until the balancing is done
			u8Temp = u8PWRNODE_BMS__Balance_IsBusy();
			if(u8Temp == 1U)
			{
				//we are still balancing
			}
			else
			{
				//done balancing, back to start
				sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__START;
			}
			break;


		case CHG_STATE__CLOSE_CONTACTOR_RELAY:

			//7. Close charging contactor

			//switch the realy on.
			vPWRNODE_CHG_RELAY__On();

			//check the charge current
			sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__CHECK_CHG_CURRENT;
			break;

		case CHG_STATE__CHECK_CHG_CURRENT:

			//Measure that charge current is flowing and not above 25A.
			//This is done autonomously, but should additionally be checked by operator.
			sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__CHECK_CELL_V_DURING_CHG;
			break;

		case CHG_STATE__CHECK_CELL_V_DURING_CHG:
			//Measure charger voltage on PCB, make sure voltages agree.voltage matches BMS voltage within 0.1V

			//can we even do that?
			sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__START;
			break;

		case CHG_STATE__MANUAL_BALANCING:
			//in this state the GS wants to maually balance.
			break;

		case CHG_STATE__ABORT:

			//immediate off
			vPWRNODE_CHG_RELAY__Off();

			//back to idle state
			sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__IDLE;
			break;

		default:
			//log error
			break;

	}//switch(sPWRNODE.sCharger.sAlgo.eState)

}


void vPWRNODE_GHG__Start_ManualBalance(void)
{
	if(sPWRNODE.sCharger.sAlgo.eState == CHG_STATE__IDLE)
	{
		sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__MANUAL_BALANCING;
	}
	else
	{
		//need to be idle
	}
}

void vPWRNODE_GHG__Stop_ManualBalance(void)
{
	sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__IDLE;
}

/***************************************************************************//**
 * @brief
 * start charging
 * 
 * @st_funcMD5		7B8FDF8B87B406209DF4C40EDC35480D
 * @st_funcID		LCCM653R0.FILE.030.FUNC.003
 */
void vPWRNODE_CHG__Start(void)
{
	Luint8 u8Test;

	//make sure we have a batt temp system up
	u8Test = u8PWR_BATTTEMP__Is_Avail();
	if(u8Test == 1U)
	{
		//move to start state
		sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__START;
	}
	else
	{
		//can't charge yet
		sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__ABORT;
	}




}

/***************************************************************************//**
 * @brief
 * Return 1 if the charger system is busy
 * 
 * @st_funcMD5		7357CD3525341E0653DA161837E24AE7
 * @st_funcID		LCCM653R0.FILE.030.FUNC.004
 */
Luint8 u8PWRNODE_CHG__Is_Busy(void)
{
	Luint8 u8Return;

	if(sPWRNODE.sCharger.sAlgo.eState == CHG_STATE__IDLE)
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
 * Immediate charge abort
 * 
 * @st_funcMD5		E442AC159B78066F7C5A8EB1416847BE
 * @st_funcID		LCCM653R0.FILE.030.FUNC.005
 */
void vPWRNODE_CHG__Abort(void)
{

	//priority is to open the relay
	vPWRNODE_CHG_RELAY__Off();

	//move to abort state, but we know our relay is open circuit
	sPWRNODE.sCharger.sAlgo.eState = CHG_STATE__ABORT;
}

#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER
#ifndef C_LOCALDEF__LCCM653__ENABLE_CHARGER
	#error
#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

