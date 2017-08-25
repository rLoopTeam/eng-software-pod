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

Lfloat32 f32PWRNODE_CHG_IV__Filter_Small_Current_Ref_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Small_Current_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Large_Current_Ref_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Large_Current_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Charger_Voltage_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Filter_Battery_Voltage_ADC_Value(Lfloat32 ADC_Sample);
Lfloat32 f32PWRNODE_CHG_IV__Current_Sensor_Value(Lfloat32 f32MeasVolts, Lfloat32 f32RefVolts, Lfloat32 f32IPN);


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

    sPWRNODE.sCHARGER_IV.u8FirstRun = 1U;

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
    Lfloat32 f32ChargerVoltageVoltage_Sample;
    Lfloat32 f32LargeCurrentVoltage_Sample;
    Lfloat32 f32LargeCurrentRefVoltage_Sample;
    Lfloat32 f32BattVoltageVoltage_Sample;
    Lfloat32 f32SmallCurrentRefVoltage_Sample;
    Lfloat32 f32SmallCurrent_Sample;
    Luint8 u8New;
    Luint8 u8Counter;


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

        f32LargeCurrentVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(1U);
        f32LargeCurrentRefVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(2U);

        f32BattVoltageVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(3U);

        f32SmallCurrentRefVoltage_Sample = f32RM4_ADC_USER__Get_Voltage(4U);
        f32SmallCurrent_Sample = f32RM4_ADC_USER__Get_Voltage(5U);

#else
        //f32Voltage_Sample = 0 - sPWRNODE.sHASS600.f32HASS_VoltageOffSet;
        f32ChargeCurrentRefVoltage_Sample = 2.5;
#endif



        //Filter the small current reference voltage and save it to the main struct
        sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentRefVoltageReading = f32PWRNODE_CHG_IV__Filter_Small_Current_Ref_ADC_Value(f32SmallCurrentRefVoltage_Sample);

        //Convert voltage reading to current reading
        //small current sensor is 50A model
        sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading = f32PWRNODE_CHG_IV__Filter_Small_Current_ADC_Value(f32PWRNODE_CHG_IV__Current_Sensor_Value(f32SmallCurrent_Sample, sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentRefVoltageReading, 50.0));

        //Filter the large current reference voltage and save it to the main struct
        sPWRNODE.sCHARGER_IV.f32HASS_LargeCurrentRefVoltageReading = f32PWRNODE_CHG_IV__Filter_Large_Current_Ref_ADC_Value(f32LargeCurrentRefVoltage_Sample);

        //Convert voltage reading to current reading
        //small current sensor is 600A model
        sPWRNODE.sCHARGER_IV.f32HASS_LargeCurrentReading = f32PWRNODE_CHG_IV__Filter_Large_Current_ADC_Value(f32PWRNODE_CHG_IV__Current_Sensor_Value(f32LargeCurrentVoltage_Sample, sPWRNODE.sCHARGER_IV.f32HASS_LargeCurrentRefVoltageReading, 600.0));

        //Convert ADC voltage reading to charger voltage reading
        sPWRNODE.sCHARGER_IV.f32HASS_ChargerVoltageReading = f32PWRNODE_CHG_IV__Filter_Charger_Voltage_ADC_Value((f32ChargerVoltageVoltage_Sample - 1.28F) * 77.93F);

        //Convert ADC voltage reading to battery input voltage value
        sPWRNODE.sCHARGER_IV.f32HASS_BattVoltageReading = f32PWRNODE_CHG_IV__Filter_Battery_Voltage_ADC_Value((f32BattVoltageVoltage_Sample - 1.28F) * 77.93F);

        //TODO Change 999999 limit to something like 50 A
        //set any alarms (flags based on any limits)
        if (sPWRNODE.sCHARGER_IV.f32HASS_LargeCurrentReading > 999999)
        {
            vSIL3_FAULTTREE__Set_Flag(&sPWRNODE.sCHARGER_IV.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX__00);
            vSIL3_FAULTTREE__Set_Flag(&sPWRNODE.sCHARGER_IV.sFaultFlags, C_LCCM653__IVMEASURE__FAULT_INDEX_MASK__00);
        }

        //Seed the averages on the first sample
        if(sPWRNODE.sCHARGER_IV.u8FirstRun == 1U)
        {
            sPWRNODE.sCHARGER_IV.u16HASS_Large_Current_Average_Counter = 0;
            sPWRNODE.sCHARGER_IV.u16HASS_Small_Current_Average_Counter = 0;
            sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading = f32PWRNODE_CHG_IV__Filter_Small_Current_ADC_Value(f32PWRNODE_CHG_IV__Current_Sensor_Value(f32SmallCurrent_Sample, sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Ref_Average_Array[0], 50.0));
            sPWRNODE.sCHARGER_IV.f32HASS_LargeCurrentReading = f32PWRNODE_CHG_IV__Filter_Large_Current_ADC_Value(f32PWRNODE_CHG_IV__Current_Sensor_Value(f32LargeCurrentVoltage_Sample, sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Ref_Average_Array[0], 600.0));

            for(u8Counter = 1;u8Counter< C_PWRCORE__CURRENT_AVG_SIZE; u8Counter++){
                sPWRNODE.sCHARGER_IV.f32Charger_Batt_Voltage_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32Charger_Batt_Voltage_Average_Array[0];
                sPWRNODE.sCHARGER_IV.f32Charger_Voltage_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32Charger_Voltage_Average_Array[0];
                sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Average_Array[0];
                sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Ref_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Ref_Average_Array[0];
                sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Average_Array[0];
                sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Ref_Average_Array[u8Counter] = sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Ref_Average_Array[0];
            }

            sPWRNODE.sCHARGER_IV.f32HASS_BattVoltageReading = sPWRNODE.sCHARGER_IV.f32Charger_Batt_Voltage_Average_Array[0];
            sPWRNODE.sCHARGER_IV.f32HASS_ChargerVoltageReading = sPWRNODE.sCHARGER_IV.f32Charger_Voltage_Average_Array[0];

            sPWRNODE.sCHARGER_IV.u8FirstRun = 0U;
        }else{
            //Do nothing
        }

        if(sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading < 100 && sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading >= 0)
        {
            sPWRNODE.sCHARGER_IV.f32HASS_BatteryCurrent = sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading;
            sPWRNODE.sCHARGER_IV.f32HASS_ChargingCurrent = 0;
        }else if (sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading >= 100) {
            sPWRNODE.sCHARGER_IV.f32HASS_BatteryCurrent = sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading;
            sPWRNODE.sCHARGER_IV.f32HASS_ChargingCurrent = 0;
        }else if (sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading < 0)
        {
            sPWRNODE.sCHARGER_IV.f32HASS_BatteryCurrent = 0;
            sPWRNODE.sCHARGER_IV.f32HASS_ChargingCurrent = sPWRNODE.sCHARGER_IV.f32HASS_SmallCurrentReading * -1;
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
 * Average the small current reference voltage
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Small_Current_Ref_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HASS_Small_Current_Ref_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Ref_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the small current reading
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Small_Current_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HASS_Small_Current_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HASS_Small_Current_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the large current reference voltage readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Large_Current_Ref_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HASS_Large_Current_Ref_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Ref_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the large current sensor readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Large_Current_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16HASS_Large_Current_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32HASS_Large_Current_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the charger voltage readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Charger_Voltage_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16Charger_Voltage_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32Charger_Voltage_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Average the battery voltage readings
 *
 * @st_funcMD5
 * @st_funcID
 */

Lfloat32 f32PWRNODE_CHG_IV__Filter_Battery_Voltage_ADC_Value(Lfloat32 ADC_Sample)
{
    Lfloat32 f32Return;

    f32Return = f32SIL3_NUM_FILTERING__Add_F32( ADC_Sample,
                                                &sPWRNODE.sCHARGER_IV.u16Charger_Batt_Voltage_Average_Counter,
                                                C_PWRCORE__CURRENT_AVG_SIZE,
                                                &sPWRNODE.sCHARGER_IV.f32Charger_Batt_Voltage_Average_Array[0]);

    return f32Return;
}

/***************************************************************************//**
 * @brief
 * Current sensor voltage reading to current
 *
 * @st_funcMD5
 * @st_funcID
 */
Lfloat32 f32PWRNODE_CHG_IV__Current_Sensor_Value(Lfloat32 f32MeasVolts, Lfloat32 f32RefVolts, Lfloat32 f32IPN)
{
   return (f32IPN/.625F * (f32MeasVolts - f32RefVolts))*-1.0F;
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

