/**
 * @file		FCU__FCTL__MAIN_SM.C
 * @brief		Main state machine for the flight control unit
 * @author		Lachlan Grogan, Ryan Adams
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__FCTL__MAIN_SM
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#include "pod__control.h"


#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

//the structure
extern struct _strFCU sFCU;

//TODO: need the following function implemented

//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_NAV__GetFrontPos();
//u32FCU_FCTL_NAV__GetRearPos();
//u32FCU_FCTL_NAV__PodSpeed();
//u32FCU_FCTL_LASERORIENT__Get_Z_Pos()
//u32LandingGearMLPLeftAftValue = u32FCU_LGU__Get_MLP_Value(Luint8 u8Counter);

/***************************************************************************//**
 * @brief
 * Init any variables as is needed by the main state machine
 * 
 * @st_funcMD5		5224534176289DBD9FF1B39936308C7E
 * @st_funcID		LCCM655R0.FILE.020.FUNC.001
 */
void vFCU_FCTL_MAINSM__Init(void)
{

    #ifdef WIN32
	DEBUG_PRINT("vFCU_FCTL_MAINSM__Init()");
    #endif

	// @todo: Initialize the state machine (set state)
	sFCU.sPodStateMachine.sm.state = POD_INIT_STATE;  // @todo: should we have a 'startup' state that checks to make sure the FCU is initialized before moving to 'IDLE'?

}


/***************************************************************************//**
 * @brief
 * Process the main state machine
 * 
 * @st_funcMD5		2C23D1564E9845C3BED5E00B06C0BBB3
 * @st_funcID		LCCM655R0.FILE.020.FUNC.002
 */
void vFCU_FCTL_MAINSM__Process(void)
{
    StateMachine *sm = &sFCU.sPodStateMachine.sm;
    
    // Step the state machine to pick up on state changes etc.
    sm_step(sm);
        
    // Process pod state machine
    switch (sm->state)
    {
        case POD_INIT_STATE:
        
            if (sm_entering(sm, POD_INIT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_INIT_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
                #ifdef WIN32
                	DEBUG_PRINT("Entering POD_INIT_STATE");
                #endif
            }
        
            // Handle transitions
            handle_POD_INIT_STATE_transitions();
         
            if (sm_exiting(sm, POD_INIT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_INIT_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_IDLE_STATE:
        
            if (sm_entering(sm, POD_IDLE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_IDLE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_IDLE_STATE_transitions();
         
            if (sm_exiting(sm, POD_IDLE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_IDLE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_TEST_MODE_STATE:
        
            if (sm_entering(sm, POD_TEST_MODE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_TEST_MODE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_TEST_MODE_STATE_transitions();
         
            if (sm_exiting(sm, POD_TEST_MODE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_TEST_MODE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_DRIVE_STATE:
        
            if (sm_entering(sm, POD_DRIVE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_DRIVE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_DRIVE_STATE_transitions();
         
            if (sm_exiting(sm, POD_DRIVE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_DRIVE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_ARMED_WAIT_STATE:
        
            if (sm_entering(sm, POD_ARMED_WAIT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_ARMED_WAIT_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_ARMED_WAIT_STATE_transitions();
         
            if (sm_exiting(sm, POD_ARMED_WAIT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_ARMED_WAIT_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_FLIGHT_PREP_STATE:
        
            if (sm_entering(sm, POD_FLIGHT_PREP_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_FLIGHT_PREP_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_FLIGHT_PREP_STATE_transitions();
         
            if (sm_exiting(sm, POD_FLIGHT_PREP_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_FLIGHT_PREP_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_READY_STATE:
        
            if (sm_entering(sm, POD_READY_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_READY_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_READY_STATE_transitions();
         
            if (sm_exiting(sm, POD_READY_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_READY_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_ACCEL_STATE:
        
            if (sm_entering(sm, POD_ACCEL_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_ACCEL_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_ACCEL_STATE_transitions();
         
            if (sm_exiting(sm, POD_ACCEL_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_ACCEL_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_COAST_INTERLOCK_STATE:
        
            if (sm_entering(sm, POD_COAST_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_COAST_INTERLOCK_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_COAST_INTERLOCK_STATE_transitions();
         
            if (sm_exiting(sm, POD_COAST_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_COAST_INTERLOCK_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_BRAKE_STATE:
        
            if (sm_entering(sm, POD_BRAKE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_BRAKE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_BRAKE_STATE_transitions();
         
            if (sm_exiting(sm, POD_BRAKE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_BRAKE_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;
        
        case POD_SPINDOWN_STATE:
        
            if (sm_entering(sm, POD_SPINDOWN_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering POD_SPINDOWN_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
            }
        
            // Handle transitions
            handle_POD_SPINDOWN_STATE_transitions();
         
            if (sm_exiting(sm, POD_SPINDOWN_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting POD_SPINDOWN_STATE\n", "sFCU.sPodStateMachine.sm");
                #endif
        
            }
            
            break;

    }
   
}

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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
    E_POD_COMMAND_T command = sFCU.sPodStateMachine.command.command;

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



void vFCU_FCTL_MAINSM__10MS_ISR(void)
{

}

void vFCU_FCTL_MAINSM__100MS_ISR(void)
{

}


#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */