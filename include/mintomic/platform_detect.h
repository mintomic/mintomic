#ifndef __MINTOMIC_PLATFORM_DETECT_H__
#define __MINTOMIC_PLATFORM_DETECT_H__


#if defined(_WIN32)
    // MSVC compiler family
    #define MINT_COMPILER_MSVC 1
    #if _MSC_VER >= 1600
        // <stdint.h> is only available in VS2010 and later
        #define MINT_HAS_STDINT 1
    #endif
    #if _XBOX_VER >= 200
        // Xbox 360
        #define MINT_TARGET_XBOX_360 1
        #define MINT_CPU_POWERPC 1
        #define MINT_PTR_SIZE 4
    #else
        #if defined(_M_X64)
            // x64
            #define MINT_CPU_X64 1
            #define MINT_PTR_SIZE 8
        #elif defined(_M_IX86)
            // x86
            #define MINT_CPU_X86 1
            #define MINT_PTR_SIZE 4
        #else
            #error Unrecognized platform!
        #endif
    #endif

#elif defined(__GNUC__)
    // GCC compiler family
    #define MINT_COMPILER_GCC 1
    #define MINT_HAS_STDINT 1
    #if defined(__llvm__)
        // LLVM
        #define MINT_COMPILER_LLVM 1
        #if __has_feature(c_atomic)
            // No need to mark mint_atomic##_t members as volatile
            #define MINT_HAS_C11_MEMORY_MODEL 1
        #endif
    #endif
    #if defined(__APPLE__)
        // Apple MacOS/iOS
        #define MINT_IS_APPLE 1
    #endif
    #if defined(__x86_64__)
        // x64
        #define MINT_CPU_X64 1
        #define MINT_PTR_SIZE 8
    #elif defined(__i386__)
        // x86
        #define MINT_CPU_X86 1
        #define MINT_PTR_SIZE 4
    #elif defined(__arm__)
        // ARM
        #define MINT_CPU_ARM 1
        #if defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
            // ARMv7
            #define MINT_CPU_ARM_VERSION 7
            #define MINT_PTR_SIZE 4
        #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
            // ARMv6
            #define MINT_CPU_ARM_VERSION 6
            #define MINT_PTR_SIZE 4
        #else
            // Could support earlier ARM versions at some point using compiler barriers and swp instruction
            #error Unrecognized ARM CPU architecture version!
        #endif
        #if defined(__thumb__)
            // Thumb instruction set mode
            #define MINT_CPU_ARM_THUMB 1
        #endif
	#elif (defined(__powerpc__) || defined (_ARCH_PPC)) && defined (__64BIT__)
        // Only supporting 64bit at the moment, so making the define include 64 for clarity
		#define MINT_CPU_POWERPC64 1
		#define MINT_PTR_SIZE 8
    #elif (defined(__sparc__) && defined (__arch64__))
        // Only supporting 64bit at the moment, so making the define include 64 for clarity
		#define MINT_CPU_SPARC64 1
		#define MINT_PTR_SIZE 8
    #elif (defined(__s390__))
		#if (defined(__s390x__))
			#define MINT_CPU_S390X 1
			#define MINT_PTR_SIZE 8
		#else
			#define MINT_CPU_S390 1
			#define MINT_PTR_SIZE 4
		#endif

    #else
        #error Unrecognized target CPU!
    #endif
#elif defined (__IBMC__) || defined (__IBMCPP__)
    #define MINT_COMPILER_XLC 1
    #define MINT_HAS_STDINT 1
    #if defined(__370__)
        #if defined(__64BIT_)
             #error 64 bit S390 not implemented yet on zOS
             #define MINT_CPU_S390X 1
             #define MINT_PTR_SIZE 8
        #else
             #define MINT_CPU_S390 1
             #define MINT_PTR_SIZE 4
        #endif
    #else
        #error Unrecognised target CPU!
    #endif
#else
    #error Unrecognized compiler!
#endif


#endif // __MINTOMIC_PLATFORM_DETECT_H__
