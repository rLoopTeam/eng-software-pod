#include "interlock_command.h"


strInterlockCommand create_interlock_command(const Luint32 duration_ms)
{
    strInterlockCommand ic;
    ic->enabled = false;
    timeout_reset(ic->commandTimeout);
}


// Call this when the first packet is received. Ok to call it multiple times; it will just reset the timer.
void interlock_command_enable(strInterlockCommand *ic)
{
    ic->enabled = true;
    timeout_restart(&ic->commandTimeout);
}

// Call this when the second packet is received to check whether the command can execute (i.e. timeout has not expired)
bool interlock_command_can_execute(strInterlockCommand *ic)
{
    bool can_execute;
    
    // Note: I know this is not great code style but under time crunch    
    if (ic->enabled && ! timeout_expired(&ic->commandTimeout) )
    {
        can_execute = true;
    } 
    else 
    {
        can_execute = false;
    }
    return can_execute;
}

// Call this if the command was executed and we're ready to listen for the initial packet again
// @todo: do we even need this? if we receive another enable packet, we will restart the timeout. Once its timed out, it will not keep counting, so we're ok. 
void interlock_command_reset(strInterlockCommand *ic)
{
    // Reset the timeout (stop it and set the elapsed time to 0)
    timeout_reset(&ic->commandTimeout);
}

// Call this in one of our timer ISRs. Ok to call this since the timeout has to be started for the update to have any effect. 
void interlock_command_update_timeout(strInterlockCommand *ic, Luint8 time_ms)
{
    // Update the timeout
    timeout_update(&ic->commandTimeout, time_ms);
}
