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
			break;

	}//switch(eChannel)
}

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

			#if C_LOCALDEF__LCCM656__ENABLE_BRAKES == 1U
				if(u32ProgramIndex == (Luint32)sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u16N2HET_Prog)
				{
					vFCU_BRAKES_SW__Right_SwitchExtend_ISR();
				}

				if(u32ProgramIndex == (Luint32)sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u16N2HET_Prog)
				{
					vFCU_BRAKES_SW__Right_SwitchRetract_ISR();
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

