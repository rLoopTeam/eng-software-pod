
#ifndef _FCU__ASI_DEFINES_H_
#define _FCU__ASI_DEFINES_H_

	/** Always use this because we are using a mux */
	#define C_ASI__DEFAULT_SLAVE_ADDX			(1U)

	// max modbus frame size
	#define C_ASI__MAX_FRAME_SIZE				(256)




	// modbus function codes
	//#define C_ASI__READ_INPUT_REGISTER			(0x04)
	//#define C_ASI__WRITE_SINGLE_REGISTER		(0x06)

	// modbus timers in 10 ms units
	#define C_ASI__MAX_TURNAROUND_DELAY			(15)
	#define C_ASI__MAX_REPLYWAIT_DELAY			(100)

	// sw test: simulate low level response
	//#define C_ASI__SW_TEST


	/** ASI controller faults bit array*/
	#define C_FCU_ASI__CONTROLLER_OVER_VOLTAGE				(OX0001)
	#define C_FCU_ASI__PHASE_OVER_CURRENT					(OX0002)
	#define C_FCU_ASI__CURRENT_SENSOR_CALIBRATION			(OX0004)
	#define C_FCU_ASI__CURRENT_SENSOR_OVER_CURRENT			(OX0008)
	#define C_FCU_ASI__CONTROLLER_TEMPERATURE				(OX0010)
	#define C_FCU_ASI__PARAMETER_CRC_32						(OX0020)
	#define C_FCU_ASI__CONTROLLER_UNDER_VOLTAGE				(OX0040)
	#define C_FCU_ASI__BRIDGE_OPEN_CIRCUIT					(OX0080)
	#define C_FCU_ASI__COMMUNICATION_TIMEOUT				(OX0100)
	#define C_FCU_ASI__INSTANTANEOUS_PHASE_CURRENT			(OX0200)
	#define C_FCU_ASI__MOTOR_TEMPERATURE					(OX0400)
	#define C_FCU_ASI__THROTTLE_OUTSIDE_VOLTAGE_RANGE		(OX0800)
	#define C_FCU_ASI__FAST_DC_OVER_VOLTAGE					(OX1000)
	#define C_FCU_ASI__INTERNAL_ERROR						(OX2000)
	#define C_FCU_ASI__BRIDGE_TURN_ON_TEST					(OX4000)
	#define C_FCU_ASI__FAST_DC_VOLTAGE						(OX8000)

#endif /* _FCU__ASI_DEFINES_H_ */
