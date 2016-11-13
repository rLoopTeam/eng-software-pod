/**
 * @file		FCU__BRAKES__SWITCHES.C
 * @brief		Switch interface for the brakes.
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
 * @addtogroup FCU__BRAKES__SWITCHES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the brake switches modules
 *
 */
void vFCU_BRAKES_SW__Init(void)
{
	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 0U;

	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 0U;
	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 0U;
}

/***************************************************************************//**
 * @brief
 * Gets the state of a brake limit swtich
 *
 * @param[in] 			eBrake			The brake, left or right
 * @param[in]			eSwitch			The extend or retract switch
 * @return				Open, Closed or Unknown
  */
E_FCU__SWITCH_STATE_T eFCU_BRAKES_SW__Get_Switch(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch)
{
	Luint32 u32Temp;
	Luint8 u8Temp;
	E_FCU__SWITCH_STATE_T eReturn;

	//init our return in place of default switch statements
	eReturn = SW_STATE__UNKNOWN;

	switch(eBrake)
	{
		case FCU_BRAKE__LEFT:

			switch(eSwitch)
			{
				case BRAKE_SW__EXTEND:
					u32Temp = u32RM4_GIO__Get_Bit(gioPORTA, 0U);
					if(u32Temp == 0U)
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					else
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					break;

				case BRAKE_SW__RETRACT:
					u32Temp = u32RM4_GIO__Get_Bit(gioPORTA, 1U);
					if(u32Temp == 0U)
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					else
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					break;

				default:
					//handled in init return
					break;
			}//switch(eSwitch)


			break;

		case FCU_BRAKE__RIGHT:
			switch(eSwitch)
			{
				case BRAKE_SW__EXTEND:
					u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 9U);
					if(u8Temp == 0U)
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					else
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					break;

				case BRAKE_SW__RETRACT:
					u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 22U);
					if(u8Temp == 0U)
					{
						//switch closed
						eReturn = SW_STATE__CLOSED;
					}
					else
					{
						//switch open
						eReturn = SW_STATE__OPEN;
					}
					break;

				default:
					//handled in return init
					break;
			}//switch(eSwitch)
			break;

		default:
			//handled in return init
			break;

	}//switch(eBrake)


	return eReturn;
}


/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Retract switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__Left_SwitchRetract_ISR(void)
{
	vSTEPDRIVE_LIMIT__Limit_ISR(0U);

	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 1U;
}

/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Extended switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__Left_SwitchExtend_ISR(void)
{
	vSTEPDRIVE_LIMIT__Limit_ISR(0U);

	sFCU.sBrakes[FCU_BRAKE__LEFT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 1U;
}


/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Retract switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__Right_SwitchRetract_ISR(void)
{
	vSTEPDRIVE_LIMIT__Limit_ISR(1U);

	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen = 1U;
}

/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Extended switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__Right_SwitchExtend_ISR(void)
{
	vSTEPDRIVE_LIMIT__Limit_ISR(1U);

	sFCU.sBrakes[FCU_BRAKE__RIGHT].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen = 1U;
}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

