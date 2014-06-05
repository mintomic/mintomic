#ifndef __MINTOMIC_PRIVATE_MINTOMIC_GCC_POWERPC_H__
#define __MINTOMIC_PRIVATE_MINTOMIC_GCC_POWERPC_H__

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
//ACTODO - Do we need something more for fences
#define mint_signal_fence_consume() (0)
#define mint_signal_fence_acquire() asm volatile("" ::: "memory")
#define mint_signal_fence_release() asm volatile("" ::: "memory")
#define mint_signal_fence_seq_cst() asm volatile("" ::: "memory")

#define mint_thread_fence_consume() (0)
#define mint_thread_fence_acquire() asm volatile("lwsync" ::: "memory")
#define mint_thread_fence_release() asm volatile("lwsync" ::: "memory")
#define mint_thread_fence_seq_cst() asm volatile("sync" ::: "memory")


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
    // CMPXCHG is written cmpxchgl because GCC (and Clang) uses AT&T assembler syntax.
    // Also due to AT&T syntax, the operands are swapped: %1 is the destination.
    // (This is the opposite of how Intel syntax lists the operands, where the destination comes first.)
    // "=a"(original) means the asm block outputs EAX to original, because CMPXCHG puts the old value in EAX.
    // "+m"(object->_nonatomic) is the memory address that is read/written. This becomes %1.
    // "q"(desired) puts desired into any of EBX, ECX or EDX before the block. This becomes %2.
    // "0"(expected) puts expected in the same register as "=a"(original), which is EAX, before the block.
    // Not putting "memory" in the clobber list because the operation is relaxed. It's OK for the compiler
    // to reorder this atomic followed by a load, for example. If the programmer wants to enforce ordering,
    // they will use an explicit fence.
    // http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.htlm
    // http://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html#Simple-Constraints
    // http://gcc.gnu.org/onlinedocs/gcc/Modifiers.html#Modifiers
    // http://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html#Machine-Constraints
    // http://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
    // http://download.intel.com/products/processor/manual/325383.pdf
    uint32_t original;
    asm volatile("again%=: lwarx %0, 0, %2\n"
				 "cmpw   0, %0, %3\n"
				 "bne-   out%=\n"
				 "stwcx. %1, 0, %2\n"
				 "bne-  again%=\n"
				 "out%=:   "
                 : "=&r"(original)
                 : "r"(desired), "r"(&object->_nonatomic), "r"(expected)
		         : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_add_32_relaxed(mint_atomic32_t *object, int32_t operand)
{
    // "=r"(original) chooses any general register, makes that %0, and outputs this register to original after the block.
    // "+m"(object->_nonatomic) is the memory address that is read/written. This becomes %1.
    // "0"(operand) puts operand into the same register as %0 before the block.
    // volatile is required. Otherwise, if the return value (original) is unused, the asm block
    // may be deleted. ("+m" is apparently not enough hint to the compiler that the asm
    // block has side effects on memory.)
    uint32_t original;
	register uint32_t temp;
    asm volatile("again%=:\n"
				 "lwarx  %0, 0, %3\n"
				 "add    %1, %2, %0\n"
				 "stwcx. %1, 0, %3\n"
				 "bne-  again%="
                 : "=&r"(original), "+r"(temp)
                 : "r"(operand), "r"(&object->_nonatomic)
		         : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_and_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    // The & in "=&a"(original) makes eax an earlyclobber operand.
    // If we don't specify &, the compiler may assign eax to input operand %3 as well.
    uint32_t original;
	register uint32_t temp;
    asm volatile("again%=:	lwarx %0, 0, %3\n" // Load into original from non-atomic
				 "      and    %1, %2, %0\n"
				 "      stwcx. %1, 0, %3\n"
				 "      bne-  again%="
                 : "=&a"(original), "=&r"(temp)
                 : "r"(operand), "r"(&object->_nonatomic)
				 : "cc", "memory");
    return original;
}

MINT_C_INLINE uint32_t mint_fetch_or_32_relaxed(mint_atomic32_t *object, uint32_t operand)
{
    uint32_t original;
    register uint32_t temp;
    asm volatile("again%=:	lwarx %0, 0, %3\n" // Load into original from non-atomic
				 "      or     %1, %2, %0\n"
				 "      stwcx. %1, 0, %3\n"
				 "      bne-  again%="
                 : "=&a"(original), "=&r"(temp)
                 : "r"(operand), "r"(&object->_nonatomic)
				 : "cc", "memory");
    return original;
}


#if MINT_CPU_POWERPC64
    //------------------------------------------------------------------------
    //  64-bit atomic operations on 64-bit processor (PPC64)
    //------------------------------------------------------------------------

    MINT_C_INLINE uint64_t mint_load_64_relaxed(mint_atomic64_t *object)
    {
        // On x64, aligned 64-bit loads are already atomic.
        return object->_nonatomic;
    }

    MINT_C_INLINE void mint_store_64_relaxed(mint_atomic64_t *object, uint64_t desired)
    {
        // On x64, aligned 64-bit stores are already atomic.
        object->_nonatomic = desired;
    }

    MINT_C_INLINE uint64_t mint_compare_exchange_strong_64_relaxed(mint_atomic64_t *object, uint64_t expected, uint64_t desired)
    {
        // On PPC64, we can work with 64-bit values directly.
        // It's the same as 32 bit
        uint64_t original;
		asm volatile("again%=: ldarx %0, 0, %1\n"
					 "       cmpd   0, %0, %3\n"
					 "       bne-   out%=\n"
					 "       stdcx. %2, 0, %1\n"
					 "       bne-  again%=\n"
					 "out%=:   "
					 : "=&r"(original), "+m"(object->_nonatomic)
					 : "r"(desired), "r"(expected)
					 : "cc", "memory");
        return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_add_64_relaxed(mint_atomic64_t *object, int64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("again%=:\n"
					 "ldarx  %0, 0, %3\n"
					 "add    %1, %2, %0\n"
					 "stdcx. %1, 0, %3\n"
					 "bne-  again%="
                 : "=&r"(original), "+r"(temp)
                 : "r"(operand), "r"(&object->_nonatomic)
		         : "cc", "memory");
	return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_and_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("again%=:	ldarx %0, 0, %3\n" // Load into original from non-atomic
					 "      and    %1, %2, %0\n"
					 "      stdcx. %1, 0, %3\n"
					 "      bne-  again%="
					 : "=&a"(original), "=&r"(temp)
					 : "r"(operand), "r"(&object->_nonatomic)
					 : "cc", "memory");
        return original;
    }

    MINT_C_INLINE uint64_t mint_fetch_or_64_relaxed(mint_atomic64_t *object, uint64_t operand)
    {
        uint64_t original;
		register uint64_t temp;
		asm volatile("again%=:	ldarx %0, 0, %3\n" // Load into original from non-atomic
					 "      or     %1, %2, %0\n"
					 "      stdcx. %1, 0, %3\n"
					 "      bne-  again%="
					 : "=&a"(original), "=&r"(temp)
					 : "r"(operand), "r"(&object->_nonatomic)
					 : "cc", "memory");
        return original;
    }

#else
    #error Unrecognized target CPU!
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_MINTOMIC_GCC_POWERPC_H__
