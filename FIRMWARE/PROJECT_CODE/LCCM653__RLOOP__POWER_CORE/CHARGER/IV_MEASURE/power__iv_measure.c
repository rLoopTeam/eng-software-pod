/**
 * @file        POWER__IV_MEASURE.C
 * @brief       Charger current and voltage measurement
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
 * @addtogroup POWER_NODE__IV_MEASURE
 * @ingroup POWER_NODE
 * @{ */

#include "../../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

#define ADCREFERENCEVOLTAGE             (5F)

extern struct _strPWRNODE sPWRNODE;

Lfloat32 f32PWRNODE_CHG_IV__Filter_Current_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Voltage_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Ref_ADC_Value(Lfloat32 ADC_Sample);

/***************************************************************************//**
 * @brief
 * Init the charger voltage and current measurement
 * 
 * @st_funcMD5      60D7C48E9A55F549B328B969C6A38605
 * @st_funcID       LCCM653R0.FILE.023.FUNC.001
 */
void vPWRNODE_CHG_IV__Init(void)
{
    vSIL3_FAULTTREE__Init(&sPWRNODE.sCHARGER_IV.sFaultFlags);

    //the ADC is already init

}

/***************************************************************************//**
 * @brief
 * Process the charger voltage and current measurement.
 * 
 * @st_funcMD5      AF5EF4D90978E6F62271760FF836E754
 * @st_funcID       LCCM653R0.FILE.023.FUNC.002
 */
void vPWRNODE_CHG_IV__Process(void)
{
    Lfloat32 f32ChargeCurrentVoltage_Sample;
    Lfloat32 f32ChargeCurrentRefVoltage_Sample;
    //Lfloat32 f32BattCurrentVoltage_Sample;
    //Lfloat32 f32BattCurrentRefVoltage_Sample;
    Lfloat32 f32ChargerVoltageVoltage_Sample;
    //Lfloat32 f32BattVoltageVoltage_Sample;
    Luint8 u8New;


    //Sample the ADC channels if new data is available
#ifndef WIN32
    u8New = u8RM4_ADC_USER__Is_NewDataAvailable();
#else
    u8New = 1U;
#endif
    if(u8New == 1U)
    {

        //get the ADC data for each channel
#ifndef WIN32
        f32ChargerVoltageVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(0U);
        //f32BattCurrentVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(1U);
        //f32BattCurrentRefVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(2U);
        //f32BattVoltageVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(3U);
        f32ChargeCurrentRefVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(4U);
        f32ChargeCurrentVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(5U);

#else
        //f32Voltage_Sample = 0 - sPWRNODE.sHASS600.f32HASS_VoltageOffSet;
        f32ChargeCurrentRefVoltage_Sample = 2.5;
#endif

        //Filter the reference voltage and save it to the main struct
        sPWRNODE.sCHARGER_IV.f32HASS_RefVoltageReading = f32PWRNODE_CHG_IV__Filter_Ref_ADC_Value(f32ChargeCurrentRefVoltage_Sample);

        //Convert voltage reading to current reading
        //Charger current sensor is 50A model
        sPWRNODE.sCHARGER_IV.f32HASS_CurrentReading = f32PWRNODE_CHG_IV__Filter_Current_ADC_Value( C_PWRCORE__CURRENT_HASS_IPN/.625F * (f32ChargeCurrentVoltage_Sample - sPWRNODE.sCHARGER_IV.f32HASS_RefVoltageReading));

        //Convert ADC voltage reading to node input voltage value
        sPWRNODE.sCHARGER_IV.f32HAAS_ChargerVoltageReading = f32PWRNODE_CHG_IV__Filter_Voltage_ADC_Value((f32ChargerVoltageVoltage_Sample - 1.28F) * 77.93F);

        //TODO Change 999999 limit to something like 50 A
        //set any alarms (flags based on any limits)
        if (sPWRNODE.sCHARGER_IV.f32HASS_CurrentReading > 999999)
        {
            vSIL3_FAULTTREE__Set_Flag(&sPWRNODE.sCHARGER_IV.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX__00);
            vSIL3_FAULTTREE__Set_Flag(&sPWRNODE.sCHARGER_IV.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX_MASK__00);
        }

        //taken the data now
#ifndef WIN32
        vRM4_ADC_USER__Clear_NewDataAvailable();
#endif

    }
    else
    {
        //adc not ready yet, don't do anything
    }
}

/***************************************************************************//**
 * @brief
 * Average the current readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Ref_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HAAS_Voltage_Ref_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HAAS_Voltage_Ref_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the current readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Current_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HAAS_Current_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HAAS_Current_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the current readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Voltage_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16Charger_Voltage_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32Charger_Voltage_Average_Array[0]);

    return f32Return;
}

//todo: provide functions to get the current voltages and currents as well as any fault flags.


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

