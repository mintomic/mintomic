#ifndef __MINTOMIC_PRIVATE_MINTOMIC_XLC_S390_H__
#define __MINTOMIC_PRIVATE_MINTOMIC_XLC_S390_H__

// This implementation could be improved if we knew we were on
// z196 or later hardware, and if interlocked-access facility was known available
// This is a set of instructions which should work in 31 bit modes.
// It should be easy to extend this to 64bit mode, but I have no need to do so.

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Atomic types
//-------------------------------------
#if MINT_HAS_C11_MEMORY_MODEL
    typedef struct { uint32_t /*_nonatomic*/; } __attribute__((aligned(4))) mint_atomic32_t;
    typedef struct { uint64_t /*_nonatomic*/; } __attribute__((aligned(8))) mint_atomic64_t;
    typedef struct { void */*_nonatomic*/; } __attribute__((aligned(MINT_PTR_SIZE))) mint_atomicPtr_t;
#else
    // Without a C/C++11 memory model, we need to declare shared values volatile to
    // prevent out-of-thin-air stores
    typedef struct { volatile uint32_t _nonatomic; } __attribute__((aligned(4))) mint_atomic32_t;
    typedef struct { volatile uint64_t _nonatomic; } __attribute__((aligned(8))) mint_atomic64_t;
    typedef struct { volatile void* _nonatomic; } __attribute__((aligned(4))) mint_atomicPtr_t;
#endif


//-------------------------------------
//  Fences
//-------------------------------------
#define mint_signal_fence_consume() (0)
#define mint_signal_fence_acquire() (0)//asm volatile("" ::: "memory")
#define mint_signal_fence_release() (0)//asm volatile("" ::: "memory")
#define mint_signal_fence_seq_cst() (0)//asm volatile("" ::: "memory")

#define mint_thread_fence_consume() (0)
void mint_thread_fence_acquire();
void mint_thread_fence_release();
void mint_thread_fence_seq_cst();
#pragma map (mint_thread_fence_acquire, "MNTFENCE")
#pragma map (mint_thread_fence_release, "MNTFENCE")
#pragma map (mint_thread_fence_seq_cst, "MNTFENCE")


//----------------------------------------------
//  32-bit atomic operations
//----------------------------------------------
MINT_C_INLINE uint32_t mint_load_32_relaxed(mint_atomic32_t *object)
{
    return object->_nonatomic;
}

MINT_C_INLINE void mint_store_32_relaxed(mint_atomic32_t *object, uint32_t desired)
{
    object->_nonatomic = desired;
}

// All functions below here are implemented as XPLINK function calls in mintomic_zos.s

uint32_t mint_compare_exchange_strong_32_relaxed(mint_atomic32_t *object, uint32_t expected, uint32_t desired);
#pragma map (mint_compare_exchange_strong_32_relaxed, "MNTCXS32")

uint32_t mint_fetch_add_32_relaxed(mint_atomic32_t *object, int32_t operand);
#pragma map (mint_fetch_add_32_relaxed, "MNTADD32")

uint32_t mint_fetch_and_32_relaxed(mint_atomic32_t *object, uint32_t operand);
#pragma map (mint_fetch_and_32_relaxed, "MNTAND32")

uint32_t mint_fetch_or_32_relaxed(mint_atomic32_t *object, uint32_t operand);
#pragma map (mint_fetch_or_32_relaxed, "MNTOR32")

//----------------------------------------------
//  64-bit atomic operations
//----------------------------------------------

uint64_t mint_load_64_relaxed(mint_atomic64_t *object);
#pragma map (mint_load_64_relaxed, "MNTLD64")

void mint_store_64_relaxed(mint_atomic64_t *object, uint64_t desired);
#pragma map (mint_store_64_relaxed, "MNTST64")

uint64_t mint_compare_exchange_strong_64_relaxed(mint_atomic64_t *object, uint64_t expected, uint64_t desired);
#pragma map (mint_compare_exchange_strong_64_relaxed, "MNTCXS64")

uint64_t mint_fetch_add_64_relaxed(mint_atomic64_t *object, int64_t operand);
#pragma map (mint_fetch_add_64_relaxed, "MNTADD64")

uint64_t mint_fetch_and_64_relaxed(mint_atomic64_t *object, uint64_t operand);
#pragma map (mint_fetch_and_64_relaxed, "MNTAND64")

uint64_t mint_fetch_or_64_relaxed(mint_atomic64_t *object, uint64_t operand);
#pragma map (mint_fetch_or_64_relaxed, "MNTOR64")

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_MINTOMIC_XLC_S390_H__
