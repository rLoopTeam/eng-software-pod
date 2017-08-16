#include "timers.h"

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
/*
typedef struct
{
    int duration_ms;  // How long to wait until repeating (note: still need to reset once you've handled it)
    int resolution_ms;

    // Is the timer running? Don't update if false.
    bool started;

    // Number of times to repeat (0 = no limit)    
    int elapsed_ms;
    
} strTimer;
*/

void timer_ensure_started(strTimer *t)
{
    if ( ! t->started ) {
        // If we're not started, make sure we are and reset our elapsed time
        t->started = true;
        t->elapsed_ms = 0;
    } else {
        // We're started; nothing to do
    }
}

void timer_stop(strTimer *t)
{
    // Stop the timer and reset the counter
    t->started = false;
    t->elapsed_ms = 0;
}

void timer_update(strTimer *t, int elapsed_ms)
{
    if (t->started) {
        t->elapsed_ms += elapsed_ms;
    }
}

void timer_reset(strTimer *timer)
{
    timer->elapsed_ms = 0;
}

bool timer_expired(const strTimer *timeout)
{
    return timeout->elapsed_ms >= timeout->duration_ms;
}


void timeout_ensure_started(strTimer *timeout)
{
    if ( ! timeout->started ) {
        // If we're not started, make sure we are and reset our elapsed time
        timeout_restart(timeout);
    } else {
        // We're started; nothing to do
    }
}


strTimer create_timeout(int duration_ms)
{
    strTimer t;
    t.duration_ms = duration_ms;
    t.elapsed_ms = 0;
    return t;
}

void timeout_reset(strTimer *timeout)
{
    timeout->elapsed_ms = 0;
    timeout->started = false;
}

bool timeout_expired(strTimer *timeout)
{
    return timeout->elapsed_ms >= timeout->duration_ms;
}

void timeout_update(strTimer *timeout, int elapsed_ms)
{
    if ( ! timeout_expired(timeout) ) 
    {
        // If we haven't expired, update our timeout. We have no reason to keep adding once we've expired.
        timeout->elapsed_ms += elapsed_ms;
    }
}

void timeout_restart(strTimer *timeout)
{
    timeout->elapsed_ms = 0U;
    timeout->started = true;
}
