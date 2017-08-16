#ifndef _TIMERS_H_
#define _TIMERS_H_

#include <stdbool.h>
/*
Usage:
strRepeatTimer t;

SomeGlobalStruct gs;

duration_ms = 1000; 
resolution_ms = 10;
repeat_n = 3;
gs.my_timer = create_timer(duration_ms, resolution_ms);

void some_loop_method()
{
    timer_ensure_started(gs.my_timer);

    if ( timer_expired(gs.my_timer) )
    {
        // Do something
        // FLASH THE LIGHTS!
        
        // Reset the timer
        timer_reset(gs.my_timer);
    }
}


void some_ISR_10ms()
{
    timer_update(gs.rep_timer, 10);
}

Notes:
- maybe add a parameter, e.g. 'if I haven't checked this in x ms, go ahead and stop the timer'


gs.my_timeout = create_timeout(duration_ms, resolution_ms);

void some_loop_method()
{
    timeout_ensure_started(gs.rep_timeout);
    if (timeout_expired(gs.rep_timeout)) {
        // Do timeout stuff
        // Note: the timeout won't reset unless you reset it
    }
}

void some_ISR_10ms()
{
    timeout_update(gs.rep_timeout, 10);
}
*/

typedef struct
{
    Luint32 duration_ms;  // How long to wait until repeating (note: still need to reset once you've handled it)

    // Is the timer running? Don't update if false.
    bool started;

    // Number of times to repeat (0 = no limit)    
    Luint32 elapsed_ms;
    
} strTimer;


// Timer functionality
void timer_ensure_started(strTimer *t);
void timer_stop(strTimer *t);
void timer_update(strTimer *t, Luint32 elapsed_ms);
void timer_reset(strTimer *t);
bool timer_expired(const strTimer *t);

// Timeout functionality
void timeout_ensure_started(strTimer *timeout);
strTimer create_timeout(Luint32 duration_ms);
void timeout_reset(strTimer *timeout);
void timeout_restart(strTimer *timeout);
bool timeout_expired(strTimer *timeout);
void timeout_update(strTimer *timeout, Luint32 elapsed_ms);


#endif //_TIMERS_H_
