#include <mintomic/mintomic.h>
#include <mintpack/threadsynchronizer.h>
#include <algorithm>


#cmakedefine01 TEST_FORCE_FAIL

static mint_atomic${TEST_INT_BITSIZE}_t g_sharedInt = { 0 };
static uint${TEST_INT_BITSIZE}_t* g_valuesSeen = NULL;
static const int kValuesPerThread = 100000;

static void threadFunc(int threadNum)
{
    int base = kValuesPerThread * threadNum;
    for (int i = base + 1; i <= base + kValuesPerThread; i++)
    {
#if TEST_FORCE_FAIL
        mint_signal_fence_seq_cst();    // Make the compiler keep the next two lines on every iteration of the loop
        uint${TEST_INT_BITSIZE}_t oldValue = mint_load_${TEST_INT_BITSIZE}_relaxed(&g_sharedInt);
        mint_store_${TEST_INT_BITSIZE}_relaxed(&g_sharedInt, i);
#else
        uint${TEST_INT_BITSIZE}_t oldValue = mint_exchange_${TEST_INT_BITSIZE}_relaxed(&g_sharedInt, i);
#endif
        g_valuesSeen[i] = oldValue;
    }
}

bool ${TEST_FUNC}(int numThreads)
{
    g_sharedInt._nonatomic = 0;
    int numValues = kValuesPerThread * numThreads + 1;
    g_valuesSeen = new uint${TEST_INT_BITSIZE}_t[numValues];
    ThreadSynchronizer threads(numThreads);
    threads.run(threadFunc);
    g_valuesSeen[0] = g_sharedInt._nonatomic;
    std::sort(g_valuesSeen, g_valuesSeen + numValues);
    bool success = true;
    for (int i = 0; i < numValues; i++)
    {
        success = success && (g_valuesSeen[i] == i);
    }
    delete[] g_valuesSeen;
    g_valuesSeen = NULL;
    return success;
}
