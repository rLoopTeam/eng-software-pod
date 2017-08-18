/**
 * @file        POWER_CORE__BMS_FANS.C
 * @brief       BMS Fan control
 * @author      Lachlan Grogan
 * @copyright   rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BMS_FANS
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U

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
 * Init the bms fans state
 *
 * @st_funcMD5
 * @st_funcID
 */
void vPWRNODE_BMS_FANS__Init(void)
{

    //Setup the hardware pins
    #if C_LOCALDEF__BMS_REVISION == 1U
        //No V1 Equivalent
    #elif C_LOCALDEF__BMS_REVISION == 2U
#ifndef WIN32
        vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 0U, GIO_DIRECTION__OUTPUT);

        //set to OFF
        vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);
#endif
    #else
        #error
    #endif
}

/***************************************************************************//**
 * @brief
 * Process the charge relay
 *
 * @st_funcMD5
 * @st_funcID
 */
void vPWRNODE_BMS_FANS__Process(void)
{

   //Not much to do here

}



/***************************************************************************//**
 * @brief
 * switch on the fans for the BMS discharge resistors
 *
 * @st_funcMD5
 * @st_funcID
 */
void vPWRNODE_BMS_FANS__On(void)
{

    #if C_LOCALDEF__BMS_REVISION == 1U
        //No V1 equivalent
    #elif C_LOCALDEF__BMS_REVISION == 2U
#ifndef WIN32
        vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 1U);
#endif
    #else
        #error
    #endif
}

/***************************************************************************//**
 * @brief
 * Switch off the fans for the bms discharge resistors
 *
 * @st_funcMD5
 * @st_funcID
 */
void vPWRNODE_BMS_FANS__Off(void)
{
    #if C_LOCALDEF__BMS_REVISION == 1U
        //No V1 Equivalent
    #elif C_LOCALDEF__BMS_REVISION == 2U
#ifndef WIN32
        vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 0U, 0U);
#endif
    #else
        #error
    #endif
}

void vPWR_BMS_FANS__100MS_ISR(){
    Luint8 u8Counter;
    Luint8 u8FanState = 0;

    //Check if any discharge resistors are enabled
    for(u8Counter = 0; u8Counter < C_BQ76__TOTAL_CELLS; u8Counter++)
    {
       if(sBQ76.sBalance.u8Resistor[u8Counter]){
           u8FanState = 1U;
           u8Counter = C_BQ76__TOTAL_CELLS;
       }
    }

    if(u8FanState == 1U){
       sPWRNODE.sBMS_Fans.u16FanTimeout = C_PWRCORE__BMS_FANS_TIMEOUT;
       vPWRNODE_BMS_FANS__On();
    }else{
        if(sPWRNODE.sBMS_Fans.u16FanTimeout == 0U){
            vPWRNODE_BMS_FANS__Off();
        }else{
            sPWRNODE.sBMS_Fans.u16FanTimeout -= 1;
        }
    }
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

