/**
 * @file		SIM_HYPERLOOP__ETHERNET.C
 * @brief		Eth Provider
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM666R0.FILE.005
 */
/**
 * @addtogroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP
 * @ingroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP__ETHERNET
 * @ingroup HYPERLOOP
 * @{ */

#include "../sim_hyperloop.h"
#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM666__ENABLE_ETHERNET == 1U

#include "D:/LOCKIE/DESIGN/RLOOP/FIRMWARE/PROJECT_CODE/LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h"

extern struct _strSIMHLOOP sSH;

//locals
void vSIMHLOOP_ETH__TxStatusPacket(void);

/***************************************************************************//**
 * @brief
 * Get the eth up on our hardware
 * 
 * @st_funcMD5		9DF4F6B55E2048BA94364A542C4807A4
 * @st_funcID		LCCM666R0.FILE.005.FUNC.001
 */
void vSIMHLOOP_ETH__Init(void)
{
	//assign.
	sSH.sEthernet.u8MACAddx[0] = 0x00;
	sSH.sEthernet.u8MACAddx[1] = 0x26;
	sSH.sEthernet.u8MACAddx[2] = 0x80;
	sSH.sEthernet.u8MACAddx[3] = 0x00;
	sSH.sEthernet.u8MACAddx[4] = 0x00;
	sSH.sEthernet.u8MACAddx[5] = 170;

	sSH.sEthernet.u8IPAddx[0] = 192;
	sSH.sEthernet.u8IPAddx[1] = 168;
	sSH.sEthernet.u8IPAddx[2] = 1;
	sSH.sEthernet.u8IPAddx[3] = 170;

	sSH.sEthernet.u8TimerFlag = 0U;

	//init the EMAC
	vXILNX_EMACLITE__Init(0, &sSH.sEthernet.u8MACAddx[0]);

	//init the ETH
	vETHERNET__Init(&sSH.sEthernet.u8MACAddx[0], &sSH.sEthernet.u8IPAddx[0]);

	//init safety UDP
	vSAFEUDP__Init();

}

/***************************************************************************//**
 * @brief
 * process the eth related tasks.
 * 
 * @st_funcMD5		4A1A51A802C0FA06537E279F3E0D57BA
 * @st_funcID		LCCM666R0.FILE.005.FUNC.002
 */
void vSIMHLOOP_ETH__Process(void)
{
	Luint8 u8Test;

	//process the ETH/LINK
	vXILNX_EMACLITE__Process(0);

	//only do if we have eth up
	u8Test = u8XILINX_EMACLITE_LINK__Is_LinkUp(0);
	if(u8Test == 1U)
	{
		//process eth layer
		vETHERNET__Process();

		//process safety UDP
		vSAFEUDP__Process();

		if(sSH.sEthernet.u8TimerFlag == 1U)
		{

			//transmit the status packet once the net us up
			vSIMHLOOP_ETH__TxStatusPacket();

			sSH.sEthernet.u8TimerFlag = 0U;
		}
		else
		{
			//timer not cooked yet
		}


	}
	else
	{
		//not ready yet
	}

}

//transmit a status update for the sim system
void vSIMHLOOP_ETH__TxStatusPacket(void)
{
	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	E_NET__PACKET_T ePacketType;
	pu8Buffer = 0;

	ePacketType = NET_PKT__XILINX_SIM__TX_PROGRESS_UPDATE;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__XILINX_SIM__TX_PROGRESS_UPDATE:
			u16Length = 4U + 1U;
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
			case NET_PKT__XILINX_SIM__TX_PROGRESS_UPDATE:

				//faults
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0xAA55AA55U);
				pu8Buffer += 4U;

				//spare 1:4
				pu8Buffer[0] = sSH.sControl.u8RunStatus;
				pu8Buffer += 1U;

				break;

			default:
				//do nothing
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
 * Handle a safetyUDP packet
 * 
 * @param[in]		eFault					Packet detected faults
 * @param[in]		u16DestPort				Host dest port
 * @param[in]		ePacketType				The packet type
 * @param[in]		u16PayloadLength		Total length of payload
 * @param[in]		*pu8Payload				Pointer to payload data
 * @st_funcMD5		63EEE34B5795CB4A47E20FEFB1305DE2
 * @st_funcID		LCCM666R0.FILE.005.FUNC.003
 */
void vSIMHLOOP_ETH__RxUDPSafe(Luint8 *pu8Payload, Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePacketType, Luint16 u16DestPort, SAFE_UDP__FAULTS_T eFault)
{
	Luint32 u32Block[4];
	Lfloat32 f32Block1;

	//make sure the dest port is for us
	if(u16DestPort == C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER)
	{

		//split into blocks
		u32Block[0] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		f32Block1 = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		switch((E_NET__PACKET_T)ePacketType)
		{

			case NET_PKT__XILINX_SIM__SIMULATION_CONTROL:

				//handle the run start/stop control
				if(u32Block[0] == 0U)
				{
					vSIMHLOOP_LOWLEVEL__Run_Off();
					sSH.sControl.u8RunStatus = 0U;
				}
				else
				{
					//update the G-Force
					vSIMHLOOP_LOWLEVEL__Set_Accel_GForce(f32Block1);

					//start running
					vSIMHLOOP_LOWLEVEL__Run_On();

					//update the user flag.
					sSH.sControl.u8RunStatus = 1U;
				}

				break;

			case NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL:
				vSIMHLOOP_LOWLEVEL__ManualLaser_Control(u32Block[0], u32Block[1]);
				break;

			default:
				//do nothing.
				break;

		} //switch(ePacketType)

	}
	else
	{
		//packet is not for us
	}

}


#endif //C_LOCALDEF__LCCM666__ENABLE_ETHERNET
#ifndef C_LOCALDEF__LCCM666__ENABLE_ETHERNET
	#error
#endif
#endif //C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE
/** @} */
/** @} */
/** @} */

