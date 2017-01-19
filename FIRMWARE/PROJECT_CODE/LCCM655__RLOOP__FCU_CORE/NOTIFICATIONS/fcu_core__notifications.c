/**
 * @file		FCU_CORE__NOTIFICATIONS.C
 * @brief		RM4 system level notifications
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
 * @addtogroup FCU_CORE__NOTIFICATIONS
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

extern struct _strFCU sFCU;

#ifndef WIN32

#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * UART Interrupt Notification
 * 
 * @param[in]		u32Flags				Module Flags
 * @param[in]		eChannel				Uart Channel
 * @st_funcMD5		304EF02D7BF62A3119548420F15F2222
 * @st_funcID		LCCM655R0.FILE.015.FUNC.001
 */
void vRM4_SCI_INT__Notification(RM4_SCI__CHANNEL_T eChannel, Luint32 u32Flags)
{
	Luint8 u8Array[1];
	switch(eChannel)
	{
		case SCI_CHANNEL__2:

			//pass off to PI
			u8Array[0] = u8RM4_SCI__Get_Rx_Value(SCI_CHANNEL__2);
			#if C_LOCALDEF__LCCM656__ENABLE_RX == 1U
				vPICOMMS_RX__Receive_Bytes(&u8Array[0], 1);
			#endif

			//send our byte to the LGU comms system
			#if C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM == 1U
				vFCU_LGU__Rx_Byte(u8Array[0]);
			#endif

			break;

		default:
			//no need
			break;

	}//switch(eChannel)
}

#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE

#endif //win32


/***************************************************************************//**
 * @brief
 * Interrupt from N2HET programs
 * 
 * @param[in]		u32Register				Reg values passed in
 * @param[in]		u32ProgramIndex			N2HET program index
 * @param[in]		eChannel				N2HET Channel
 * @st_funcMD5		BA3672C0F276685B06058BF6ECA514B1
 * @st_funcID		LCCM655R0.FILE.015.FUNC.002
 */
void vRM4_N2HET_DYNAMIC__Notification(RM4_N2HET__CHANNEL_T eChannel, Luint32 u32ProgramIndex, Luint32 u32Register)
{

	switch(eChannel)
	{
		case N2HET_CHANNEL__1:
			#if C_LOCALDEF__LCCM656__ENABLE_PUSHER == 1U
				if(u32ProgramIndex == (Luint32)sFCU.sPusher.sSwitches[0].u16N2HET_Prog)
				{
					vFCU_PUSHER__InterlockA_ISR();
				}

				if(u32ProgramIndex == (Luint32)sFCU.sPusher.sSwitches[1].u16N2HET_Prog)
				{
					vFCU_PUSHER__InterlockB_ISR();
				}
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				if(u32ProgramIndex == (Luint32)sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog)
				{
					vFCU_BRAKES_SW__Right_SwitchExtend_ISR();
				}

				if(u32ProgramIndex == (Luint32)sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog)
				{
					vFCU_BRAKES_SW__Right_SwitchRetract_ISR();
				}
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

				//setup the contrast sensor programs
				if(u32ProgramIndex == sFCU.sContrast.sSensors[LASER_CONT__FWD].u16N2HET_Index)
				{
					vFCU_LASERCONT__ISR(LASER_CONT__FWD, u32Register);
				}
				if(u32ProgramIndex == sFCU.sContrast.sSensors[LASER_CONT__MID].u16N2HET_Index)
				{
					vFCU_LASERCONT__ISR(LASER_CONT__MID, u32Register);
				}
				if(u32ProgramIndex == sFCU.sContrast.sSensors[LASER_CONT__AFT].u16N2HET_Index)
				{
					vFCU_LASERCONT__ISR(LASER_CONT__AFT, u32Register);
				}
			#endif


			break;

		default:
			//do nothing.
			break;

	}//switch(eChannel)

	//FCU_Process_EdgeISR(u32ProgramIndex, u32Register);
}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

