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

#include "pod__types.h"
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


#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
