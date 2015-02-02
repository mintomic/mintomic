#ifndef __MINTOMIC_PRIVATE_MINTOMIC_GCC_S390_H__
#define __MINTOMIC_PRIVATE_MINTOMIC_GCC_S390_H__

// This implementation could be improved if we knew we were on
// z196 or later hardware, and if interlocked-access facility was known available
// This is a set of instructions which should work on all 64bit processors in
// either 64 or 31 bit modes

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Atomic types
//-------------------------------------
#if MINT_HAS_C11_MEMORY_MODEL
    typedef struct { uint32_t _nonatomic; } __attribute__((aligned(4))) mint_atomic32_t;
    typedef struct { uint64_t _nonatomic; } __attribute__((aligned(8))) mint_atomic64_t;
    typedef struct { void *_nonatomic; } __attribute__((aligned(MINT_PTR_SIZE))) mint_atomicPtr_t;
#else
    // Without a C/C++11 memory model, we need to declare shared values volatile to
    // prevent out-of-thin-air stores
    typedef struct { volatile uint32_t _nonatomic; } __attribute__((aligned(4))) mint_atomic32_t;
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
//With fast-BCR-serialization availability these would be bcr14,0
#define mint_thread_fence_acquire() asm volatile("bcr 15,0" ::: "memory")
#define mint_thread_fence_release() asm volatile("bcr 15,0" ::: "memory")
#define mint_thread_fence_seq_cst() asm volatile("bcr 15,0" ::: "memory")


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
    uint32_t original;
    asm volatile("	cs	%0,%3,%1\n"
				 : "=&d" (original), "=Q" (object->_nonatomic)
				 : "0" (expected), "d" (desired), "Q" (object->_nonatomic)
				 : "memory", "cc");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_add_32_relaxed(mint_atomic32_t *object, int32_t operand)
{
    uint32_t original;
	register uint32_t temp;
    asm volatile("l   %0, %2\n"
				 "again%=:\n"
				 "lr  %1, %0\n"
				 "ar  %1, %3\n"
				 "cs  %0, %1, %2\n"
				 "brc 4, again%="
                 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
                 : "r"(operand), "Q"(object->_nonatomic)
		         : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_and_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    // The & in "=&a"(original) makes eax an earlyclobber operand.
    // If we don't specify &, the compiler may assign eax to input operand %3 as well.
    uint32_t original;
	register uint32_t temp;
    asm volatile("l   %0, %2\n"
				 "again%=:\n"
				 "lr  %1, %0\n"
				 "nr  %1, %3\n"
				 "cs  %0, %1, %2\n"
				 "brc 4, again%="
                 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
                 : "r"(operand), "Q"(object->_nonatomic)
		         : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_or_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    uint32_t original;
    register uint32_t temp;
    asm volatile("l   %0, %2\n"
				 "again%=:\n"
				 "lr  %1, %0\n"
				 "or  %1, %3\n"
				 "cs  %0, %1, %2\n"
				 "brc 4, again%="
                 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
                 : "r"(operand), "Q"(object->_nonatomic)
		         : "cc", "memory");
    return original;
}

MINT_C_INLINE uint64_t mint_load_64_relaxed(mint_atomic64_t *object)
{
	// GCC makes aligned 64-bit loads atomic in both 31 and 64bit amodes
	return object->_nonatomic;
}

MINT_C_INLINE void mint_store_64_relaxed(mint_atomic64_t *object, uint64_t desired)
{
	// GCC makes aligned 64-bit stores atomic in both 31 and 64bit amodes
	object->_nonatomic = desired;
}

#if MINT_CPU_S390X
    //------------------------------------------------------------------------
    //  64-bit atomic operations on 64-bit processor (S390X)
    //------------------------------------------------------------------------

    MINT_C_INLINE uint64_t mint_compare_exchange_strong_64_relaxed(mint_atomic64_t *object, uint64_t expected, uint64_t desired)
    {
        // In 64 but AMODE, we can work with 64-bit values directly.
        // It's the same as 32 bit but with a g for grande.
        uint64_t original;
		asm volatile("	csg	%0,%3,%1\n"
					 : "=&d" (original), "=Q" (object->_nonatomic)
					 : "0" (expected), "d" (desired), "Q" (object->_nonatomic)
					 : "memory", "cc");
        return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_add_64_relaxed(mint_atomic64_t *object, int64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("lg   %0, %2\n"
					 "again%=:\n"
					 "lgr  %1, %0\n"
					 "agr  %1, %3\n"
					 "csg  %0, %1, %2\n"
					 "brc  4, again%="
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "r"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
	return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_and_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("lg   %0, %2\n"
					 "again%=:\n"
					 "lgr  %1, %0\n"
					 "ngr  %1, %3\n"
					 "csg  %0, %1, %2\n"
					 "brc  4, again%="
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "r"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
        return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_or_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("lg   %0, %2\n"
					 "again%=:\n"
					 "lgr  %1, %0\n"
					 "ogr  %1, %3\n"
					 "csg  %0, %1, %2\n"
					 "brc  4, again%="
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "r"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
        return original;
    }
#elif MINT_CPU_S390
    //------------------------------------------------------------------------
    //  64-bit atomic operations on 32/31-bit processor (S390)
    //------------------------------------------------------------------------

    MINT_C_INLINE uint64_t mint_compare_exchange_strong_64_relaxed(mint_atomic64_t *object, uint64_t expected, uint64_t desired)
    {
		asm volatile("	cds	%0,%2,%1\n"
					 : "+&d" (expected), "+Q" (object->_nonatomic)
					 : "d" (desired)
					 : "memory", "cc");
        return expected;
    }

    MINT_C_INLINE uint64_t mint_fetch_add_64_relaxed(mint_atomic64_t *object, int64_t operand)
    {
        int64_t original;
		int64_t temp;
		asm volatile("lm %0, %N0, %2\n"
					 "again%=:\n"
					 // Copy original to temp
					 "lr %1, %0\n"
					 "lr %N1, %N0\n"
					 // Add
					 "ar  %1, %3\n"
					 "alr %N1, %N3\n"
					 // Branch on NOT carry, cc = 0 or cc = 1
					 "brc 12,nocarry%=\n"
					 "ahi %1,1\n"
					 "nocarry%=:\n"
					 "cds  %0, %1, %2\n"
					 "brc  4, again%=\n"
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "d"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
		return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_and_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        int64_t original;
		int64_t temp;
		asm volatile("lm %0, %N0, %2\n"
					 "again%=:\n"
					 // Copy original to temp
					 "lr %1, %0\n"
					 "lr %N1, %N0\n"
					 // And both words
					 "nr  %1, %3\n"
					 "nr %N1, %N3\n"
					 "cds  %0, %1, %2\n"
					 "brc  4, again%=\n"
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "d"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
		return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_or_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        int64_t original;
		int64_t temp;
		asm volatile("lm %0, %N0, %2\n"
					 "again%=:\n"
					 // Copy original to temp
					 "lr %1, %0\n"
					 "lr %N1, %N0\n"
					 // Or both words
					 "or  %1, %3\n"
					 "or %N1, %N3\n"
					 "cds  %0, %1, %2\n"
					 "brc  4, again%=\n"
					 : "=&d"(original), "=&d"(temp), "+Q"(object->_nonatomic)
					 : "d"(operand), "Q"(object->_nonatomic)
					 : "cc", "memory");
		return original;
    }

#else
    #error Unrecognized target CPU!
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_MINTOMIC_GCC_S390_H__
