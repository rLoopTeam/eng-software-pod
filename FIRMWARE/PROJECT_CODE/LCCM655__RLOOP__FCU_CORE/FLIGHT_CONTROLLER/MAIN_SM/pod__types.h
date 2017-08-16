#ifndef _POD__TYPES_H_
#define _POD__TYPES_H_

// #include "../COMPAT.h"
#include "../../state_machine.h"


/*  Now in fcu_core__types.h
/////////////////////////////////////////////////////////////////////
//  Pod States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    POD_NULL_STATE = 0U,
    POD_INIT_STATE,
    POD_IDLE_STATE,
    POD_TEST_MODE_STATE,
    POD_DRIVE_STATE,
    POD_ARMED_WAIT_STATE,
    POD_FLIGHT_PREP_STATE,
    POD_READY_STATE,
    POD_ACCEL_STATE,
    POD_COAST_INTERLOCK_STATE,
    POD_BRAKE_STATE,
    POD_SPINDOWN_STATE
} E_POD_STATE_T;
#define E_POD_STATE_N 12

// Pod state lookup
static char *pod_state_lookup[] =
{
    "POD_NULL_STATE",
    "POD_INIT_STATE",
    "POD_IDLE_STATE",
    "POD_TEST_MODE_STATE",
    "POD_DRIVE_STATE",
    "POD_ARMED_WAIT_STATE",
    "POD_FLIGHT_PREP_STATE",
    "POD_READY_STATE",
    "POD_ACCEL_STATE",
    "POD_COAST_INTERLOCK_STATE",
    "POD_BRAKE_STATE",
    "POD_SPINDOWN_STATE"
};

// Pod state lookup function
static inline const char * lookup_pod_state(const E_POD_STATE_T state)
{
    return pod_state_lookup[state];
};


/////////////////////////////////////////////////////////////////////
//  Pod Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    POD_NO_CMD = 0U,
    POD_IDLE,
    POD_TEST_MODE,
    POD_DRIVE,
    POD_FLIGHT_PREP,
    POD_ARMED_WAIT,
    POD_READY

} E_POD_COMMAND_T;
#define E_POD_COMMAND_N 7

// Pod command lookup
static char *pod_command_lookup[] = 
{
    "POD_NO_CMD",
    "POD_IDLE",
    "POD_TEST_MODE",
    "POD_DRIVE",
    "POD_FLIGHT_PREP",
    "POD_ARMED_WAIT",
    "POD_READY"
};

// Pod command lookup function
static inline const char * lookup_pod_command(const E_POD_COMMAND_T command)
{
    return pod_command_lookup[command];
};
*/

/////////////////////////////////////////////////////////////////////
//  Pod command struct
/////////////////////////////////////////////////////////////////////
/* now in fcu_core.h
typedef struct 
{
    // Command
    E_POD_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        
    
    } args;

} strPodCmd;

*/

/////////////////////////////////////////////////////////////////////
//  Pod struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
/** @todo: make sure this is in sFCU (named sPodStateMachine)
typedef struct 
{
    // Internal command (first priority)
    strPodCmd internal_command;

    // External command (second priority)
    strPodCmd external_command;

    StateMachine sm;
    
    // Determine if the subsystem will accept commands
    bool enabled;

    // Index of this subsystem in its parent. Defaults to 0 for single-instance subsystems.
    int index;

    #if DEBUG == 1U
        // For debug printing
        char name[32];  
        char absname[64];
    #endif


    // Timers and timeouts
    // Ready state to Idle backup timeout
    strTimer ReadyExpiredBackupTimeout;
    
    // Accel to Coast Interlock backup timeout
    strTimer AccelBackupTimeout;
    
    // Coast interlock timeout
    strTimer CoastInterlockTimeout;
    
    // Brake to Spindown backup timeout
    strTimer BrakeToSpindownBackupTimeout;
    
    // Spindown to Idle backup timeout
    strTimer SpindownToIdleBackupTimeout;

} strPod;
*/

/////////////////////////////////////////////////////////////////////
//  Pod Allowable commands per state
/////////////////////////////////////////////////////////////////////
/*
static const Luint8 pod_allowed_state_commands[E_POD_STATE_N][E_POD_COMMAND_N] = 
{
    [POD_IDLE_STATE][POD_TEST_MODE] = 1,
    [POD_IDLE_STATE][POD_ARMED_WAIT] = 1,
    [POD_IDLE_STATE][POD_DRIVE] = 1,
    [POD_IDLE_STATE][POD_IDLE] = 1,
    [POD_TEST_MODE_STATE][POD_IDLE] = 1,
    [POD_TEST_MODE_STATE][POD_TEST_MODE] = 1,
    [POD_DRIVE_STATE][POD_IDLE] = 1,
    [POD_DRIVE_STATE][POD_DRIVE] = 1,
    [POD_ARMED_WAIT_STATE][POD_IDLE] = 1,
    [POD_ARMED_WAIT_STATE][POD_FLIGHT_PREP] = 1,
    [POD_ARMED_WAIT_STATE][POD_ARMED_WAIT] = 1,
    [POD_FLIGHT_PREP_STATE][POD_ARMED_WAIT] = 1,
    [POD_FLIGHT_PREP_STATE][POD_READY] = 1,
    [POD_FLIGHT_PREP_STATE][POD_FLIGHT_PREP] = 1,
    [POD_READY_STATE][POD_FLIGHT_PREP] = 1,
    [POD_READY_STATE][POD_READY] = 1
};

static inline const bool pod_state_allows_command(const E_POD_STATE_T state, const E_POD_COMMAND_T command)
{
    return pod_allowed_state_commands[state][command];
};
*/

/////////////////////////////////////////////////////////////////////
//  Pod target states by current state+command
/////////////////////////////////////////////////////////////////////
/*
static const Luint8 pod_state_command_target_state[E_POD_STATE_N][E_POD_COMMAND_N] = {
    [POD_IDLE_STATE][POD_TEST_MODE] = POD_TEST_MODE_STATE,
    [POD_IDLE_STATE][POD_ARMED_WAIT] = POD_ARMED_WAIT_STATE,
    [POD_IDLE_STATE][POD_DRIVE] = POD_DRIVE_STATE,
    [POD_TEST_MODE_STATE][POD_IDLE] = POD_IDLE_STATE,
    [POD_DRIVE_STATE][POD_IDLE] = POD_IDLE_STATE,
    [POD_ARMED_WAIT_STATE][POD_IDLE] = POD_IDLE_STATE,
    [POD_ARMED_WAIT_STATE][POD_FLIGHT_PREP] = POD_FLIGHT_PREP_STATE,
    [POD_FLIGHT_PREP_STATE][POD_ARMED_WAIT] = POD_ARMED_WAIT_STATE,
    [POD_FLIGHT_PREP_STATE][POD_READY] = POD_READY_STATE,
    [POD_READY_STATE][POD_FLIGHT_PREP] = POD_FLIGHT_PREP_STATE
};

static inline const E_POD_STATE_T get_pod_target_state(const E_POD_STATE_T current_state, const E_POD_COMMAND_T command)
{
    return pod_state_command_target_state[current_state][command];
}
*/

#endif // _POD__TYPES_H_
