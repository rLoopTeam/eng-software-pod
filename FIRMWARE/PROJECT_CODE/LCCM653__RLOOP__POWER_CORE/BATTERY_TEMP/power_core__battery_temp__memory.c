/**
 * @file		POWER_CORE__BATTERY_TEMP__MEMORY.C
 * @brief		Read and write ROMID for temp sensors in the system.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.009
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BATTERY_TEMP__MEMORY
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U

extern struct _strPWRNODE sPWRNODE;

//locals
Lint16 s16PWRNODE_BATTEMP_MEM__Load(void);

//the default battery packs
extern const Luint8 u8FwdPack__Default[];

void vPWRNODE_BATTTEMP_MEM__Init(void)
{

	Luint16 u16CRC;
	Luint8 u8Test;
	Lint16 s16Return;

	//first up, lets load (or default) our top level params
	sPWRNODE.sTemp.u16NumSensors = 0U;

	//check the storage CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_POWERCORE__EEPARAM_INDEX__BATTTEMP__NUM_SENSORS,
										C_POWERCORE__EEPARAM_INDEX__BATTTEMP__PACK_CRC,
										C_POWERCORE__EEPARAM_INDEX__BATTTEMP__CRC);

	if(u8Test == 1U)
	{
		//CRC was good
		sPWRNODE.sTemp.u16NumSensors = u16EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__BATTTEMP__NUM_SENSORS);
		sPWRNODE.sTemp.u16PackMemCRC = u16EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__BATTTEMP__PACK_CRC);
	}
	else
	{

		//default the data
		vEEPARAM__WriteU16(	C_POWERCORE__EEPARAM_INDEX__BATTTEMP__NUM_SENSORS,
							(C_PWRCORE__NUM_TEMP_SNSR_PER_6P * C_PWRCORE__NUM_6P_MODULES),
							1U);
		//reload it
		sPWRNODE.sTemp.u16NumSensors = u16EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__BATTTEMP__NUM_SENSORS);

		//Pack CRC, just set to zero as it will fail later on
		sPWRNODE.sTemp.u16PackMemCRC = 0U;

		//update our CRC
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_POWERCORE__EEPARAM_INDEX__BATTTEMP__NUM_SENSORS,
												C_POWERCORE__EEPARAM_INDEX__BATTTEMP__PACK_CRC,
												C_POWERCORE__EEPARAM_INDEX__BATTTEMP__CRC);

	}

	//now load the memory
	s16Return = s16PWRNODE_BATTEMP_MEM__Load();

	//todo, check it loaded well and verify some sensors.


}

//return the number of sensors
Luint16 u16PWRNODE_BATTTEMP_MEM__Get_NumSensors(void)
{
	return sPWRNODE.sTemp.u16NumSensors;
}


void vPWRNODE_BATTTEMP_MEM__Process(void)
{


}


void vPWRNODE_BATTEMP_MEM__Set_ROMID(Luint16 u16Index, Luint32 u32ROMID_Upper, Luint32 u32ROMID_Lower)
{

	//set the ROMID

}

void vPWRNODE_BATTEMP_MEM__Set_UserData(Luint16 u16Index, Luint16 UserIndex, Luint8 u8BusID, Luint8 u8Resolution)
{

	//set the data

}


Lint16 s16PWRNODE_BATTEMP_MEM__Save(void)
{

	//save off

	return 0;

}

//load the sensor array data from memory
Lint16 s16PWRNODE_BATTEMP_MEM__Load(void)
{

	Luint16 u16MemorySize;
	Luint8 *pu8Array;
	Luint16 u16CRC;

	//step 1 is to collect data on the number of sensors.
	//sPWRNODE.sTemp.u8NumSensors


	//compute the size of the memory
	u16MemorySize = sPWRNODE.sTemp.u16NumSensors;

	//ROMID,etc
	u16MemorySize *= 12U;

	//do the CRC on the memory we currently have

	//using sector 1 of bank 7.
	pu8Array = (Luint8*)C_LCCM320__FLASH_SECTOR_1__START_ADDX;

	//do the CRC on it
	u16CRC = 0U;
	u16CRC = u16SWCRC__CRC(pu8Array, u16MemorySize);

	//compare the CRC to our stored CRC
	if(sPWRNODE.sTemp.u16PackMemCRC == u16CRC)
	{
		//CRC is good, load the data

		//need to make sure we have enough space in the DS18B20 array
		if(sPWRNODE.sTemp.u16NumSensors < C_LOCALDEF__LCCM644__MAX_DEVICES)
		{
			//we have room, do the load

			//get the device address
			pu8Array = (Luint8 *)u32DS18B20__Get_DeviceAddx();

			//load it
			vRM4_EEPROM__Read_U8Array(1U, 0x0000, pu8Array, u16MemorySize);

			//set the enumerated size.
		}
		else
		{
			//error, too many devies
		}

	}
	else
	{
		//CRC is bad need to default the data.

	}




	return 0;
}

//safetys
#ifndef C_LOCALDEF__LCCM644__MAX_DEVICES
	#error
#endif

#endif //C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

