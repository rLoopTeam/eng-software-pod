/**
 * @file		POWER_CORE__CHARGE_RELAY.C
 * @brief		Charger Relay Control
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
 * @addtogroup POWER_NODE__CHARGE_RELAY
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

extern struct _strPWRNODE sPWRNODE;


void vPWRNODE_CHG_RELAY__Init(void)
{

	//init
	sPWRNODE.sCharger.eRelayState = CHG_RLY_STATE__RESET;

	//Setup the hardware pins
	//GPIOA1
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 1U, GIO_DIRECTION__OUTPUT);

	//set to OFF
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 0U);
}

void vPWRNODE_CHG_RELAY__Process(void)
{

	//handle the charger relay control
	switch(sPWRNODE.sCharger.eRelayState)
	{
		case CHG_RLY_STATE__RESET:
			//do nothing.
			break;

	}//switch(sPWRNODE.sCharger.eRelayState)

}


//switch on the charger relay
void vPWRNODE_CHG_RELAY__On(void)
{

	//todo, change state

	//for test week, toggle the pin.
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 1U);
}

void vPWRNODE_CHG_RELAY__Off(void)
{

	//todo, change state

	//for test week, toggle the pin.
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 0U);
}

#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER
#ifndef C_LOCALDEF__LCCM653__ENABLE_CHARGER
	#error
#endif
#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

