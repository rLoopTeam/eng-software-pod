/**
 * @file		FCU_CORE__DEFINES.H
 * @brief		Flight control code constants
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
#ifndef _FCU_CORE__DEFINES_H_
#define _FCU_CORE__DEFINES_H_


	/** the number of brake actuators in the system */
	#define C_FCU__NUM_BRAKES								(2U)

	/** 2 Accel devices on the PCB - DO NOT CHANGE */
	#define C_FCU__NUM_ACCEL_CHIPS							(2U)

		/** Accel filtering window */
		#define C_FCU__ACCEL_FILTER_WINDOW					(8U)

	/** Hover Engines */
	#define C_FCU__NUM_HOVER_ENGINES						(8U)

	//laser orientation code defines
	#define LASER_ORIENT__X 0U
	#define LASER_ORIENT__Y 1U
	#define LASER_ORIENT__Z 2U
	#define LASER_ORIENT__A 0U
	#define LASER_ORIENT__B 1U
	#define LASER_ORIENT__C 2U
	#define LASER_ORIENT__D 3U

	/** Number of lasers facing down to the ground */
	#define C_FCU__NUM_LASERS_GROUND						(4U)

	/** number of lasers for the i-beam */
	#define C_FCU__NUM_LASERS_IBEAM							(2U)

	/** Total number of Laser OptoNCDT's*/
	#define C_FCU__NUM_LASERS_OPTONCDT						(C_FCU__NUM_LASERS_GROUND + C_FCU__NUM_LASERS_IBEAM)

	/** number of lasers for the constrast detection system */
	#define C_FCU__NUM_LASERS_CONTRAST						(3U)

	//Opto NCDT indexes
	#define C_FCU__SC16_OPTO_FL_INDEX						(0U)
	#define C_FCU__SC16_OPTO_FR_INDEX						(1U)
	#define C_FCU__SC16_OPTO_RL_INDEX						(2U)
	#define C_FCU__SC16_OPTO_RR_INDEX						(3U)
	#define C_FCU__SC16_OPTO_YAWF_INDEX						(4U)
	#define C_FCU__SC16_OPTO_YAWR_INDEX						(5U)

	//fwd looking laser
	#define C_FCU__SC16_FWD_LASER_INDEX						(6U)


	/** The SC16 device index for the ASI interface*/
	#define C_FCU__SC16_ASI_INDEX							(7U)

	/** max number of commands in the round robbin list */
	#define C_FCU__ASI_COMMAND_LIST_MAX						(4U)

	/** The max number of contrast laser stripes in the tube
	 * 1 Mile Tube = 5280ft
	 * Spacing = 100ft
	 * Stripes = 53 + 2 spare
	 *  */
	#define C_FCU__LASER_CONTRAST__MAX_STRIPES				(55U)


	/** Min brakes I-Beam Distance */
	#define C_FCU__BRAKES__MIN_IBEAM_DIST_MM				(2.5F)

	#define C_FCU__BRAKES__MAX_IBEAM_DIST_MM				(22.0F)


	/** Number of geometry items */
	#define C_FCU__GEOM__NUM_ITEMS_F32						(8U)
	#define C_FCU__GEOM__NUM_ITEMS_S32						(8U)

	/** Navigation function constants */
	#define C_FCU__NAV_POD_MIN_X_POS							(500U)	//define exact value
	#define C_FCU__NAV_MAX_UNLIFTED_HEIGHT					(10U) 	//define exact value
	#define C_FCU__NAV_PODSPEED_STANDBY						(1U) 	//define exact value
	#define C_FCU__NAV_PODSPEED_MAX_SPEED_TO_STABILIZE		(1000000U) //define exact value. ATM extra large so that HE never throttle down
	#define C_FCU__NAV_MIN_PUSHER_SPEED						(10U)	//define exact value

	/** State Machine constants */
	#define C_FCU__MAINSM_PUSHER_RELEASE_DELAY				(10U) 	//define exact value

	/** GS Communication constants */
	#define C_FCU__GS_COMM_LOSS_DELAY						(1U)		//define exact value

	/** Pod Position constants */
	#define C_FCU__POD_TARGET_POINT_MARGIN_POS				(16U)
	#define C_FCU__POD_STOP_X_POS							(1600U)	//define exact value

	/** State Machine constants */
	#define C_FCU__LIFTMECH_RETRACTED_MLP_DISTANCE			(30U)	//define exact value
	#define C_FCU__LIFTMECH_ACTUATOR_NOM_UNLIFT_SPEED			(30U)	//define exact value
	/** Laser Orientation constants */
	#define C_FCU__LASERORIENT_MAX_UNLIFTED_HEIGHT			(10U)	//define exact value
	#define C_FCU__LASERORIENT_MIN_LIFTED_HEIGHT				(10U)	//define exact value
	#define C_FCU__LASERORIENT_MIN_RUN_MODE_HEIGHT			(5U)		//define exact value

	/** Hover Engines Parameters */
	#define C_FCU__HE_STATIC_HOVER_RPM                     (2000U)   //hover engine nominal RPM speed
	#define C_FCU__HE_CRUISE_RPM                           (2000U)   //hover engine cruise RPM speed
	#define C_FCU__HE_RPM_TOLERANCE                         (500U)   //hover engine maximum allowed RPM speed douring hovering
	#define C_FCU__HE_MAX_CURRENT                            (10U)   //hover engine maximum allowed current TO BE CHECKED IF EXISTS
	#define C_FCU__HE_MIN_CURRENT                             (1U)   //hover engine minimum allowed current
	#define C_FCU__HE_MAX_VOLTAGE                        (100000U)   //define exact value
	#define C_FCU__HE_MIN_VOLTAGE                             (1U)   //define exact value
	#define C_FCU__HE_MAX_TEMPERATURE                        (95U)   //critical hover engine temperature

	/**Eddy Brakes Parameters */
	#define C_FCU__EDDYBRAKES_STEPPER_MOTOR_MAX_TEMP			(90U)	//define exact value
	#define C_FCU__EDDYBRAKES_NOM_APPL_SPEED					(1U)		//define exact value
	#define C_FCU__EDDYBRAKES_APPL_MLP_DISTANCE				(1U)		//define exact value
	#define C_FCU__EDDYBRAKES_NOM_RELEASE_SPEED				(1U)		//define exact value
	#define C_FCU__EDDYBRAKES_RELEASE_MLP_DISTANCE			(1U)		//define exact value

	#define C_FCU__LIFTMECH_ACTUATOR_NOM_UNLIFT_SPEED			(10U)	//define exact value


#endif /* _FCU_CORE__DEFINES_H_ */
