#ifndef __MINTPACK_THREAD_SYNCHRONIZER_H__
#define __MINTPACK_THREAD_SYNCHRONIZER_H__

#include <mintthreads/thread.h>
#include <mintthreads/semaphore.h>
#include <mintomic/mintomic.h>


//-------------------------------------
//  ThreadSynchronizer
//-------------------------------------
class ThreadSynchronizer
{
private:
    struct ThreadInfo
    {
        mint_thread_t thread;
        ThreadSynchronizer *parent;
        mint_sem_t *beginSema;
    };
    int m_numThreads;
    ThreadInfo* m_threadInfos;
    mint_atomic32_t m_syncRemaining;
    mint_sem_t* m_endSema;

    static void* threadStart(void* param);
    bool m_mustExit;
    void (*m_threadFunc)(int);
    void kickThreads();

public:
    ThreadSynchronizer(int numThreads);
    ~ThreadSynchronizer();
    void run(void (*func)(int));
};


#endif // __MINTPACK_THREAD_SYNCHRONIZER_H__
