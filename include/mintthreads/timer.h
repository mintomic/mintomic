#ifndef __MINTTHREADS_TIMER_H__
#define __MINTTHREADS_TIMER_H__

#include <mintomic/core.h>

#if MINT_COMPILER_MSVC
    #include "private/timer_msvc.h"
#elif MINT_COMPILER_GCC
    #include "private/timer_gcc.h"
#else
    #error Unsupported platform!
#endif

#endif // __MINTTHREADS_TIMER_H__
