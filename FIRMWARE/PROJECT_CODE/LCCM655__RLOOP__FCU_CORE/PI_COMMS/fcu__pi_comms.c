/**
 * @file		FCU__PI_COMMS.C
 * @brief		FCU to PiComms interface layer
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
 * @addtogroup FCU__PI_COMMS
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_PI_COMMS == 1U

//The PICOMMS RX Callbacks
void vFCU_PICOMMS__recvLuint8(Luint16 u16Index, Luint8 data);
void vFCU_PICOMMS__recvLint8(Luint16 index, Lint8 data);
void vFCU_PICOMMS__recvLuint16(Luint16 index, Luint16 data);
void vFCU_PICOMMS__recvLint16(Luint16 index, Lint16 data);
void vFCU_PICOMMS__recvLuint32(Luint16 u16Index, Luint32 u32Data);
void vFCU_PICOMMS__recvLint32(Luint16 index, Lint32 data);
void vFCU_PICOMMS__recvLuint64(Luint16 index, Luint64 data);
void vFCU_PICOMMS__recvLint64(Luint16 index, Lint64 data);
void vFCU_PICOMMS__recvLfloat32(Luint16 index, Lfloat32 data);
void vFCU_PICOMMS__recvLfloat64(Luint16 index, Lfloat64 data);

//the structure
extern struct _strFCU sFCU;

//the main structure
extern struct _strPICOMMS sPC;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_PICOMMS__Init(void)
{

	//default or variables
	sFCU.sPiComms.eState = PICOM_STATE__IDLE;
	sFCU.sPiComms.u8100MS_Timer = 0U;

	//init pi comms
	vPICOMMS__Init();

	//Attach all the callbacks
	PICOMMS_RX_recvLuint8 = &vFCU_PICOMMS__recvLuint8;
	PICOMMS_RX_recvLint8 = &vFCU_PICOMMS__recvLint8;
	PICOMMS_RX_recvLuint16 = &vFCU_PICOMMS__recvLuint16;
	PICOMMS_RX_recvLint16 = &vFCU_PICOMMS__recvLint16;
	PICOMMS_RX_recvLuint32 = &vFCU_PICOMMS__recvLuint32;
	PICOMMS_RX_recvLint32 = &vFCU_PICOMMS__recvLint32;
	PICOMMS_RX_recvLuint64 = &vFCU_PICOMMS__recvLuint64;
	PICOMMS_RX_recvLint64 = &vFCU_PICOMMS__recvLint64;
	PICOMMS_RX_recvLfloat32 = &vFCU_PICOMMS__recvLfloat32;
	PICOMMS_RX_recvLfloat64 = &vFCU_PICOMMS__recvLfloat64;

	//switch on notifications now we are ready
	#if C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS == 1U
		vRM4_SCI_INT__Enable_Notification(SCI_CHANNEL__2, SCI_RX_INT);
	#endif

}


/***************************************************************************//**
 * @brief
 * Process any PiComms tasks
 * 
 */
void vFCU_PICOMMS__Process(void)
{
	Luint32 u32Length;
	Luint8 * pu8Buffer;
	Luint8 u8Test;
	Luint8 u8Counter;

	//process our state machine
	switch(sFCU.sPiComms.eState)
	{

		case PICOM_STATE__IDLE:

			//check the timer state
			if(sFCU.sPiComms.u8100MS_Timer == 1U)
			{
				//only do a new frame the DMA is not busy
				u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
				if(u8Test == 0U)
				{
					sFCU.sPiComms.eState = PICOM_STATE__SETUP_FRAME;

					sFCU.sPiComms.u8100MS_Timer = 0U;
				}
			}
			else
			{

			}

			break;

		case PICOM_STATE__SETUP_FRAME:
			//start a new frame
			PICOMMS_TX_beginFrame();

			//change states
			sFCU.sPiComms.eState = PICOM_STATE__ASSEMBLE_BUFFER;
			break;

		case PICOM_STATE__ASSEMBLE_BUFFER:

			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU_BRAKES__LEFT__SCREW_POS, f32FCU_BRAKES__Get_ScrewPos(FCU_BRAKE__LEFT));
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU_BRAKES__RIGHT__SCREW_POS, f32FCU_BRAKES__Get_ScrewPos(FCU_BRAKE__RIGHT));

				vPICOMMS_TX__Add_U8(PI_PACKET__FCU_BRAKES__LEFT__LIMIT_EXTEND, (Luint8)eFCU_BRAKES__Get_SwtichState(FCU_BRAKE__LEFT, BRAKE_SW__EXTEND));
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU_BRAKES__RIGHT__LIMIT_EXTEND, (Luint8)eFCU_BRAKES__Get_SwtichState(FCU_BRAKE__RIGHT, BRAKE_SW__EXTEND));
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU_BRAKES__LEFT__LIMIT_RETRACT, (Luint8)eFCU_BRAKES__Get_SwtichState(FCU_BRAKE__LEFT, BRAKE_SW__RETRACT));
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU_BRAKES__RIGHT__LIMIT_RETRACT, (Luint8)eFCU_BRAKES__Get_SwtichState(FCU_BRAKE__RIGHT, BRAKE_SW__RETRACT));

				vPICOMMS_TX__Add_F32(PI_PACKET__FCU_BRAKES__LEFT__IBEAM_DIST, f32FCU_BRAKES__Get_IBeam_mm(FCU_BRAKE__LEFT));
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU_BRAKES__RIGHT__IBEAM_DIST, f32FCU_BRAKES__Get_IBeam_mm(FCU_BRAKE__RIGHT));

				vPICOMMS_TX__Add_U16(PI_PACKET__FCU_BRAKES__LEFT__ADC_RAW, u16FCU_BRAKES__Get_ADC_Raw(FCU_BRAKE__LEFT));
				vPICOMMS_TX__Add_U16(PI_PACKET__FCU_BRAKES__RIGHT__ADC_RAW, u16FCU_BRAKES__Get_ADC_Raw(FCU_BRAKE__RIGHT));

				vPICOMMS_TX__Add_F32(PI_PACKET__FCU_BRAKES__LEFT__MLP_SCALED, f32FCU_BRAKES__Get_MLP_mm(FCU_BRAKE__LEFT));
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__BRAKES__RIGHT__MLP_SCALED, f32FCU_BRAKES__Get_MLP_mm(FCU_BRAKE__RIGHT));
			#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
				for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_LASER_OPTONCDT; u8Counter++)
				{
					vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__PITCH_FL + u8Counter, f32FCU_LASEROPTO__Get_Distance(u8Counter));
				}
				/*
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__PITCH_FR, 0.0F);
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__PITCH_RL, 0.0F);
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__PITCH_RR, 0.0F);
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__YAW_F, 0.0F);
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__LASER__YAW_R, 0.0F);
				*/
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU__PUSHER_SW_A, u8FCU_PUSHER__Get_Switch(0U));
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU__PUSHER_SW_B, u8FCU_PUSHER__Get_Switch(1U));
				vPICOMMS_TX__Add_U8(PI_PACKET__FCU__PUSHER_STATE, u8FCU_PUSHER__Get_PusherState());
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
				vPICOMMS_TX__Add_S16(PI_PACKET__FCU__ACCEL1_X, s16FCU_ACCEL__Get_LastSample(0U, 0U));
				vPICOMMS_TX__Add_S16(PI_PACKET__FCU__ACCEL1_Y, s16FCU_ACCEL__Get_LastSample(0U, 1U));
				vPICOMMS_TX__Add_S16(PI_PACKET__FCU__ACCEL1_Z, s16FCU_ACCEL__Get_LastSample(0U, 2U));

				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__ACCEL1_GFORCE_X, f32FCU_ACCEL__Get_LastG(0U, 0U));
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__ACCEL1_GFORCE_Y, f32FCU_ACCEL__Get_LastG(0U, 1U));
				vPICOMMS_TX__Add_F32(PI_PACKET__FCU__ACCEL1_GFORCE_Z, f32FCU_ACCEL__Get_LastG(0U, 2U));

			#endif


			//move to transmit
			sFCU.sPiComms.eState = PICOM_STATE__START_DMA;

			break;

		case PICOM_STATE__START_DMA:
			//end the frame
			u32Length = (Luint32)PICOMMS_TX_endFrame();

			//get the buffer pointer
			pu8Buffer = pu8I2CTx__Get_BufferPointer();

			//todo, probably should check transaction is not running

			//start the transaction.
			#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
				vRM4_SCI_DMA__Begin_Tx(SCI_CHANNEL__2, pu8Buffer, u32Length);
			#endif

			//change state
				sFCU.sPiComms.eState = PICOM_STATE__WAIT_DMA;
			break;

		case PICOM_STATE__WAIT_DMA:

			//test if the DMA is running
			#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
				u8Test = u8RM4_SCI_DMA__Is_TxBusy(SCI_CHANNEL__2);
			#else
				u8Test = 0U;
			#endif
			if(u8Test == 0U)
			{
				//cleanup the DMA interrupts for next time.
				vRM4_SCI_DMA__Cleanup(SCI_CHANNEL__2);

				//todo, for now go back to start.
				sFCU.sPiComms.eState = PICOM_STATE__IDLE;
			}
			else
			{
				//stay in state
			}

			break;

	}

}

//100ms timer tick
void vFCU_PICOMMS__100MS_ISR(void)
{
	//set the flag
	sFCU.sPiComms.u8100MS_Timer = 1U;

}

/***************************************************************************//**
 * @brief
 * Process all the UINT8 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLuint8(Luint16 u16Index, Luint8 data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{
//		case PI_PACKET__PWRNODE__NODE_PRESS_STREAM_CONTROL:
//			break;


	}

/*
	switch(index)
	{
		case  10000: sPC.sLp.PICOMMS_LOOP_UINT8 = data;
				break;
	}
*/

}

/***************************************************************************//**
 * @brief
 * Process all the INT8 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLint8(Luint16 index, Lint8 data)
{
	switch(index)
	{
		case  10001: sPC.sLp.PICOMMS_LOOP_INT8 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the UINT16 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLuint16(Luint16 index, Luint16 data)
{
	switch(index)
	{
		case  10002: sPC.sLp.PICOMMS_LOOP_UINT16 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT16 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLint16(Luint16 index, Lint16 data)
{
	switch(index)
	{
		case  10003: sPC.sLp.PICOMMS_LOOP_INT16 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the UINT32 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLuint32(Luint16 u16Index, Luint32 u32Data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{

		case PI_PACKET__PWRNODE__POD_STOP_UNLOCK_KEY:
			break;

		case PI_PACKET__PWRNODE__POD_STOP_COMMAND:
			break;


		case PI_PACKET__FCU_BRAKES__SET_LEFTMOTOR__MICROSTEPS:
			vSTEPDRIVE_MEM__Set_MicroStepResolution(0U, (Luint8)u32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_LEFTMOTOR__STEPS_REV:
			//hard coded
			break;

		case PI_PACKET__FCU_BRAKES__SET_RIGHTMOTOR__MICROSTEPS:
			vSTEPDRIVE_MEM__Set_MicroStepResolution(1U, (Luint8)u32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_RIGHTMOTOR__STEPS_REV:
			//hard coded
			break;

		default:
			//do nothing.
			break;

	}//switch((E_PICOMMS__PACKET_TYPES_T)index)

	/*
	switch(u16Index)
	{
		case  10004: sPC.sLp.PICOMMS_LOOP_UINT32 = data;
				break;
	}
	*/
}

/***************************************************************************//**
 * @brief
 * Process all the INT32 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLint32(Luint16 u16Index, Lint32 s32Data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{

		case PI_PACKET__FCU_BRAKES__SET_LEFTMOTOR__MAX_ACCEL:
			vSTEPDRIVE_MEM__Set_MaxAngularAccel(0U, s32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_LEFTMOTOR__MICRO_REV:
			vSTEPDRIVE_MEM__Set_PicoMeters_PerRev(0U, s32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_LEFTMOTOR__MAX_VELOC:
			vSTEPDRIVE_MEM__Set_MaxRPM(0U, s32Data);
			break;

		case PI_PACKET__FCU_BRAKES__SET_RIGHTMOTOR__MAX_ACCEL:
			vSTEPDRIVE_MEM__Set_MaxAngularAccel(1U, s32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_RIGHTMOTOR__MICRO_REV:
			vSTEPDRIVE_MEM__Set_PicoMeters_PerRev(1U, s32Data);
			break;
		case PI_PACKET__FCU_BRAKES__SET_RIGHTMOTOR__MAX_VELOC:
			vSTEPDRIVE_MEM__Set_MaxRPM(1U, s32Data);
			break;


		default:
			//do nothing.
			break;

	}//switch((E_PICOMMS__PACKET_TYPES_T)index)
	/*
	switch(index)
	{
		case  10005: sPC.sLp.PICOMMS_LOOP_INT32 = data;
				break;
	}
	*/
}

/***************************************************************************//**
 * @brief
 * Process all the UINT64 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLuint64(Luint16 index, Luint64 data)
{
	switch(index)
	{
		case  10006: sPC.sLp.PICOMMS_LOOP_UINT64 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the INT64 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLint64(Luint16 index, Lint64 data)
{
	switch(index)
	{
		case  10007: sPC.sLp.PICOMMS_LOOP_INT64 = data;
				break;
	}
}

/***************************************************************************//**
 * @brief
 * Process all the FLOAT32 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLfloat32(Luint16 u16Index, Lfloat32 f32Data)
{

	switch((E_PICOMMS__PACKET_TYPES_T)u16Index)
	{
		case PI_PACKET__FCU_BRAKES__SET_IBEAM_DIST:
			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				vFCU_BRAKES__Move_IBeam_Distance_mm(f32Data);
			#endif
			break;

	}

/*

	switch(index)
	{
		case  10008: sPC.sLp.PICOMMS_LOOP_FLOAT32 = data;
				break;
	}
*/
}

/***************************************************************************//**
 * @brief
 * Process all the FLOAT64 parameters sent from the GS.
 *
 */
void vFCU_PICOMMS__recvLfloat64(Luint16 index, Lfloat64 data)
{
	switch(index)
	{
		case  10009: sPC.sLp.PICOMMS_LOOP_FLOAT64 = data;
				break;
	}
}

#endif //C_LOCALDEF__LCCM655__ENABLE_PI_COMMS
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

