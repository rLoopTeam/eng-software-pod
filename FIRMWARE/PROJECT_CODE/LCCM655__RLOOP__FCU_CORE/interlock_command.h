#ifndef _INTERLOCK_COMMAND_H_
#define _INTERLOCK_COMMAND_H_

#include <stdbool.h>
#include "timers.h"


typedef struct
{
    bool enabled; // Happens first, starts the timer
    strTimer commandTimeout;

} strInterlockCommand;


strInterlockCommand create_interlock_command(const Luint32 duration_ms);

// Call this when the first packet is received. Ok to call it multiple times; it will just restart the timeout.
void interlock_command_enable(strInterlockCommand *ic);

// Call this when the second packet is received to check whether the command can execute (i.e. timeout has not expired)
bool interlock_command_can_execute(strInterlockCommand *ic);

// Call this if the command was executed and we're ready to listen for the initial packet again
// @todo: do we even need this? if we receive another enable packet, we will restart the timeout. Once its timed out, it will not keep counting, so we're ok. 
void interlock_command_reset(strInterlockCommand *ic);

// Call this in one of our timer ISRs. Ok to call this since the timeout has to be started for the update to have any effect. 
void interlock_command_update_timeout(strInterlockCommand *ic, Luint8 time_ms);


#endif //_INTERLOCK_COMMAND_H_