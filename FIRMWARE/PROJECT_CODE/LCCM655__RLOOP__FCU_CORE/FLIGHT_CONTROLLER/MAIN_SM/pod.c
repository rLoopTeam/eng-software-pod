#include "pod.h"
#include "../fcu_core.h"

// Subsystems
#include "brakes/brakes.h"
#include "cooling/cooling.h"
#include "auxprop/auxprop.h"
#include "engines/engines.h"


void vPod__Init(strPod *sPod)
{
    sPod->sm.state = POD_INIT_STATE;
        

    // Init Brakes subsystem
    sPod->sBrakes.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sBrakes.name, "sBrakes");
    sprintf(sPod->sBrakes.absname, "%s.%s", sPod->absname, sPod->sBrakes.name);
    #endif
    
    vBrakes__Init(&sPod->sBrakes);
    
    // Init Cooling subsystem
    sPod->sCooling.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sCooling.name, "sCooling");
    sprintf(sPod->sCooling.absname, "%s.%s", sPod->absname, sPod->sCooling.name);
    #endif
    
    vCooling__Init(&sPod->sCooling);
    
    // Init AuxProp subsystem
    sPod->sAuxProp.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sAuxProp.name, "sAuxProp");
    sprintf(sPod->sAuxProp.absname, "%s.%s", sPod->absname, sPod->sAuxProp.name);
    #endif
    
    vAuxProp__Init(&sPod->sAuxProp);
    
    // Init Engines subsystem
    sPod->sEngines.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sEngines.name, "sEngines");
    sprintf(sPod->sEngines.absname, "%s.%s", sPod->absname, sPod->sEngines.name);
    #endif
    
    vEngines__Init(&sPod->sEngines);

}


void vPod__Process(strPod *sPod)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sPod->sm);
        
    // Process pod state machine
    switch (sPod->sm.state)
    {
        case POD_INIT_STATE:
        
            if (sm_entering(&sPod->sm, POD_INIT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_INIT_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_INIT_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_INIT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_INIT_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_IDLE_STATE:
        
            if (sm_entering(&sPod->sm, POD_IDLE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_IDLE_STATE\n", sPod->absname);
                #endif
                internal_cmd_POD_BRAKES_DISABLE(&sPod->sBrakes);
                internal_cmd_COOLING_DISABLE(&sPod->sCooling);
                internal_cmd_AUXPROP_DISABLE(&sPod->sAuxProp);
            }
        
            // Handle transitions
            handle_POD_IDLE_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_IDLE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_IDLE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_TEST_MODE_STATE:
        
            if (sm_entering(&sPod->sm, POD_TEST_MODE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_TEST_MODE_STATE\n", sPod->absname);
                #endif
                internal_cmd_POD_BRAKES_ENABLE(&sPod->sBrakes);
                cmd_COOLING_MANUAL(&sPod->sCooling);
                internal_cmd_AUXPROP_MANUAL(&sPod->sAuxProp);
            }
        
            // Handle transitions
            handle_POD_TEST_MODE_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_TEST_MODE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_TEST_MODE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_DRIVE_STATE:
        
            if (sm_entering(&sPod->sm, POD_DRIVE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_DRIVE_STATE\n", sPod->absname);
                #endif
                cmd_POD_BRAKES_HOLD(&sPod->sBrakes);
                cmd_COOLING_MANUAL(&sPod->sCooling);
                internal_cmd_AUXPROP_ENABLE(&sPod->sAuxProp);
            }
        
            // Handle transitions
            handle_POD_DRIVE_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_DRIVE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_DRIVE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_ARMED_WAIT_STATE:
        
            if (sm_entering(&sPod->sm, POD_ARMED_WAIT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_ARMED_WAIT_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_ARMED_WAIT_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_ARMED_WAIT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_ARMED_WAIT_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_FLIGHT_PREP_STATE:
        
            if (sm_entering(&sPod->sm, POD_FLIGHT_PREP_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_FLIGHT_PREP_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_FLIGHT_PREP_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_FLIGHT_PREP_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_FLIGHT_PREP_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_READY_STATE:
        
            if (sm_entering(&sPod->sm, POD_READY_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_READY_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_READY_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_READY_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_READY_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_ACCEL_STATE:
        
            if (sm_entering(&sPod->sm, POD_ACCEL_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_ACCEL_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_ACCEL_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_ACCEL_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_ACCEL_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_COAST_INTERLOCK_STATE:
        
            if (sm_entering(&sPod->sm, POD_COAST_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_COAST_INTERLOCK_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_COAST_INTERLOCK_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_COAST_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_COAST_INTERLOCK_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_BRAKE_STATE:
        
            if (sm_entering(&sPod->sm, POD_BRAKE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_BRAKE_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_BRAKE_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_BRAKE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_BRAKE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case POD_SPINDOWN_STATE:
        
            if (sm_entering(&sPod->sm, POD_SPINDOWN_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_SPINDOWN_STATE\n", sPod->absname);
                #endif
            }
        
            // Handle transitions
            handle_POD_SPINDOWN_STATE_transitions();
         
            if (sm_exiting(&sPod->sm, POD_SPINDOWN_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_SPINDOWN_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;

    }
    
    /////////////////////////////////////////////////////////////////
    //  Process Subsystems
    /////////////////////////////////////////////////////////////////
    
    // Process Brakes subsystem
    vBrakes__Process(&sPod->sBrakes);
    
    // Process Cooling subsystem
    vCooling__Process(&sPod->sCooling);
    
    // Process AuxProp subsystem
    vAuxProp__Process(&sPod->sAuxProp);
    
    // Process Engines subsystem
    vEngines__Process(&sPod->sEngines);

}


void vPod__10MS_ISR(strPod *sPod) 
{
    // Coast interlock timeout
    timeout_update(&sPod->CoastInterlockTimeout, 10);
    
    // Brakes 10ms ISR
    vBrakes__10MS_ISR(&sPod->sBrakes);
    
    // Cooling 10ms ISR
    vCooling__10MS_ISR(&sPod->sCooling);
    
    // AuxProp 10ms ISR
    vAuxProp__10MS_ISR(&sPod->sAuxProp);
    
    // Engines 10ms ISR
    vEngines__10MS_ISR(&sPod->sEngines);
    

}

void vPod__100MS_ISR(strPod *sPod)
{
    // Ready state to Idle backup timeout
    timeout_update(&sPod->ReadyExpiredBackupTimeout, 100);
    
    // Accel to Coast Interlock backup timeout
    timeout_update(&sPod->AccelBackupTimeout, 100);
    
    // Brake to Spindown backup timeout
    timeout_update(&sPod->BrakeToSpindownBackupTimeout, 100);
    
    // Spindown to Idle backup timeout
    timeout_update(&sPod->SpindownToIdleBackupTimeout, 100);
    
    // Brakes 100ms ISR
    vBrakes__100MS_ISR(&sPod->sBrakes);
    
    // Cooling 100ms ISR
    vCooling__100MS_ISR(&sPod->sCooling);
    
    // AuxProp 100ms ISR
    vAuxProp__100MS_ISR(&sPod->sAuxProp);
    
    // Engines 100ms ISR
    vEngines__100MS_ISR(&sPod->sEngines);
    

}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_pod_transitions(strPod *sPod)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_pod_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strPodCmd.
    command_executed = handle_pod_command(sPod, &sPod->internal_command, &sPod->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strPodCmd.
        command_executed = handle_pod_command(sPod, &sPod->external_command, &sPod->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_pod_conditional_transition(sPod);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sPod->sm))
    {
        handle_pod_timeout_transition(sPod);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sPod->sm))
    {
        handle_pod_automatic_transition(sPod);
    }
    else
    {
        // Nothing more to do
    }

}


