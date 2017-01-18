/**
 * @file		POWER_CORE__BATTERY_TEMP__ETHERNET.C
 * @brief		Batt temp sensor ethernet subsystem
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
 * @addtogroup POWER_NODE__BATTERY_TEMP__ETHERNET
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Transmit a general eth packet
 * 
 * @param[in]		ePacketType			Eth Type
 * @st_funcMD5		285D08C3FCC2B0B0F87EB0E5B7FAFB32
 * @st_funcID		LCCM653R0.FILE.028.FUNC.001
 */
void vPWRNODE_BAATTEMP_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint16 u16Device;
	Luint16 u16Temp;

	pu8Buffer = 0;

	u16Temp = u16PWRNODE_BATTTEMP_MEM__Get_NumSensors();

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS:
			//length will be updated a bit later.
			u16Length = 4U + (u16Temp * 4U);
			break;

		case NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA:
			u16Length = 4U + (u16Temp * 4U);
			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS:

				//number of temp sensors
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, u16Temp);
				pu8Buffer += 2U;

				//spare
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, 0U);
				pu8Buffer += 2U;

				//1080 bytes here!
				for(u16Device = 0U; u16Device < u16Temp; u16Device++)
				{

					//temp in deg C
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32DS18B20__Get_Temperature_DegC(u16Device));
					pu8Buffer += 4U;


				}//for(u16Device = 0U; u16Device < u16Temp; u16Device++)
				break;

			case NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA:
				//send the sensor location data

				//number of temp sensors
				u16Temp = u16PWRNODE_BATTTEMP_MEM__Get_NumSensors();
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, u16Temp);
				pu8Buffer += 2U;

				//spare
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, 0U);
				pu8Buffer += 2U;

				for(u16Device = 0U; u16Device < u16Temp; u16Device++)
				{

					//user location
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, u162DS18B20__Get_UserIndex(u16Device));
					pu8Buffer += 2U;

					//resolution
					pu8Buffer[0] = u82DS18B20__Get_Resolution(u16Device);
					pu8Buffer += 1U;

					//bus index
					pu8Buffer[0] = u82DS18B20__Get_BusIndex(u16Device);
					pu8Buffer += 1U;


				}//for(u16Device = 0U; u16Device < u16Temp; u16Device++)

			break;


			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


/***************************************************************************//**
 * @brief
 * Transmit a ROMID packet
 * 
 * @param[in]		u32Index			Enumeration Index
 * @st_funcMD5		ED610968B92B427A06555891B9679CDB
 * @st_funcID		LCCM653R0.FILE.028.FUNC.002
 */
void vPWRNODE_BAATTEMP_ETH__Transmit_ROMID(Luint32 u32Index)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint16 u16Device;
	Luint16 u16Temp;

	pu8Buffer = 0;

	//setup length based on packet.
	u16Length = 12U;


	//pre-comit
	s16Return = s16SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)NET_PKT__PWR_TEMP__TX_ROMID_INDEX, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//Rensed the index
		vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32Index);
		pu8Buffer += 4U;

		//send the ID
		vDS18B20__Get_ROMID(u32Index, pu8Buffer);
		pu8Buffer += 8U;


		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
#endif //
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
