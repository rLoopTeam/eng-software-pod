/*
 * power_core__defines.h
 *
 *  Created on: 28 Dec 2016
 *      Author: Lachlan
 */

#ifndef RLOOP_POWER_CORE__DEFINES_H_
#define RLOOP_POWER_CORE__DEFINES_H_

	//number of 10ms timers per Tx count
	#define C_ETH_PACKET_TX_COUNT					(10U)

	/** Enable UNICASTING to GS */
	#define C_ETH_ENABLE_UNICAST						(0U)

	/** Number of 6P modules in a battery pack */
	#define C_PWRCORE__NUM_6P_MODULES					(18U)

	/** The number of cells in a 6P module */
	#define C_PWRCORE__NUM_CELLS_PER_6P					(6U)

	/** The number of temp sensors per 6P module */
	#define C_PWRCORE__NUM_TEMP_SNSR_PER_6P				(15U)

	/** pack location masks */
	#define C_PWRCORE__6P_LOC00_MASK						(0x01U)
	#define C_PWRCORE__6P_LOC01_MASK						(0x02U)
	#define C_PWRCORE__6P_LOC02_MASK						(0x03U)
	#define C_PWRCORE__6P_LOC03_MASK						(0x04U)
	#define C_PWRCORE__6P_LOC04_MASK						(0x05U)
	#define C_PWRCORE__6P_LOC05_MASK						(0x06U)
	#define C_PWRCORE__6P_LOC06_MASK						(0x07U)
	#define C_PWRCORE__6P_LOC07_MASK						(0x08U)
	#define C_PWRCORE__6P_LOC08_MASK						(0x09U)
	#define C_PWRCORE__6P_LOC09_MASK						(0x0AU)
	#define C_PWRCORE__6P_LOC10_MASK						(0x0BU)
	#define C_PWRCORE__6P_LOC11_MASK						(0x0CU)
	#define C_PWRCORE__6P_LOC12_MASK						(0x0DU)
	#define C_PWRCORE__6P_LOC13_MASK						(0x0EU)
	#define C_PWRCORE__6P_LOC14_MASK						(0x0FU)
	#define C_PWRCORE__6P_LOC15_MASK						(0x11U)
	#define C_PWRCORE__6P_LOC16_MASK						(0x11U)
	#define C_PWRCORE__6P_LOC17_MASK						(0x12U)

	#define C_PWRCORE__BMS_TEMP_MASK						(0x20U)

	#define C_PWRCORE__BMS_BOARD0_MASK						(0x01U)
	#define C_PWRCORE__BMS_BOARD1_MASK						(0x02U)
	#define C_PWRCORE__BMS_BOARD2_MASK						(0x03U)

	#define C_PWRCORE__6P_CELL0_MASK						(0x01U)
	#define C_PWRCORE__6P_CELL1_MASK						(0x02U)
	#define C_PWRCORE__6P_CELL2_MASK						(0x03U)

	#define C_PWRCORE__6P_POSBUS0_MASK						(0x11U)
	#define C_PWRCORE__6P_POSBUS1_MASK						(0x12U)
	#define C_PWRCORE__6P_POSBUS2_MASK						(0x13U)
	#define C_PWRCORE__6P_POSBUS3_MASK						(0x14U)
	#define C_PWRCORE__6P_POSBUS4_MASK						(0x15U)
	#define C_PWRCORE__6P_POSBUS5_MASK						(0x16U)

	#define C_PWRCORE__6P_NEGBUS0_MASK						(0x21U)
	#define C_PWRCORE__6P_NEGBUS1_MASK						(0x22U)
	#define C_PWRCORE__6P_NEGBUS2_MASK						(0x23U)
	#define C_PWRCORE__6P_NEGBUS3_MASK						(0x24U)
	#define C_PWRCORE__6P_NEGBUS4_MASK						(0x25U)
	#define C_PWRCORE__6P_NEGBUS5_MASK						(0x26U)

	//TODO confirm mapping with electrical
	#define C_PWRCORE_HOVERENGINES0_N2HET_PIN_NUMBER			(8U)
	#define C_PWRCORE_HOVERENGINES1_N2HET_PIN_NUMBER			(16U)
	#define C_PWRCORE_HOVERENGINES2_N2HET_PIN_NUMBER			(22U)
	#define C_PWRCORE_HOVERENGINES3_N2HET_PIN_NUMBER			(23U)
	#define C_PWRCORE_EDDYBRAKE0_N2HET_PIN_NUMBER				(4U)

	//TODO confirm Hover Engine Thermocouples User IDs
	#define C_PWRCORE_HOVERENGINE0_THERMOCOUPLE_USERID			(0x00U)
	#define C_PWRCORE_HOVERENGINE1_THERMOCOUPLE_USERID			(0x01U)
	#define C_PWRCORE_HOVERENGINE2_THERMOCOUPLE_USERID			(0x02U)
	#define C_PWRCORE_HOVERENGINE3_THERMOCOUPLE_USERID			(0x03U)
	#define C_PWRCORE_HOVERENGINE4_THERMOCOUPLE_USERID			(0x04U)
	#define C_PWRCORE_HOVERENGINE5_THERMOCOUPLE_USERID			(0x05U)
	#define C_PWRCORE_HOVERENGINE6_THERMOCOUPLE_USERID			(0x06U)
	#define C_PWRCORE_HOVERENGINE7_THERMOCOUPLE_USERID			(0x07U)

	//TODO confirm Eddy Brake Thermocouples User IDs
	#define C_PWRCORE_EDDYBRAKE0_THERMOCOUPLE_USERID			(0x08U)
	#define C_PWRCORE_EDDYBRAKE1_THERMOCOUPLE_USERID			(0x09U)

	#define C_PWRCORE_COOLING_WARNING_THRESHOLD					(75.0F)
	#define C_PWRCORE_COOLING_CRITICAL_THRESHOLD				(95.0F)
	#define C_PWRCORE_COOLING_EMERGENCY_THRESHOLD				(105.0F)

	#define C_PWRCORE_COOLING_500MS								(5U)
	#define C_PWRCORE_COOLING_1000MS							(10U)
	#define C_PWRCORE_COOLING_2000MS							(20U)

	#define C_PWRCORE__CURRENT_AVG_SIZE						(0x4U)

    #define C_PWRCORE__CURRENT_HASS_IPN                        (50.0F)

    /** BMS Fans time running after last discharge resistor in secs * 10 **/
    #define C_PWRCORE__BMS_FANS_TIMEOUT                         (300U)
#endif /* RLOOP_POWER_CORE__DEFINES_H_ */
