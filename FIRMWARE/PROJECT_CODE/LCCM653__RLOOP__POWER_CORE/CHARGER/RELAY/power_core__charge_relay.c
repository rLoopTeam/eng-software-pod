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

#include "../../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

extern struct _strPWRNODE sPWRNODE;


/***************************************************************************//**
 * @brief
 * Init the charge relay state
 * 
 * @st_funcMD5		6F451776DBE4DCAE500A358AB04D18A7
 * @st_funcID		LCCM653R0.FILE.022.FUNC.001
 */
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

/***************************************************************************//**
 * @brief
 * Process the charge relay
 * 
 * @st_funcMD5		1C9F48BE1837BEFD9325D836ACCB6CFC
 * @st_funcID		LCCM653R0.FILE.022.FUNC.002
 */
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



/***************************************************************************//**
 * @brief
 * switch on the charger relay
 * 
 * @st_funcMD5		A9BFD6505E8FC763D0B281BE62161696
 * @st_funcID		LCCM653R0.FILE.022.FUNC.003
 */
void vPWRNODE_CHG_RELAY__On(void)
{

	//todo, change state

	//for test week, toggle the pin.
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 1U, 1U);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		44A67B75C1052F8DCA9577FCCE0DE0E4
 * @st_funcID		LCCM653R0.FILE.022.FUNC.004
 */
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

