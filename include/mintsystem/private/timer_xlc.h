#ifndef __MINTSYSTEM_PRIVATE_TIMER_XLC_H__
#define __MINTSYSTEM_PRIVATE_TIMER_XLC_H__

#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Timers
//-------------------------------------
typedef uint64_t mint_timer_tick_t;

// These are initialized by mint_timer_initialize:
extern double mint_timer_ticksToSeconds;
extern double mint_timer_secondsToTicks;

void mint_timer_initialize();
double mint_timer_getSecondsToTicks();    // Can be called before mint_timer_initialize

MINT_C_INLINE int mint_timer_is_initialized()
{
    return mint_timer_secondsToTicks != 0;
}

extern int _storeclock(uint64_t* c);
#pragma map(_storeclock, "STCK")

MINT_C_INLINE mint_timer_tick_t mint_timer_get()
{
	uint64_t clock;
	_storeclock(&clock);
	clock=clock*1000/4096;
	return clock;
}

MINT_C_INLINE int mint_timer_greater_or_equal(mint_timer_tick_t a, mint_timer_tick_t b)
{
    return (int64_t) (a - b) >= 0;
}


//-------------------------------------
//  Sleep
//-------------------------------------
MINT_C_INLINE void mint_yield_hw_thread()
{
    // Only implemented on x86/64
}

MINT_C_INLINE void mint_sleep_millis(int millis)
{
    struct timeval ts;
    ts.tv_sec = millis / 1000;
    ts.tv_usec = (millis % 1000) * 1000;
	select(0, NULL, NULL, NULL, &ts);
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTSYSTEM_PRIVATE_TIMER_XLC_H__
