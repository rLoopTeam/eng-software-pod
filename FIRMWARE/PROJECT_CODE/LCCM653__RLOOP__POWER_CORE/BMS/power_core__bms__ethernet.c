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
#if C_LOCALDEF__BMS_REVISION == 1U
	extern struct _str6870 sATA6870;
#elif C_LOCALDEF__BMS_REVISION == 2U
	extern TS_BQ76__MAIN sBQ76;
#else
	#error
#endif

/***************************************************************************//**
 * @brief
 * Init the Eth Portion
 * 
 * @st_funcMD5		3C23F10BFAD5C0FAB78B1C9FB1178A79
 * @st_funcID		LCCM653R0.FILE.032.FUNC.001
 */
void vPWR_BMS_ETH__Init(void)
{
	//do nothing.
}


/***************************************************************************//**
 * @brief
 * Tx an eth packet
 * 
 * @param[in]		ePacketType				The packet type.
 * @st_funcMD5		8F66B9F76D2E197949E7C8F228310ABE
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
			#if C_LOCALDEF__BMS_REVISION == 1U
				u16Length = 42U;
				u16Length +=  (C_LOCALDEF__LCCM650__NUM_DEVICES * C_ATA6870__MAX_CELLS * 4U);
				u16Length += C_ATA6870__MAX_BUS_DEVICES;
				u16Length += 12U;
			#elif C_LOCALDEF__BMS_REVISION == 2U
				u16Length = 28U;

				//volts
				u16Length +=  (C_BQ76__TOTAL_CELLS * 4U);
				//spares
				u16Length +=  (C_BQ76__TOTAL_CELLS * 4U);

				//dischg resistors
				u16Length += C_BQ76__TOTAL_CELLS;
				u16Length += 4;

				//battery spares
				u16Length += 4;

				//charger
				u16Length += 1;

				//temp sensor
				u16Length += 17;

				//press+temp = 8
				u16Length += 8U;
			#else
				#error
			#endif


			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{

#if C_LOCALDEF__BMS_REVISION == 1U
			case NET_PKT__PWR_BMS__TX_BMS_STATUS:

				//fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sFaults.sTopLevel.u32Flags[0]);
				pu8Buffer += 4U;

				//temp sensor state
				pu8Buffer[0] = (Luint8)sPWRNODE.sTemp.eState;
				pu8Buffer += 1U;

				//charger state
				#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
					pu8Buffer[0] = (Luint8)sPWRNODE.sCharger.sAlgo.eState;
					pu8Buffer += 1U;
				#else
					pu8Buffer[0] = 0U;
					pu8Buffer += 1U;
				#endif

				//num sensors
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, u16DS18B20__Get_NumEnum_Sensors());
				pu8Buffer += 2U;

				//highest individual temp
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32HighestTemp);
				pu8Buffer += 4U;

				//average temp
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32AverageTemp);
				pu8Buffer += 4U;

				//highest temp sensor
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sPWRNODE.sTemp.u16HighestSensorIndex);
				pu8Buffer += 2U;

				#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
					//pack volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Get_PackVoltage());
					pu8Buffer += 4U;

					//highest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_HighestVoltage());
					pu8Buffer += 4U;

					//lowest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_LowestVoltage());
					pu8Buffer += 4U;
				#else
					//pack volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;

					//highest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;

					//lowest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
				#endif

				//BMS boards Temp
				//todo
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
				pu8Buffer += 4U;

				//node press
				#if C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS == 1U
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODEPRESS__Get_Pressure_Bar());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, -1.0F);
					pu8Buffer += 4U;
				#endif

				//node temp
				#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODETEMP__Get_DegC());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, -1.0F);
					pu8Buffer += 4U;
				#endif

				#if C_LOCALDEF__BMS_REVISION == 1U
					//cell volts
					for(u8Device = 0; u8Device < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Device++)
					{
						for(u8Counter = 0; u8Counter < C_ATA6870__MAX_CELLS; u8Counter++)
						{
							//Cell voltage
							vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sATA6870.f32Voltage[(u8Device * C_ATA6870__MAX_CELLS) + u8Counter]);
							pu8Buffer += 4U;
						}
					}

					//BMS ID
					for(u8Counter = 0U; u8Counter < C_ATA6870__MAX_BUS_DEVICES; u8Counter++)
					{
						pu8Buffer[0] = sATA6870.u8RevID[u8Counter];
						pu8Buffer += 1U;
					}
				#elif C_LOCALDEF__BMS_REVISION == 2U
					//cell volts
					for(u8Device = 0; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
					{
						for(u8Counter = 0; u8Counter < C_BQ76__MAX_CELLS_PER_DEVICE; u8Counter++)
						{
							//Cell voltage
							vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
							pu8Buffer += 4U;
						}
					}

					//BMS ID
					for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Counter++)
					{
						pu8Buffer[0] = 1U;
						pu8Buffer += 1U;
					}
				#else
					#error
				#endif

				//count of times the voltage was updated.
				#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_VoltsUpdateCount());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
				#endif

				//Number of times we've scaned the temperature sensors
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sTemp.u32TempScanCount);
				pu8Buffer += 4U;

				//Current through the battery pack
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sHASS600.f32HASS_CurrentReading);
				pu8Buffer += 4U;

				break;

#elif C_LOCALDEF__BMS_REVISION == 2U
			case NET_PKT__PWR_BMS__TX_BMS_STATUS:

				//fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sFaults.sTopLevel.u32Flags[0]);
				pu8Buffer += 4U;

				//Device fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_DeviceFlags(0U));
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_DeviceFlags(1U));
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_DeviceFlags(2U));
				pu8Buffer += 4U;

				#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
					//pack volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Get_PackVoltage());
					pu8Buffer += 4U;
					//highest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_HighestVoltage());
					pu8Buffer += 4U;
					//lowest volts
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_BMS__Cell_Get_LowestVoltage());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
				#endif


				//cell volts
				for(u8Counter = 0; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
				{
					//Cell voltage
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32BQ76__Get_CellVoltage(u8Counter));
					pu8Buffer += 4U;

				}

				//cell spares
				for(u8Counter = 0; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
				{
					//Cell voltage
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;

				}

				//discharge resistors
				for(u8Counter = 0; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
				{
					pu8Buffer[0] = sBQ76.sBalance.u8Resistor[u8Counter];
					pu8Buffer += 1U;
				}

				//count of times the voltage was updated.
				#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32PWRNODE_BMS__Get_VoltsUpdateCount());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
				#endif

				//battery spares
				pu8Buffer += 4U;


				//charger state
				#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
					pu8Buffer[0] = (Luint8)sPWRNODE.sCharger.sAlgo.eState;
					pu8Buffer += 1U;
				#else
					pu8Buffer[0] = 0U;
					pu8Buffer += 1U;
				#endif



				//temp sensor state
				pu8Buffer[0] = (Luint8)sPWRNODE.sTemp.eState;
				pu8Buffer += 1U;


				//num sensors
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, u16DS18B20__Get_NumEnum_Sensors());
				pu8Buffer += 2U;

				//highest individual temp
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32HighestTemp);
				pu8Buffer += 4U;

				//average temp
				vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sTemp.f32AverageTemp);
				pu8Buffer += 4U;

				//highest temp sensor
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sPWRNODE.sTemp.u16HighestSensorIndex);
				pu8Buffer += 2U;

				//Number of times we've scaned the temperature sensors
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sPWRNODE.sTemp.u32TempScanCount);
				pu8Buffer += 4U;


				//node press
				#if C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS == 1U
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODEPRESS__Get_Pressure_Bar());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
				#endif

				//node temp
				#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32PWRNODE_NODETEMP__Get_DegC());
					pu8Buffer += 4U;
				#else
					vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
					pu8Buffer += 4U;
				#endif




				//Current through the battery pack
				//vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, sPWRNODE.sHASS600.f32HASS_CurrentReading);
				//pu8Buffer += 4U;

				break;

#else
	#error
#endif

			default:
				//fall on
				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, sPWRNODE.u16EthPort, sPWRNODE.u16EthPort);

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
