#ifndef _LCCM418__00__FAULT_FLAGS_H_
#define _LCCM418__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * GENERAL 
 * 
 * A general fault has occurred. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * SENSOR INDEX NOT FOUND 
 * 
 * The software tried to address a sensor whos index was not found.
This is 
 * a programming fault. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * DEVICE NOT WORKING 
 * 
 * The device's ID could not be detected during power up.
This can be a result 
 * of a faulty I2C bus, or a device fault. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * STATUS REGISTER READ FAIL
 
 * 
 * The status register could not be read, due to an I2C timeout or other device 
 * problem.
 
*/
#define C_LCCM418__CORE__FAULT_INDEX__03				0x00000003U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__03			0x00000008U

/*
 * @fault_index
 * 04
 * 
 * @brief
 * INTERRUPT LOST 
 * 
 * The device started up in interrupt mode, however no interrupts were received 
 * after a time period. Indicating a device or CPU issue. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__04				0x00000004U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__04			0x00000010U

/*
 * @fault_index
 * 05
 * 
 * @brief
 * UNABLE TO CALIBRATE 
 * 
 * An attempt was made to enter calibration mode, but this failed. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__05				0x00000005U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__05			0x00000020U

/*
 * @fault_index
 * 06
 * 
 * @brief
 * RESET CALIBRATION DATA 
 * 
 * Calibration data had to be re-zerod and re-loaded from memory
This fault 
 * is typical after device programming. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__06				0x00000006U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__06			0x00000040U

/*
 * @fault_index
 * 07
 * 
 * @brief
 * CAL DATA CRC FAULT 
 * 
 * The calibration data has a CRC fault. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__07				0x00000007U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__07			0x00000080U

/*
 * @fault_index
 * 08
 * 
 * @brief
 * CALIBRATION IN PROGRESS 
 * 
 * This is an on/off flag without setting the general flag. In the field this 
 * should never happen. 
*/
#define C_LCCM418__CORE__FAULT_INDEX__08				0x00000008U
#define C_LCCM418__CORE__FAULT_INDEX_MASK__08			0x00000100U

#endif //#ifndef _LCCM418__FAULT_FLAGS_H_

