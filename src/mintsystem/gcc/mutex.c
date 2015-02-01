#include <mintsystem/mutex.h>


int mint_mutex_init(mint_mutex_t *mutex)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#if defined (PTHREAD_MUTEX_RECURSIVE) || defined(__FreeBSD__)
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#else
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
    return pthread_mutex_init(mutex, &attr);
}

