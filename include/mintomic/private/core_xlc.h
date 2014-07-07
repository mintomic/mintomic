#ifndef __MINTOMIC_PRIVATE_CORE_XLC_H__
#define __MINTOMIC_PRIVATE_CORE_XLC_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Alignment
//-------------------------------------
#define MINT_DECL_ALIGNED(declaration, amt) error Not Available


//-------------------------------------
//  Inlining
//-------------------------------------
#define MINT_C_INLINE inline
#define MINT_NO_INLINE


//-------------------------------------
//  Thread local
//-------------------------------------
#define MINT_THREAD_LOCAL error Not Available


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_PRIVATE_CORE_XLC_H__
