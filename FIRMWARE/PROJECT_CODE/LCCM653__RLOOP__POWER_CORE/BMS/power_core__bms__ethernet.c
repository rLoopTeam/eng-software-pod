/**
 * @file		POWER_CORE__BMS__ETHERNET.C
 * @brief		Ethernet UDP diagnostics for battery management system
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
 * @addtogroup POWER_NODE__BMS__ETHERNET
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

extern struct _strPWRNODE sPWRNODE;

//needed right now.
extern struct _str6870 sATA6870;

/***************************************************************************//**
 * @brief
 * Init the Eth Portion
 * 
 * @st_funcMD5		3C23F10BFAD5C0FAB78B1C9FB1178A79
 * @st_funcID		LCCM653R0.FILE.032.FUNC.001
 */
void vPWR_BMS_ETH__Init(void)
{

}


/***************************************************************************//**
 * @brief
 * Tx an eth packet
 * 
 * @param[in]		ePacketType				The packet type.
 * @st_funcMD5		85992BC7984E5F9DF42F02F1180C432E
 * @st_funcID		LCCM653R0.FILE.032.FUNC.002
 */
void vPWR_BMS_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__PWR_BMS__TX_BMS_STATUS:
			u16Length = 42U;
			u16Length +=  (C_LOCALDEF__LCCM650__NUM_DEVICES * C_ATA6870__MAX_CELLS * 4U);
			u16Length += C_ATA6870__MAX_BUS_DEVICES;
			u16Length += 8U;
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
			case NET_PKT__PWR_BMS__TX_BMS_STATUS:

				//fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sFaults.sTopLevel.u32Flags[0]);
				pu8Buffer += 4U;

				//temp sensor state
				pu8Buffer[0] = (Luint8)sPWRNODE.sTemp.eState;
				pu8Buffer += 1U;

				//charger state
				pu8Buffer[0] = (Luint8)sPWRNODE.sCharger.sAlgo.eState;
				pu8Buffer += 1U;

				//num sensors
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, u16DS18B20__Get_NumEnum_Sensors());
				pu8Buffer += 2U;

				//highest individual temp
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32HighestTemp);
				pu8Buffer += 4U;

				//average temp
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32AverageTemp);
				pu8Buffer += 4U;

				//highest temp sensor
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sPWRNODE.sTemp.u16HighestSensorIndex);
				pu8Buffer += 2U;

				//pack volts
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Get_PackVoltage());
				pu8Buffer += 4U;

				//highest volts
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_HighestVoltage());
				pu8Buffer += 4U;

				//lowest volts
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_LowestVoltage());
				pu8Buffer += 4U;

				//BMS boards Temp
				//todo
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, 0.0F);
				pu8Buffer += 4U;

				//node press
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODEPRESS__Get_Pressure_Bar());
				pu8Buffer += 4U;

				//node temp
				vNUMERICAL_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODETEMP__Get_DegC());
				pu8Buffer += 4U;

				//cell volts
				for(u8Device = 0; u8Device < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Device++)
				{
					for(u8Counter = 0; u8Counter < C_ATA6870__MAX_CELLS; u8Counter++)
					{
						//Cell voltage
						vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sATA6870.f32Voltage[(u8Device * C_ATA6870__MAX_CELLS) + u8Counter]);
						pu8Buffer += 4U;
					}
				}

				//BMS ID
				for(u8Counter = 0U; u8Counter < C_ATA6870__MAX_BUS_DEVICES; u8Counter++)
				{
					pu8Buffer[0] = sATA6870.u8RevID[u8Counter];
					pu8Buffer += 1U;
				}

				//count of times the voltage was updated.
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_VoltsUpdateCount());
				pu8Buffer += 4U;

				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sTemp.u32TempScanCount);
				pu8Buffer += 4U;


				break;

			default:
				//fall on
				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, sPWRNODE.u16EthPort, sPWRNODE.u16EthPort);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

#endif //#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_ETHERNET
	#error
#endif
/** @} */
/** @} */
/** @} */
