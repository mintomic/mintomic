#ifndef __MINTSYSTEM_PRIVATE_TID_GCC_H__
#define __MINTSYSTEM_PRIVATE_TID_GCC_H__

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


//-------------------------------------
//  Thread IDs
//-------------------------------------
typedef pthread_t mint_tid_t;

MINT_C_INLINE mint_tid_t mint_get_current_thread_id()
{
    return pthread_self();
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTSYSTEM_PRIVATE_TID_GCC_H__
