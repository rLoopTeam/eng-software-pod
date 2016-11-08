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


void vFCU_BRAKES_SW__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Get Brake 0 (Left) Extend swtich state
 *
 * @return				1 = Closed\n
 * 						0 = Open
 */
Luint8 u8FCU_BRAKES_SW__Get_B0_Extend(void)
{
	Luint32 u32Temp;
	Luint8 u8Return;

	u32Temp = u32RM4_GIO__Get_Bit(gioPORTA, 0U);
	if(u32Temp == 0U)
	{
		//switch closed
		u8Return = 1U;
	}
	else
	{
		//switch open
		u8Return = 0U;
	}

	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Get Brake 0 (Left) Retract swtich state
 *
 * @return				1 = Closed\n
 * 						0 = Open
 */
Luint8 u8FCU_BRAKES_SW__Get_B0_Retract(void)
{
	Luint32 u32Temp;
	Luint8 u8Return;

	u32Temp = u32RM4_GIO__Get_Bit(gioPORTA, 1U);
	if(u32Temp == 0U)
	{
		//switch closed
		u8Return = 1U;
	}
	else
	{
		//switch open
		u8Return = 0U;
	}

	return u8Return;
}

/***************************************************************************//**
 * @brief
 * Get Brake 1 (Right) Extend swtich state
 *
 * @return				1 = Closed\n
 * 						0 = Open
 */
Luint8 u8FCU_BRAKES_SW__Get_B1_Extend(void)
{
	Luint32 u8Temp;
	Luint8 u8Return;

	u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 9U);
	if(u8Temp == 0U)
	{
		//switch closed
		u8Return = 1U;
	}
	else
	{
		//switch open
		u8Return = 0U;
	}

	return u8Return;
}

/***************************************************************************//**
 * @brief
 * Get Brake 1 (Right) Retract swtich state
 *
 * @return				1 = Closed\n
 * 						0 = Open
 */
Luint8 u8FCU_BRAKES_SW__Get_B1_Retract(void)
{
	Luint32 u8Temp;
	Luint8 u8Return;

	u8Temp = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 22U);
	if(u8Temp == 0U)
	{
		//switch closed
		u8Return = 1U;
	}
	else
	{
		//switch open
		u8Return = 0U;
	}

	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Retract switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__B0_SwitchRetract_ISR(void)
{
	//todo
}

/***************************************************************************//**
 * @brief
 * Brake 0 (Left) Extended switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__B0_SwitchExtend_ISR(void)
{
	//todo
}


/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Retract switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__B1_SwitchRetract_ISR(void)
{
	//todo
}

/***************************************************************************//**
 * @brief
 * Brake 1 (Right) Extended switch interrupt handler
 *
 *
 */
void vFCU_BRAKES_SW__B1_SwitchExtend_ISR(void)
{
	//todo
}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

