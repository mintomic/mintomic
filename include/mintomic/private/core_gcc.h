#ifndef __MINTOMIC_PRIVATE_CORE_GCC_H__
#define __MINTOMIC_PRIVATE_CORE_GCC_H__

#include <pthread.h>
#include <stddef.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Alignment
//-------------------------------------
// Note: May not work on local variables.
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=24691
#define MINT_DECL_ALIGNED(declaration, amt) declaration __attribute__((aligned(amt)))


//-------------------------------------
//  Inlining
//-------------------------------------
#define MINT_C_INLINE static inline
#define MINT_NO_INLINE __attribute__((noinline))


//-------------------------------------
//  Thread IDs
//-------------------------------------
typedef pthread_t mint_tid;

MINT_C_INLINE mint_tid mint_get_current_thread_id()
{
    return pthread_self();
}


//-------------------------------------
//  Sleep
//-------------------------------------
MINT_C_INLINE void mint_yield_hw_thread()
{
    // Only implemented on x86/64
#if MINT_CPU_X86 || MINT_CPU_X64
    asm volatile("pause");
#endif
}

MINT_C_INLINE void mint_sleep_millis(int millis)
{
    struct timespec ts;
    ts.tv_sec = millis / 1000;
    ts.tv_nsec = (millis % 1000) * 1000;
    nanosleep(&ts, NULL);
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_CORE_GCC_H__
