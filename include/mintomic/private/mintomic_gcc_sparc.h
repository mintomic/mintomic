#ifndef __MINTOMIC_PRIVATE_MINTOMIC_GCC_SPARC_H__
#define __MINTOMIC_PRIVATE_MINTOMIC_GCC_SPARC_H__

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Atomic types
//-------------------------------------
#if MINT_HAS_C11_MEMORY_MODEL
    typedef struct { uint32_t _nonatomic; } __attribute__((aligned(8))) mint_atomic32_t;
    typedef struct { uint64_t _nonatomic; } __attribute__((aligned(8))) mint_atomic64_t;
    typedef struct { void *_nonatomic; } __attribute__((aligned(MINT_PTR_SIZE))) mint_atomicPtr_t;
#else
    // Without a C/C++11 memory model, we need to declare shared values volatile to
    // prevent out-of-thin-air stores
    typedef struct { volatile uint32_t _nonatomic; } __attribute__((aligned(8))) mint_atomic32_t;
    typedef struct { volatile uint64_t _nonatomic; } __attribute__((aligned(8))) mint_atomic64_t;
    typedef struct { void *volatile _nonatomic; } __attribute__((aligned(MINT_PTR_SIZE))) mint_atomicPtr_t;
#endif


//-------------------------------------
//  Fences
//-------------------------------------
#define mint_signal_fence_consume() (0)
#define mint_signal_fence_acquire() asm volatile("" ::: "memory")
#define mint_signal_fence_release() asm volatile("" ::: "memory")
#define mint_signal_fence_seq_cst() asm volatile("" ::: "memory")

#define mint_thread_fence_consume() (0)
#define mint_thread_fence_acquire() asm volatile("membar #LoadLoad | #LoadStore" ::: "memory")
#define mint_thread_fence_release() asm volatile("membar #LoadStore | #StoreStore" ::: "memory")
#define mint_thread_fence_seq_cst() asm volatile("membar #Sync" ::: "memory")


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

MINT_C_INLINE uint32_t mint_compare_exchange_strong_32_relaxed(mint_atomic32_t *object, uint32_t expected, uint32_t desired)
{
    asm volatile("cas  [%2], %3, %0\n"
				 : "=&r" (desired)
                 : "0"(desired), "r" (&object->_nonatomic), "r" (expected));
    return desired;
}

MINT_C_INLINE uint32_t mint_fetch_add_32_relaxed(mint_atomic32_t *object, int32_t operand)
{
    register uint32_t original;
	register uint32_t result;
    asm volatile("lduw [%3], %0\n"
				 "again%=:\n"
				 "add %2, %0, %1\n"
				 "cas [%3], %0, %1\n"
				 "cmp %0, %1\n"
				 "bne,a,pn  %%icc, again%=\n"
				 "add %1, 0, %0\n"
				 : "=&r" (original), "=&r" (result)
                 : "r" (operand), "r" (&object->_nonatomic)
				 : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_and_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    register uint32_t original;
	register uint32_t result;
    asm volatile("lduw [%3], %0\n"
				 "again%=:\n"
				 "and %2, %0, %1\n"
				 "cas [%3], %0, %1\n"
				 "cmp %0, %1\n"
				 "bne,a,pn  %%icc, again%=\n"
				 "add %1, 0, %0\n"
				 : "=&r" (original), "=&r" (result)
                 : "r" (operand), "r" (&object->_nonatomic)
				 : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_or_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    register uint32_t original;
	register uint32_t result;
    asm volatile("lduw [%3], %0\n"
				 "again%=:\n"
				 "or %2, %0, %1\n"
				 "cas [%3], %0, %1\n"
				 "cmp %0, %1\n"
				 "bne,a,pn  %%icc, again%=\n"
				 "add %1, 0, %0\n"
				 : "=&r" (original), "=&r" (result)
                 : "r" (operand), "r" (&object->_nonatomic)
				 : "cc", "memory");
	return original;
}


#if MINT_CPU_SPARC64
    //------------------------------------------------------------------------
    //  64-bit atomic operations on 64-bit processor (PPC64)
    //------------------------------------------------------------------------

    MINT_C_INLINE uint64_t mint_load_64_relaxed(mint_atomic64_t *object)
    {
        // On 64 bit sparc, aligned 64-bit loads are already atomic.
        return object->_nonatomic;
    }

    MINT_C_INLINE void mint_store_64_relaxed(mint_atomic64_t *object, uint64_t desired)
    {
        // On 64 bit sparc, aligned 64-bit stores are already atomic.
        object->_nonatomic = desired;
    }

    MINT_C_INLINE uint64_t mint_compare_exchange_strong_64_relaxed(mint_atomic64_t *object, uint64_t expected, uint64_t desired)
    {
        // On Sparc64, we can work with 64-bit values directly.
        // It's the same as 32 bit but with an x
		asm volatile("casx  [%2], %3, %0\n"
					 : "=&r" (desired)
					 : "0"(desired), "r" (&object->_nonatomic), "r" (expected));
		return desired;
    }

    MINT_C_INLINE uint64_t mint_fetch_add_64_relaxed(mint_atomic64_t *object, int64_t operand)
    {
		register uint64_t original;
		register uint64_t result;
		asm volatile("ldx [%3], %0\n"
					 "again%=:\n"
					 "add %2, %0, %1\n"
					 "casx [%3], %0, %1\n"
					 "cmp %0, %1\n"
					 "bne,a,pn  %%xcc, again%=\n"
					 "add %1, 0, %0\n"
					 : "=&r" (original), "=&r" (result)
					 : "r" (operand), "r" (&object->_nonatomic)
					 : "cc", "memory");
		return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_and_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
		register uint64_t original;
		register uint64_t result;
		asm volatile("ldx [%3], %0\n"
					 "again%=:\n"
					 "and %2, %0, %1\n"
					 "casx [%3], %0, %1\n"
					 "cmp %0, %1\n"
					 "bne,a,pn  %%xcc, again%=\n"
					 "add %1, 0, %0\n"
					 : "=&r" (original), "=&r" (result)
					 : "r" (operand), "r" (&object->_nonatomic)
					 : "cc", "memory");
		return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_or_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
		register uint64_t original;
		register uint64_t result;
		asm volatile("ldx [%3], %0\n"
					 "again%=:\n"
					 "or %2, %0, %1\n"
					 "casx [%3], %0, %1\n"
					 "cmp %0, %1\n"
					 "bne,a,pn  %%xcc, again%=\n"
					 "add  %1, 0, %0\n"
					 : "=&r" (original), "=&r" (result)
					 : "r" (operand), "r" (&object->_nonatomic)
					 : "cc", "memory");
        return original;
    }

#else
    #error Unrecognized target CPU!
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_MINTOMIC_GCC_SPARC_H__
