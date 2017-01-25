/*
 * power_core__defines.h
 *
 *  Created on: 28 Dec 2016
 *      Author: Lachlan
 */

#ifndef RLOOP_POWER_CORE__DEFINES_H_
#define RLOOP_POWER_CORE__DEFINES_H_


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

	#define C_PWRCORE__CURRENT_AVG_SIZE						(0x4U)
#endif /* RLOOP_POWER_CORE__DEFINES_H_ */
