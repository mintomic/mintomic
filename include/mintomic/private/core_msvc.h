#ifndef __MINTOMIC_PRIVATE_CORE_MSVC_H__
#define __MINTOMIC_PRIVATE_CORE_MSVC_H__

#if MINT_TARGET_XBOX_360    // Xbox 360
    #include <xtl.h>
#else                       // Windows
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    #undef WIN32_LEAN_AND_MEAN
    #include <intrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Alignment
//-------------------------------------
#define MINT_DECL_ALIGNED(declaration, amt) __declspec(align(amt)) declaration


//-------------------------------------
//  Inlining
//-------------------------------------
#ifdef __cplusplus
#define MINT_C_INLINE inline
#else
#define MINT_C_INLINE __inline
#endif

#define MINT_NO_INLINE __declspec(noinline)


//-------------------------------------
//  Thread IDs
//-------------------------------------
typedef uint32_t mint_tid;

MINT_C_INLINE mint_tid mint_get_current_thread_id()
{
#if MINT_TARGET_XBOX_360  // Xbox 360
    return GetCurrentThreadId();
#elif MINT_CPU_X64        // Windows x64
    return ((uint32_t*) __readgsqword(48))[18]; // Read directly from the TIB
#elif MINT_CPU_X86        // Windows x86
    return ((uint32_t*) __readfsdword(24))[9];  // Read directly from the TIB
#endif
}


//-------------------------------------
//  Sleep
//-------------------------------------
MINT_C_INLINE void mint_yield_hw_thread()
{
    YieldProcessor();
}

MINT_C_INLINE void mint_sleep_millis(int millis)
{
    Sleep(millis);
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_CORE_MSVC_H__
