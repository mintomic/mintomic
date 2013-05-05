#ifndef __MINTTHREADS_PRIVATE_TIMER_GCC_H__
#define __MINTTHREADS_PRIVATE_TIMER_GCC_H__

#include <mintomic/core.h>
#if MINT_IS_APPLE
    #include <mach/mach_time.h>
#else
    #include <time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef uint64_t mint_timer_tick;

extern double mint_timer_secondsToTicks;
extern double mint_timer_ticksToSeconds;

void mint_timer_initialize();

MINT_C_INLINE mint_timer_tick mint_timer_get()
{
#if MINT_IS_APPLE
    return mach_absolute_time();
#else
    struct timespec tick;
    clock_gettime(CLOCK_MONOTONIC, &tick);
    return (mint_timer_tick) tick.tv_sec * 1000000000ull + tick.tv_nsec;
#endif
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTTHREADS_PRIVATE_TIMER_GCC_H__
