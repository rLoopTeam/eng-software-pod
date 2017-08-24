/**
 * @file		FCU__ACCEL__ETHERNET.C
 * @brief		Ethernet UDP diagnostics for the accel system
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__ACCEL__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the eth portion
 * 
 * @st_funcMD5		DFD2C95E0ADE8C13D321AAD24CC70B80
 * @st_funcID		LCCM655R0.FILE.030.FUNC.002
 */
void vFCU_ACCEL_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Transmit acceleration data over ethernet
 *
 * @param[in]		u16PacketType			The type of packet to transmit
 * @st_funcMD5		EC29840AA5182F63786383AE8105B0A7
 * @st_funcID		LCCM655R0.FILE.030.FUNC.001
 */
void vFCU_ACCEL_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_ACCEL__TX_FULL_DATA:
			u16Length = C_FCU__NUM_ACCEL_CHIPS * 50U;
			//data valid system
			u16Length += 14U;

			//thresholding
			u16Length += 9U;  // Accel
			u16Length += 9U;  // Decel
			break;

		case NET_PKT__FCU_ACCEL__TX_CAL_DATA:
			u16Length = C_FCU__NUM_ACCEL_CHIPS * 10U;
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
			case NET_PKT__FCU_ACCEL__TX_FULL_DATA:
				//30
				for(u8Device = 0U; u8Device < C_FCU__NUM_ACCEL_CHIPS; u8Device++)
				{

					//fault flags
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32SIL3_MMA8451__Get_FaultFlags(u8Device));
					pu8Buffer += 4U;

					//X Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__X));
					pu8Buffer += 2U;

					//Y Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__Y));
					pu8Buffer += 2U;

					//Z Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__Z));
					pu8Buffer += 2U;


					#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
						//X Accel
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32MMA8451_MATH__Get_GForce(u8Device, MMA8451_AXIS__X));
						pu8Buffer += 4U;

						//Y Accel
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32MMA8451_MATH__Get_GForce(u8Device, MMA8451_AXIS__Y));
						pu8Buffer += 4U;

						//Z Accel
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32MMA8451_MATH__Get_GForce(u8Device, MMA8451_AXIS__Z));
						pu8Buffer += 4U;

						//Pitch
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32MMA8451_MATH__Get_PitchAngle(u8Device));
						pu8Buffer += 4U;

						//Roll
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, f32MMA8451_MATH__Get_RollAngle(u8Device));
						pu8Buffer += 4U;
					#else
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
						pu8Buffer += 4U;
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
						pu8Buffer += 4U;
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
						pu8Buffer += 4U;
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
						pu8Buffer += 4U;
						vSIL3_NUM_CONVERT__Array_F32(pu8Buffer, 0.0F);
						pu8Buffer += 4U;
					#endif

					//FCU computed specifics
					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sChannels[u8Device].s32CurrentAccel_mm_ss);
					pu8Buffer += 4U;

					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sChannels[u8Device].s32CurrentVeloc_mm_s);
					pu8Buffer += 4U;

					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sChannels[u8Device].s32PrevVeloc_mm_s);
					pu8Buffer += 4U;

					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sChannels[u8Device].s32CurrentDisplacement_mm);
					pu8Buffer += 4U;

					vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sChannels[u8Device].s32PrevDisplacement_mm);
					pu8Buffer += 4U;

				}//for(u8Device = 0U; u8Device < C_FCU__NUM_ACCEL_CHIPS; u8Device++)



				//send our the data validity subsystem value
				pu8Buffer[0] = sFCU.sAccel.sValid.u8Enabled;
				pu8Buffer += 1U;

				pu8Buffer[0] = sFCU.sAccel.sValid.u8IsValid;
				pu8Buffer += 1U;

				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sValid.s32ValidAccel_mm_ss);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sValid.s32ValidVeloc_mm_s);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sValid.s32ValidDisplacement_mm);
				pu8Buffer += 4U;

				//send the accel thresholding data
				pu8Buffer[0] = sFCU.sAccel.sAccelThresh.u8ThresholdTrue;
				pu8Buffer += 1U;

				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sFCU.sAccel.sAccelThresh.u16ThreshTime_x10ms);
				pu8Buffer += 2U;
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sAccelThresh.s32Thresh_Accel_mm_ss);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sFCU.sAccel.sAccelThresh.u1610MS_Counter);
				pu8Buffer += 2U;

				//send the decel thresholding data
				pu8Buffer[0] = sFCU.sAccel.sDecelThresh.u8ThresholdTrue;
				pu8Buffer += 1U;

				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sFCU.sAccel.sDecelThresh.u16ThreshTime_x10ms);
				pu8Buffer += 2U;
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sAccel.sDecelThresh.s32Thresh_Accel_mm_ss);
				pu8Buffer += 4U;
				vSIL3_NUM_CONVERT__Array_U16(pu8Buffer, sFCU.sAccel.sDecelThresh.u1610MS_Counter);
				pu8Buffer += 2U;


				break;

			case NET_PKT__FCU_ACCEL__TX_CAL_DATA:

				//10 bytes per device
				for(u8Device = 0U; u8Device < C_FCU__NUM_ACCEL_CHIPS; u8Device++)
				{

					//fault flags
					vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, u32SIL3_MMA8451__Get_FaultFlags(u8Device));
					pu8Buffer += 4U;

					//X Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__X));
					pu8Buffer += 2U;

					//Y Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__Y));
					pu8Buffer += 2U;

					//Z Raw
					vSIL3_NUM_CONVERT__Array_S16(pu8Buffer, s16SIL3_MMA8451_FILTERING__Get_Average(u8Device, MMA8451_AXIS__Z));
					pu8Buffer += 2U;

				}
				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__FCU, C_RLOOP_NET_PORT__FCU);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
