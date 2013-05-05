#ifndef __MINTTHREADS_THREAD_H__
#define __MINTTHREADS_THREAD_H__

#include <mintomic/core.h>

#if MINT_COMPILER_MSVC
    #include "private/thread_msvc.h"
#elif MINT_COMPILER_GCC
    #include "private/thread_gcc.h"
#else
    #error Unsupported platform!
#endif

#endif // __MINTTHREADS_THREAD_H__
