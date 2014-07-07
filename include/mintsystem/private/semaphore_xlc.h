#ifndef __MINTSYSTEM_PRIVATE_SEMAPHORE_XLC_H__
#define __MINTSYSTEM_PRIVATE_SEMAPHORE_XLC_H__

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	pthread_cond_t cv;
	pthread_mutex_t mtx;
	int value;
}
mint_sem_t;

#define MINT_SEM_FAILED ((mint_sem_t *) NULL)

mint_sem_t *mint_sem_create();
int mint_sem_destroy(mint_sem_t *sem);
int mint_sem_wait(mint_sem_t *sem);
int mint_sem_post(mint_sem_t *sem);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTSYSTEM_PRIVATE_SEMAPHORE_XLC_H__
