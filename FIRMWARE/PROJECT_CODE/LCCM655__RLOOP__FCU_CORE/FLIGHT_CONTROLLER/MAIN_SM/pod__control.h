#ifndef _POD__CONTROL_H_
#define _POD__CONTROL_H_


/////////////////////////////////////////////////////////////////////
//  Pod guard/check functions
/////////////////////////////////////////////////////////////////////
 
/**
 * pod_init_complete
 */
bool pod_init_complete();

/**
 * armed_wait_checks_ok
 */
bool armed_wait_checks_ok();

/**
 * drive_checks_ok
 */
bool drive_checks_ok();

/**
 * flight_prep_checks_ok
 */
bool flight_prep_checks_ok();

/**
 * flight_readiness_checks_ok
 */
bool flight_readiness_checks_ok();

/**
 * accel_confirmed
 */
bool accel_confirmed();

/**
 * pusher_separation_confirmed
 */
bool pusher_separation_confirmed();

/**
 * pod_stop_confirmed
 */
bool pod_stop_confirmed();

/**
 * spindown_complete_confirmed
 */
bool spindown_complete_confirmed();


/////////////////////////////////////////////////////////////////////
//  Pod state transition functions
/////////////////////////////////////////////////////////////////////

/**
 * Pod POD_INIT_STATE transition handler
 */
void handle_POD_INIT_STATE_transitions();

/**
 * Pod POD_IDLE_STATE transition handler
 */
void handle_POD_IDLE_STATE_transitions();

/**
 * Pod POD_TEST_MODE_STATE transition handler
 */
void handle_POD_TEST_MODE_STATE_transitions();

/**
 * Pod POD_DRIVE_STATE transition handler
 */
void handle_POD_DRIVE_STATE_transitions();

/**
 * Pod POD_ARMED_WAIT_STATE transition handler
 */
void handle_POD_ARMED_WAIT_STATE_transitions();

/**
 * Pod POD_FLIGHT_PREP_STATE transition handler
 */
void handle_POD_FLIGHT_PREP_STATE_transitions();

/**
 * Pod POD_READY_STATE transition handler
 */
void handle_POD_READY_STATE_transitions();

/**
 * Pod POD_ACCEL_STATE transition handler
 */
void handle_POD_ACCEL_STATE_transitions();

/**
 * Pod POD_COAST_INTERLOCK_STATE transition handler
 */
void handle_POD_COAST_INTERLOCK_STATE_transitions();

/**
 * Pod POD_BRAKE_STATE transition handler
 */
void handle_POD_BRAKE_STATE_transitions();

/**
 * Pod POD_SPINDOWN_STATE transition handler
 */
void handle_POD_SPINDOWN_STATE_transitions();


/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Transition to POD_IDLE
 */
void cmd_POD_IDLE();

/**
 *  Transition to POD_TEST_MODE
 */
void cmd_POD_TEST_MODE();

/**
 *  Transition to POD_DRIVE
 */
void cmd_POD_DRIVE();

/**
 *  Transition to POD_FLIGHT_PREP
 */
void cmd_POD_FLIGHT_PREP();

/**
 *  Transition to POD_ARMED_WAIT
 */
void cmd_POD_ARMED_WAIT();

/**
 *  Transition to POD_READY
 */
void cmd_POD_READY();


#endif // _POD__CONTROL_H_
