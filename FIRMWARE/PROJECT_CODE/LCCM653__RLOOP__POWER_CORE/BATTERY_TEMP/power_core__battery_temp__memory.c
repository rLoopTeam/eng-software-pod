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



//the default battery packs
extern const Luint8 u8FwdPack__Default[];

/***************************************************************************//**
 * @brief
 * Init the memory system. Check the CRC's and load the pack data if needed.
 * 
 * @st_funcMD5		C7CA8EDC3B6B18471A4DDFF2BEBCFF18
 * @st_funcID		LCCM653R0.FILE.029.FUNC.001
 */
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
							((C_PWRCORE__NUM_TEMP_SNSR_PER_6P * C_PWRCORE__NUM_6P_MODULES) + 3U),
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



	//todo, check it loaded well and verify some sensors.


}


/***************************************************************************//**
 * @brief
 * Return the number of sensors
 * 
 * @st_funcMD5		61B6DDBC6B2331B8A91A22BAE7D575C4
 * @st_funcID		LCCM653R0.FILE.029.FUNC.002
 */
Luint16 u16PWRNODE_BATTTEMP_MEM__Get_NumSensors(void)
{
	return sPWRNODE.sTemp.u16NumSensors;
}


/***************************************************************************//**
 * @brief
 * Process any batt pack memory tasks.
 * 
 * @st_funcMD5		675C2F664A0027481072063B15FDCBE1
 * @st_funcID		LCCM653R0.FILE.029.FUNC.003
 */
void vPWRNODE_BATTTEMP_MEM__Process(void)
{


}


/***************************************************************************//**
 * @brief
 * Set the ROMID in memory
 * 
 * @param[in]		u32ROMID_Lower		## Desc ##
 * @param[in]		u32ROMID_Upper		## Desc ##
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		D7F42D40DB34F09AEA3ACFED2EED390E
 * @st_funcID		LCCM653R0.FILE.029.FUNC.004
 */
void vPWRNODE_BATTEMP_MEM__Set_ROMID(Luint16 u16Index, Luint32 u32ROMID_Upper, Luint32 u32ROMID_Lower)
{

	//set the ROMID

}

/***************************************************************************//**
 * @brief
 * Set the misc user data
 * 
 * @param[in]		u8Resolution		## Desc ##
 * @param[in]		u8BusID		## Desc ##
 * @param[in]		UserIndex		## Desc ##
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		A7987F0D7E4721A5389B8514028C9463
 * @st_funcID		LCCM653R0.FILE.029.FUNC.005
 */
void vPWRNODE_BATTEMP_MEM__Set_UserData(Luint16 u16Index, Luint16 UserIndex, Luint8 u8BusID, Luint8 u8Resolution)
{

	//set the data

}


/***************************************************************************//**
 * @brief
 * Save the current DS18B20 structure
 * 
 * @st_funcMD5		EE6440D1A5AD7B2C555B3DE1D83E8197
 * @st_funcID		LCCM653R0.FILE.029.FUNC.006
 */
Lint16 s16PWRNODE_BATTEMP_MEM__Save(void)
{

	//save off

	return 0;

}


/***************************************************************************//**
 * @brief
 * Load the sensor array data from memory
 * 
 * @st_funcMD5		88966F4CCD3C418E659974B230D4817D
 * @st_funcID		LCCM653R0.FILE.029.FUNC.007
 */
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

