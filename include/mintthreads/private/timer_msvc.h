#ifndef __MINTTHREADS_PRIVATE_TIMER_MSVC_H__
#define __MINTTHREADS_PRIVATE_TIMER_MSVC_H__

#include <mintomic/core.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef uint64_t mint_timer_tick;

extern double mint_timer_ticksToSeconds;
extern double mint_timer_secondsToTicks;

void mint_timer_initialize();

MINT_C_INLINE mint_timer_tick mint_timer_get()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return now.QuadPart;
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTTHREADS_PRIVATE_TIMER_MSVC_H__
