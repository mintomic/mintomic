#include <mintomic/mintomic.h>
#include <mintpack/threadsynchronizer.h>
#include <stdio.h>

extern int g_maxMemKb;

struct Node
{
    Node* next;
};

static mint_atomicPtr_t g_head;
static int g_iterations = 2000000;

static void threadFunc(int threadNum)
{
    for (int i = 0; i < g_iterations; i++)
    {
        Node* insert = new Node;
        Node* h;
        do
        {
            h = (Node*) mint_load_ptr_relaxed(&g_head);
            insert->next = h;
        }
        while (mint_compare_exchange_strong_ptr_relaxed(&g_head, h, insert) != h);
    }
}

bool ${TEST_FUNC}(int numThreads)
{
    if (g_maxMemKb > 1)
    {
        int iter = (g_maxMemKb * 1024 / sizeof(Node)) / numThreads;
        if (iter < g_iterations)
        {
            g_iterations = iter;
        }
    }

    g_head._nonatomic = NULL;
    ThreadSynchronizer threads(numThreads);
    threads.run(threadFunc);
    int count = 0;
    while (g_head._nonatomic)
    {
        Node* t = (Node*) g_head._nonatomic;
        g_head._nonatomic = t->next;
        // If this loop runs too slowly in Windows,
        // make sure to set the environment variable _NO_DEBUG_HEAP to 1,
        // or run without the debugger attached.
        delete t;
        count++;
    }

    return count == g_iterations * numThreads;
}
