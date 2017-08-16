#include "pod__control.h"
#include "pod__types.h"
#include "../../fcu_core.h"
#include "../../timers.h"
#include "../../state_machine.h"


extern struct _strFCU sFCU;


/////////////////////////////////////////////////////////////////////
//  Pod transition and command guard functions
/////////////////////////////////////////////////////////////////////

bool pod_init_complete()
{
    // @todo: implement
    return false;
}

bool armed_wait_checks_ok()
{
    // @todo: implement
    return false;
}

bool drive_checks_ok()
{
    // @todo: implement
    return false;
}

bool flight_prep_checks_ok()
{
    // @todo: implement
    return false;
}

bool flight_readiness_checks_ok()
{
    // @todo: implement
    return false;
}

bool accel_confirmed()
{
    // @todo: implement
    return false;
}

bool pusher_separation_confirmed()
{
    // @todo: implement
    return false;
}

bool pod_stop_confirmed()
{
    // @todo: implement
    return false;
}

bool spindown_complete_confirmed()
{
    // @todo: implement
    return false;
}


/////////////////////////////////////////////////////////////////////
//  Pod state transition handling
/////////////////////////////////////////////////////////////////////


void handle_POD_INIT_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_INIT_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check conditionals (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( pod_init_complete() )
        {
            sm->state = POD_IDLE_STATE;
        } 
        else
        {
            // fall on
        }
    }


}

void handle_POD_IDLE_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_IDLE_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_TEST_MODE:
                sm->state = POD_TEST_MODE_STATE;
                break;
            
            case POD_ARMED_WAIT:
                if ( armed_wait_checks_ok() )
                {
                    sm->state = POD_ARMED_WAIT_STATE;
                } 
                else 
                {
                    #if DEBUG == 1U
                    printf("%s -- REJECTING COMMAND %s in state %s: failed armed_wait_checks_ok() check", sPod->absname, lookup_pod_command(POD_ARMED_WAIT), lookup_pod_state(POD_IDLE_STATE));
                    #endif
                }
                break;
            
            case POD_DRIVE:
                if ( drive_checks_ok() )
                {
                    sm->state = POD_DRIVE_STATE;
                } 
                else 
                {
                    #if DEBUG == 1U
                    printf("%s -- REJECTING COMMAND %s in state %s: failed drive_checks_ok() check", sPod->absname, lookup_pod_command(POD_DRIVE), lookup_pod_state(POD_IDLE_STATE));
                    #endif
                }
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    

}

void handle_POD_TEST_MODE_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_TEST_MODE_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_IDLE:
                sm->state = POD_IDLE_STATE;
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    

}

void handle_POD_DRIVE_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_DRIVE_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_IDLE:
                sm->state = POD_IDLE_STATE;
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    

}

void handle_POD_ARMED_WAIT_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_ARMED_WAIT_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_IDLE:
                sm->state = POD_IDLE_STATE;
                break;
            
            case POD_FLIGHT_PREP:
                if ( flight_prep_checks_ok() )
                {
                    sm->state = POD_FLIGHT_PREP_STATE;
                } 
                else 
                {
                    #if DEBUG == 1U
                    printf("%s -- REJECTING COMMAND %s in state %s: failed flight_prep_checks_ok() check", sPod->absname, lookup_pod_command(POD_FLIGHT_PREP), lookup_pod_state(POD_ARMED_WAIT_STATE));
                    #endif
                }
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    

}

void handle_POD_FLIGHT_PREP_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_FLIGHT_PREP_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_ARMED_WAIT:
                sm->state = POD_ARMED_WAIT_STATE;
                break;
            
            case POD_READY:
                if ( flight_readiness_checks_ok() )
                {
                    sm->state = POD_READY_STATE;
                } 
                else 
                {
                    #if DEBUG == 1U
                    printf("%s -- REJECTING COMMAND %s in state %s: failed flight_readiness_checks_ok() check", sPod->absname, lookup_pod_command(POD_READY), lookup_pod_state(POD_FLIGHT_PREP_STATE));
                    #endif
                }
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    

}

void handle_POD_READY_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_READY_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check commands (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        // Handle commands
        switch(command) {
            
            case POD_FLIGHT_PREP:
                sm->state = POD_FLIGHT_PREP_STATE;
                break;
        
            default:
                // Nothing to do
                break;
        }
    }
    
    // Check conditionals (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( accel_confirmed() )
        {
            sm->state = POD_ACCEL_STATE;
        } 
        else
        {
            // fall on
        }
    }

    // Check timeouts (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( timeout_expired(&sFCU.sPodStateMachine.ReadyExpiredBackupTimeout) ) 
        {
            sm->state = POD_IDLE_STATE;
        } 
        else 
        {
            // fall on
        }
    }

}

void handle_POD_ACCEL_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_ACCEL_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check conditionals (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( pusher_separation_confirmed() )
        {
            sm->state = POD_COAST_INTERLOCK_STATE;
        } 
        else
        {
            // fall on
        }
    }

    // Check timeouts (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( timeout_expired(&sFCU.sPodStateMachine.AccelBackupTimeout) ) 
        {
            sm->state = POD_COAST_INTERLOCK_STATE;
        } 
        else 
        {
            // fall on
        }
    }

}

void handle_POD_COAST_INTERLOCK_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_COAST_INTERLOCK_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check timeouts (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( timeout_expired(&sFCU.sPodStateMachine.CoastInterlockTimeout) ) 
        {
            sm->state = POD_BRAKE_STATE;
        } 
        else 
        {
            // fall on
        }
    }

}

void handle_POD_BRAKE_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_BRAKE_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check conditionals (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( pod_stop_confirmed() )
        {
            sm->state = POD_SPINDOWN_STATE;
        } 
        else
        {
            // fall on
        }
    }

    // Check timeouts (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( timeout_expired(&sFCU.sPodStateMachine.BrakeToSpindownBackupTimeout) ) 
        {
            sm->state = POD_SPINDOWN_STATE;
        } 
        else 
        {
            // fall on
        }
    }

}

void handle_POD_SPINDOWN_STATE_transitions()
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    // Convenience
    E_POD_STATE_T state = POD_SPINDOWN_STATE;
    E_POD_COMMAND_T command = sm->command.command;

    // Check conditionals (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( spindown_complete_confirmed() )
        {
            sm->state = POD_IDLE_STATE;
        } 
        else
        {
            // fall on
        }
    }

    // Check timeouts (if we aren't already transitioning)
    if ( ! sm_transitioning(sm) )
    {
        if ( timeout_expired(&sFCU.sPodStateMachine.SpindownToIdleBackupTimeout) ) 
        {
            sm->state = POD_IDLE_STATE;
        } 
        else 
        {
            // fall on
        }
    }

}


// @todo: get rid of everything below here

/////////////////////////////////////////////////////////////////////
//  Pod command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
/*
bool handle_pod_conditional_transition(strPod *sPod)
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;

    bool transitioning;

    switch(sm->state) {  // Current state
        case POD_INIT_STATE:
            if ( pod_init_complete(sPod) ) 
            {
                sm->state = POD_IDLE_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_READY_STATE:
            if ( accel_confirmed(sPod) ) 
            {
                sm->state = POD_ACCEL_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_ACCEL_STATE:
            if ( pusher_separation_confirmed(sPod) ) 
            {
                sm->state = POD_COAST_INTERLOCK_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_BRAKE_STATE:
            if ( pod_stop_confirmed(sPod) ) 
            {
                sm->state = POD_SPINDOWN_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_SPINDOWN_STATE:
            if ( spindown_complete_confirmed(sPod) ) 
            {
                sm->state = POD_IDLE_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;

        default:
            // Do nothing
            break;

    }
    
    return transitioning;
}
*/

// Handle timeout transitions
// Return whether or not we're transitioning
/*
bool handle_pod_timeout_transition(strPod *sPod)
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;
    
    bool transitioning;

    switch(sm->state) {  // Current state
        case POD_READY_STATE:
            if ( timeout_expired(&sFCU.sPodStateMachine.ReadyExpiredBackupTimeout) ) 
            {
                sm->state = POD_IDLE_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_ACCEL_STATE:
            if ( timeout_expired(&sFCU.sPodStateMachine.AccelBackupTimeout) ) 
            {
                sm->state = POD_COAST_INTERLOCK_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_COAST_INTERLOCK_STATE:
            if ( timeout_expired(&sFCU.sPodStateMachine.CoastInterlockTimeout) ) 
            {
                sm->state = POD_BRAKE_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_BRAKE_STATE:
            if ( timeout_expired(&sFCU.sPodStateMachine.BrakeToSpindownBackupTimeout) ) 
            {
                sm->state = POD_SPINDOWN_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;
        
        case POD_SPINDOWN_STATE:
            if ( timeout_expired(&sFCU.sPodStateMachine.SpindownToIdleBackupTimeout) ) 
            {
                sm->state = POD_IDLE_STATE;
                transitioning = true;
            } else {
                transitioning = false;
            }
            break;

        default:
            // No timeouts were tripped, so we're not transitioning
            transitioning = false;
            break;

    }
    
    return transitioning;
}
*/

// Handle automatic transitions
// Return whether or not we're transitioning
/*
bool handle_pod_automatic_transition(strPod *sPod)
{
    // No automatic transitions to handle
    return false;
} 
*/

/////////////////////////////////////////////////////////////////////
//  Pod command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
/*
bool handle_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot)
{

/////////////////////////////////////////////////////////////////////
//  Order of operations:
//  1. Check to see if the command is allowed in our current state
//  2. Check any guards that may prevent a command from executing. 
//     Note: some state/command combinations have guards, some do not.
//  3. If the command has passed all of our checks, perform a state
//     change if there's one associated with the command/state combo,
//     and update any variables etc. based on the command arguments.
/////////////////////////////////////////////////////////////////////    

    #if DEBUG == 1U
        // printf("Handling command in handle_pod_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == POD_NO_CMD)
    {
        return false;
    } 
    else 
    {
        // fall on
    }    

    E_POD_STATE_T state = sPod->sm.state;
    E_POD_COMMAND_T command = cmd->command;

    bool exec_command = true;

    //  1. Check to see if the command is allowed in our current state
    if (pod_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        if (state == POD_IDLE_STATE && command == POD_ARMED_WAIT)
        {
            if ( armed_wait_checks_ok(sPod) )
            {
                exec_command = true;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed armed_wait_checks_ok() check", sPod->absname, lookup_pod_command(POD_ARMED_WAIT), lookup_pod_state(POD_IDLE_STATE));
                #endif
                exec_command = false;
            }
        }
        else if (state == POD_IDLE_STATE && command == POD_DRIVE)
        {
            if ( drive_checks_ok(sPod) )
            {
                exec_command = true;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed drive_checks_ok() check", sPod->absname, lookup_pod_command(POD_DRIVE), lookup_pod_state(POD_IDLE_STATE));
                #endif
                exec_command = false;
            }
        }
        else if (state == POD_ARMED_WAIT_STATE && command == POD_FLIGHT_PREP)
        {
            if ( flight_prep_checks_ok(sPod) )
            {
                exec_command = true;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed flight_prep_checks_ok() check", sPod->absname, lookup_pod_command(POD_FLIGHT_PREP), lookup_pod_state(POD_ARMED_WAIT_STATE));
                #endif
                exec_command = false;
            }
        }
        else if (state == POD_FLIGHT_PREP_STATE && command == POD_READY)
        {
            if ( flight_readiness_checks_ok(sPod) )
            {
                exec_command = true;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed flight_readiness_checks_ok() check", sPod->absname, lookup_pod_command(POD_READY), lookup_pod_state(POD_FLIGHT_PREP_STATE));
                #endif
                exec_command = false;
            }
        }
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sPod->absname, lookup_pod_command(command), lookup_pod_state(state));
        #endif
        
        // Command not allowed in this state
        exec_command = false;
    }
    
    
    //  3. If we've passed all of our checks, handle state changes and command args

    if (exec_command) 
    {
        /////////////////////////////////////////////////////////////////////
        //  Handle state transition if one is associated with the 
        //  state/command combination
        /////////////////////////////////////////////////////////////////////
        E_POD_STATE_T target_state = get_pod_target_state(state, command);
        if ( target_state != POD_NULL_STATE )
        {
            sPod->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sPod->absname, lookup_pod_command(command), lookup_pod_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_pod_command(sPod, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_pod_command(sPod, cmd, "handle_pod_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot)
{
    // Update variables as needed based on command arguments
    
    // Note: Only commands with arguments need to be handled here    

    // Clear the command now that we've handled it
    clear_pod_command(sPod, command_slot);
}


void reject_pod_command(strPod *sPod, const strPodCmd *cmd, const char *reject_message, strPodCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_pod_command(sPod, command_slot);
}


void clear_pod_command(strPod *sPod, strPodCmd *command_slot)
{
    // Clear the pod command
    command_slot->command = POD_NO_CMD; // No command
}
*/

/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

void cmd_POD_IDLE()
{
    #if DEBUG == 1U
        printf("cmd_POD_IDLE() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_IDLE;

}

void cmd_POD_TEST_MODE()
{
    #if DEBUG == 1U
        printf("cmd_POD_TEST_MODE() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_TEST_MODE;

}

void cmd_POD_DRIVE()
{
    #if DEBUG == 1U
        printf("cmd_POD_DRIVE() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_DRIVE;

}

void cmd_POD_FLIGHT_PREP()
{
    #if DEBUG == 1U
        printf("cmd_POD_FLIGHT_PREP() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_FLIGHT_PREP;

}

void cmd_POD_ARMED_WAIT()
{
    #if DEBUG == 1U
        printf("cmd_POD_ARMED_WAIT() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_ARMED_WAIT;

}

void cmd_POD_READY()
{
    #if DEBUG == 1U
        printf("cmd_POD_READY() called\n");
    #endif
    
    strPodCmd * cmd = &sFCU.sPodStateMachine.command;
    cmd->command = POD_READY;

}

