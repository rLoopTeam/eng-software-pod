/**
 * @file		MMA8451__REGISTER_DEFS.H
 * @brief		MMA8451 register definitions
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM418R0.FILE.016
 */

#ifndef _MMA8451__REGISTER_DEFS_H_
#define _MMA8451__REGISTER_DEFS_H_

/*
Name        Type        Register    Auto-Increment  Default     Comment
                        Address     Address
--------------------------------------------------------------------------------
*/
//STATUS(1)(2) R        0x00        0x01            00000000    Addresses 0x00, 0x04, 0x0B are aliases to the
//                                                              same register. Data Ready status information or
//                                                              FIFO status information.
#define C_MMA8451__REGISTER__STATUS_R           0x00


//OUT_X_MSB(1)(2) R     0x01        0x02 | 0x01     output      [7:0] are 8 MSBs of         | Root pointer to XYZ
//                                                              12-bit real-time sample.    | FIFO 8-bit data.
#define C_MMA8451__REGISTER__OUT_X_MSB_R        0x01

//OUT_Y_MSB(1)(2) R     0x02        0x03            output      [7:0] are 8 MSBs of 12-bit real-time sample
#define C_MMA8451__REGISTER__OUT_Y_MSB_R        0x03

//OUT_Z_MSB(1)(2) R     0x03        0x00            output      [7:0] are 8 MSBs of 12-bit real-time sample
#define C_MMA8451__REGISTER__OUT_Z_MSB_R        0x05

//STATUS(1)(2) R        0x04        0x05            00000000    Addresses 0x00, 0x04, 0x0B are aliases to the
//																same register. Data Ready status information or
//																FIFO status information.
#define C_MMA8451__REGISTER__STATUS2_R          0x00

//OUT_X_LSB(1)(2) R 0x05 			0x06 0x05 		output		[3:0] are 4 LSBs of			| Root pointer to XYZ
//																12-bit sample.				| FIFO 12-bit data.
#define C_MMA8451__REGISTER__OUT_X_LSB_R		0x02

//Note: There are no differences between the MSBs located in 0x01, 0x02, 0x03 and 0x06, 0x08, 0x0A.
//OUT_X_MSB(1)(2) R 0x06 			0x07 			output 		[7:0] are 8 MSBs of 12-bit real-time sample
//#define C_MMA8451__REGISTER__OUT_X_MSB2_R		0x06
//OUT_Y_LSB(1)(2) R 0x07 			0x08 output [3:0] are 4 LSBs of 12-bit real-time sample
#define C_MMA8451__REGISTER__OUT_Y_LSB_R		0x04
//OUT_Y_MSB(1)(2) R 0x08 0x09 output [7:0] are 8 MSBs of 12-bit real-time sample
//#define C_MMA8451__REGISTER__OUT_Y_MSB2_R		0x08
//OUT_Z_LSB(1)(2) R 0x09 0x0A output [3:0] are 4 LSBs of 12-bit real-time sample
#define C_MMA8451__REGISTER__OUT_Z_LSB_R		0x06
//OUT_Z_MSB(1)(2) R 0x0A 0x04 output [7:0] are 8 MSBs of 12-bit real-time sample
//#define C_MMA8451__REGISTER__OUT_Z_MSB2_R			0x0A

/*
STATUS(1)(2) R 0x0B 0x0C 00000000	Addresses 0x00, 0x04, 0x0B are aliases to the same register. Data Ready status information or FIFO status information.
OUT_X_DELTA(1)(2) R 0x0C 0x0D output 8-bit AC X-axis data
OUT_Y_DELTA(1)(2) R 0x0D 0x0E output 8-bit AC Y-axis data
OUT_Z_DELTA(1)(2) R 0x0E 0x0B output 8-bit AC Z-axis data
*/
//WHO_AM_I(1) 		R 	0x0F 		0xC6 		11000110 		NVM Programmable Fixed Device ID No.
#define C_MMA8451__REGISTER__WHO_AM_I			0x0D
/*
F_STATUS(1)(2) R 0x10 0x11 00000000 FIFO Status: No FIFO event Detected
F_8DATA(1)(2) R 0x11 0x11 Output 8-bit FIFO data
F_12DATA(1)(2) R 0x12 0x12 Output 12-bit FIFO data
F_SETUP(1)(3) R/W 0x13 0x14 00000000 FIFO setup
SYSMOD(1)(2) R 0x14 0x15 Output Current System Mode
INT_SOURCE(1)(2) R 0x15 0x16 Output Interrupt status
*/
//XYZ_DATA_CFG(1)(4) R/W 0x16 0x17 00000000 Acceleration data event flag configuration
#define C_MMA8451__REGISTER__XYZ_DATA_CFG_RW				0x0E

//HP_FILTER_CUTOFF(1)(3) R/W 0x17 0x18 00000000 Cutoff frequency is set to 4Hz @ 400Hz
#define C_MMA8451__REGISTER__HP_FILTER_CUTOFF_RW			0x0F

/*
PL_STATUS(1)(2) R 0x18 0x19 00000000 Landscape/Portrait orientation status
PL_PRE_STATUS(1)(2) R 0x19 0x1A 00000000 Landscape/Portrait previous orientation
PL_CFG(1)(4) R/W 0x1A 0x1B 10000011
Landscape/Portrait configuration.
1g Lockout offset is set to default value of 1.15g.
Debounce counters are clear during invalid
sequence condition.
PL_COUNT(1)(3) R/W 0x1B 0x1C 00000000 Landscape/Portrait debounce counter
PL_BF_ZCOMP(1)(4) R/W 0x1C 0x1D 00000010
Back-Front Trip threshold is �75�.
Z-Lockout angle is 32.14�

PL_P_L_THS_REG1(1)(4) R/W 0x1D 0x1E 00011010 Portrait-to-Landscape Trip Angle is 30�
PL_P_L_THS_REG2(1)(4) R/W 0x1E 0x1F 00100010 Portrait-to-Landscape Trip Angle is 30�
PL_P_L_THS_REG3(1)(4) R/W 0x1F 0x20 11010100 Portrait-to-Landscape Trip Angle is 30�
PL_L_P_THS_REG1(1)(4) R/W 0x20 0x21 00101101 Landscape-to-Portrait Trip Angle is 60�
PL_L_P_THS_REG2(1)(4) R/W 0x21 0x22 01000001 Landscape-to-Portrait Trip Angle is 60�
PL_L_P_THS_REG3(1)(4) R/W 0x22 0x23 10100010 Landscape-to-Portrait Trip Angle is 60�
FF_MT_CFG_1(1)(4) R/W 0x23 0x24 00000000 Freefall/Motion1 configuration
FF_MT_SRC_1(1)(2) R 0x24 0x25 00000000 Freefall/Motion1 event source register
FF_MT_THS_1(1)(3) R/W 0x25 0x26 00000000 Freefall/Motion1 threshold register
FF_MT_COUNT_1(1)(3) R/W 0x26 0x27 00000000 Freefall/Motion1 debounce counter
FF_MT_CFG_2(1)(4) R/W 0x27 0x28 00000000 Freefall/Motion2 configuration
FF_MT_SRC_2(1)(2) R 0x28 0x29 00000000 Freefall/Motion2 event source register
FF_MT_THS_2(1)(3) R/W 0x29 0x2A 00000000 Freefall/Motion2 threshold register
FF_MT_COUNT_2(1)(3) R/W 0x2A 0x2B 00000000 Freefall/Motion2 debounce counter
TRANSIENT_CFG(1)(4) R/W 0x2B 0x2C 00000000 Transient configuration
TRANSIENT_SRC(1)(2) R 0x2C 0x2D 00000000 Transient event status register
TRANSIENT_THS(1)(3) R/W 0x2D 0x2E 00000000 Transient event threshold
TRANSIENT_COUNT(1)(3) R/W 0x2E 0x2F 00000000 Transient debounce counter
PULSE_CFG(1)(4) R/W 0x2F 0x30 00000000 ELE, Double_XYZ or Single_XYZ
PULSE_SRC(1)(2) R 0x30 0x31 00000000 EA, Double_XYZ or Single_XYZ
PULSE_THSX(1)(3) R/W 0x31 0x32 00000000 X pulse threshold
PULSE_THSY(1)(3) R/W 0x32 0x33 00000000 Y pulse threshold
PULSE_THSZ(1)(3) R/W 0x33 0x34 00000000 Z pulse threshold
PULSE_TMLT(1)(4) R/W 0x34 0x35 00000000 Time limit for pulse
PULSE_LTCY(1)(4) R/W 0x35 0x36 00000000 Latency time for 2nd pulse
PULSE_WIND(1)(4) R/W 0x36 0x37 00000000 Window time for 2nd pulse
ASLP_COUNT(1)(4) R/W 0x37 0x38 00000000 Counter setting for auto-sleep
CTRL_REG1(1)(4) R/W 0x38 0x39 00000000 ODR = 400 Hz, Standby Mode.
*/
#define C_MMA8451__REGISTER__CTRL_REG1_RW		0x2A

//CTRL_REG2(1)(4) R/W 0x39 0x3A 00000000	ST = Disabled, SLPE = Disabled,MODS = Normal mode.
#define C_MMA8451__REGISTER__CTRL_REG2_RW		0x2B

//CTRL_REG3(1)(4) R/W 0x3A 0x3B 00000000 IPOL, PP_OD
#define C_MMA8451__REGISTER__CTRL_REG3_RW		0x2C

//CTRL_REG4(1)(4) R/W 0x3B 0x3C 00000000 Interrupt enable register
#define C_MMA8451__REGISTER__CTRL_REG4_RW		0x2D

//CTRL_REG5(1)(4) R/W 0x3C 0x3D 00000000 Interrupt pin (INT1/INT2) map configuration
#define C_MMA8451__REGISTER__CTRL_REG5_RW		0x2E

//OFF_X(1)(4) R/W 0x3D 0x3E 00000000 X-axis offset adjust
#define C_MMA8451__REGISTER__OFF_X_RW		0x2F
//OFF_Y(1)(4) R/W 0x3E 0x3F 00000000 Y-axis offset adjust
#define C_MMA8451__REGISTER__OFF_Y_RW		0x30
//OFF_Z(1)(4) R/W 0x3F 0x0F 00000000 Z-axis offset adjust
#define C_MMA8451__REGISTER__OFF_Z_RW		0x31


#endif //




