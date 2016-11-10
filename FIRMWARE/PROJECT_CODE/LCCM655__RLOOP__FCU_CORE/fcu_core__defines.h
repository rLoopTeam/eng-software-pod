/**
 * @file		FCU_CORE__DEFINES.H
 * @brief		Flight control code constatants
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__DEFINES_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__DEFINES_H_


	/** the number of brake actuators in the system */
	#define C_FCU__NUM_BRAKES								(2U)

	/** ASI command parameter addresses */
	#define C_FCU_ASI__OVER_TEMP_THRESHOLD					(90)
	#define C_FCU_ASI__FOLDBACK_STARING_TEMP				(91)
	#define C_FCU_ASI__FOLDBACK_END_TEMP					(92)
	#define C_FCU_ASI__COMMAND_SOURCE						(208)
	#define C_FCU_ASI__CONTROLLER_STATUS					(257)
	#define C_FCU_ASI__FAULTS								(258)
	#define C_FCU_ASI__CONTROLLER_TEMPERATURE				(259)
	#define C_FCU_ASI__TEMPERATURE							(261)
	#define C_FCU_ASI__MOTOR_RPM							(263)
	#define C_FCU_ASI__LAST_FAULT							(269)
	#define C_FCU_ASI__RAW_SENSOR_TEMPERATURE				(273)
	#define C_FCU_ASI__WRITE_PARAMS							(511)

	/** ASI command read or write */
	#define C_FCU_ASI__PARAM_READ							(0)
	#define C_FCU_ASI__PARAM_WRITE							(1)

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




#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__DEFINES_H_ */
