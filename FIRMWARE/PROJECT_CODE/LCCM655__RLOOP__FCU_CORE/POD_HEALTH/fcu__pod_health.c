/*
 * fcu__pod_health.c
 *
 *  Created on: 26 Jan 2017
 *      Author: Lachlan
 */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U

extern struct _strFCU sFCU;

/** Quick and nasty here */
#define C_FCU__POD_HEALTH_INDEX__BATTERY_PACK_TEMP_RANGE				0x00000000
#define C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_TEMP_RANGE				0x00000001
#define C_FCU__POD_HEALTH_INDEX__BATTERY_VOLTAGE_RANGE					0x00000002
#define C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_VOLTAGE_RANGE				0x00000003
#define C_FCU__POD_HEALTH_INDEX__BATTERY_CURRENT_RANGE					0x00000004

#define C_FCU__POD_HEALTH_INDEX__HE_TEMP_RANGE							0x00000005
#define C_FCU__POD_HEALTH_INDEX__HE_CURRENT_RANGE						0x00000006
#define C_FCU__POD_HEALTH_INDEX__HE_VOLT_RANGE							0x00000007
#define C_FCU__POD_HEALTH_INDEX__HE_RPM_RANGE							0x00000008

#define C_FCU__POD_HEALTH_INDEX__PV_PRESS_RANGE							0x00000009
#define C_FCU__POD_HEALTH_INDEX__PV_TEMP_RANGE							0x0000000A

//http://confluence.rloop.org/display/SD/10.+Pod+Health+Check

Luint32 u32FCU_PODHEALTH__Check_InRange_F32(Lfloat32 f32Value, Lfloat32 f32Min, Lfloat32 f32Max);
void vFCU_PODHEALTH__Set_FlagInRage__F32(Lfloat32 f32Value, Lfloat32 f32Min, Lfloat32 f32Max, Luint32 u32FlagIndex);


//init the pod health system
void vFCU_PODHEALTH__Init(void)
{
	//init
	vFAULTTREE__Init(&sFCU.sPodHealth.sHealthFlags);

}

//process the health items
void vFCU_PODHEALTH__Process(void)
{
	Luint8 u8BatteryPack;
	Luint8 u8Counter;
/* 0	Battery Pack Average Max Temperature	0 to 50 °C	60 °C
 * 1	Max individual Battery cell temperature	0 to 50 °C	60 °C
 * 2	Battery Voltage	54V to 75.6V
 * 3	Cell Voltage Range	> 3.0 and < 4.2 V
 * 4	Battery Current	500A max
 *
 *
 */
	u8BatteryPack = 0U;
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32AverageTemp, 0.0F, 50.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_PACK_TEMP_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32HighestTemp, 0.0F, 50.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_TEMP_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32PackVoltage, 54.0F, 75.6F, C_FCU__POD_HEALTH_INDEX__BATTERY_VOLTAGE_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32HighestCellVoltage, 0.0F, 4.2F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_VOLTAGE_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32LowestCellVoltage, 3.0F, 5.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_VOLTAGE_RANGE);

	//battery current.
	//vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8Counter].f32LowestCellVoltage, 3.0F, 5.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CURRENT_RANGE);

	u8BatteryPack = 1U;
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32AverageTemp, 0.0F, 50.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_PACK_TEMP_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32HighestTemp, 0.0F, 50.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_TEMP_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32PackVoltage, 54.0F, 75.6F, C_FCU__POD_HEALTH_INDEX__BATTERY_VOLTAGE_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32HighestCellVoltage, 0.0F, 4.2F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_VOLTAGE_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32LowestCellVoltage, 3.0F, 5.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CELL_VOLTAGE_RANGE);

	//battery current.
	//vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8Counter].f32LowestCellVoltage, 3.0F, 5.0F, C_FCU__POD_HEALTH_INDEX__BATTERY_CURRENT_RANGE);

/*
	Hover Engines
	5	Hover Engine temperature	0 to 80°C 	100 °C
	6	Hover Engine current draw	100 A Max
	7	Hover Engine input voltage draw	50-72 VDC
	8	Hover Engine RPM	0 - 3000 RPM
*/

	//go through each HE
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
	{
		//todo, temp sensor:
		//C_FCU__POD_HEALTH_INDEX__HE_TEMP_RANGE

		//I,V,RPM
		vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sASI.sHolding[u8Counter].f32MotorCurrentA, 0.0F, 100.0F, C_FCU__POD_HEALTH_INDEX__HE_CURRENT_RANGE);

		//todo: volts
		//C_FCU__POD_HEALTH_INDEX__HE_VOLT_RANGE
		//vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sASI[u8Counter].sHolding.f32TempC,

		vFCU_PODHEALTH__Set_FlagInRage__F32((Lfloat32)sFCU.sASI.sHolding[u8Counter].u16RPM, 0.0F, 3000.0F, C_FCU__POD_HEALTH_INDEX__HE_RPM_RANGE);

	}

/*
	9	Pressure Vessel Pressure	0.7 - 1.1 atm	0.4 atm	Repressurization of the pod is triggered at 0.6 atm and stops at 0.9 atm
	10	Pressure Vessel Temperature	0 - 40 °C	60 °C
*/
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32PV_Press, 0.7F, 1.1F, C_FCU__POD_HEALTH_INDEX__PV_PRESS_RANGE);
	vFCU_PODHEALTH__Set_FlagInRage__F32(sFCU.sBMS[u8BatteryPack].f32PV_Temp, 0.0F, 40.0F, C_FCU__POD_HEALTH_INDEX__PV_TEMP_RANGE);


}

//set a fault flag if NOT in range, clears it if back in range
void vFCU_PODHEALTH__Set_FlagInRage__F32(Lfloat32 f32Value, Lfloat32 f32Min, Lfloat32 f32Max, Luint32 u32FlagIndex)
{
	Luint32 u32Test;

	//see if we are in range
	u32Test = u32FCU_PODHEALTH__Check_InRange_F32(f32Value, f32Min, f32Max);
	if(u32Test == 1U)
	{
		vFAULTTREE__Set_Flag(&sFCU.sPodHealth.sHealthFlags, u32FlagIndex);
	}
	else
	{
		vFAULTTREE__Clear_Flag(&sFCU.sPodHealth.sHealthFlags, u32FlagIndex);
	}
}

//checks if we are in range, return 1 if NOT in range
Luint32 u32FCU_PODHEALTH__Check_InRange_F32(Lfloat32 f32Value, Lfloat32 f32Min, Lfloat32 f32Max)
{
	Luint32 u32Return;

	if((f32Value > f32Min) && (f32Value < f32Max))
	{
		u32Return = 0x00000000U;
	}
	else
	{
		u32Return = 0x00000001U;
	}

	return u32Return;
}

#endif //C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH



