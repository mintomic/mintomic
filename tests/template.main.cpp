#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mintpack/timewaster.h>
#include <mintsystem/timer.h>


typedef bool TestEntryFunc(int numThreads);

struct TestInfo
{
    const char* description;
    TestEntryFunc* func;
    int numThreads;
    bool allowFailure;
    bool selected;
};

${TEST_ENTRY_FUNCS}

TestInfo g_testInfos[] =
{
${TEST_INFOS}
};

int g_maxMemKb = -1;

struct TestGroup
{
    int numTests;
    int numPassed;
    int numSkipped;

    TestGroup()
    {
        numTests = 0;
        numPassed = 0;
        numSkipped = 0;
    }
    void addResult(bool success)
    {
        if (success)
            numPassed++;
        numTests++;
    }
    void skipped()
    {
        numSkipped++;
        numTests++;
    }
};

static bool selectTests(const char *start, const char *end, int numTests)
{
    char *numEnd = NULL;
    long from = strtol(start, &numEnd, 10);
    if (numEnd == start || from <= 0 || from > numTests)
    {
        return false;
    }
    long to = strtol(end, &numEnd, 10);
    if (numEnd == end || to < from || to > numTests)
    {
        return false;
    }

    for (int i = from; i <= to; ++i)
    {
        g_testInfos[i - 1].selected = true;
    }
    return true;
}

int main(int argc, char **argv)
{
    bool hasSelection = false;
    int numTests = sizeof(g_testInfos) / sizeof(g_testInfos[0]);
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strncmp(argv[i], "mem:", 4) == 0)
            {
                char *numEnd = NULL;
                g_maxMemKb = strtol(argv[i] + 4, &numEnd, 0);
                if (numEnd == argv[i] + 4 || g_maxMemKb <= 1)
                {
                    g_maxMemKb = -1;
                }
                else
                {
                    printf("Using iterative memory limit of %d KB.\n", g_maxMemKb);
                }
                continue;
            }

            char *dash = strchr(argv[i], '-');
            if (dash != NULL)
            {
                hasSelection = selectTests(argv[i], dash + 1, numTests) || hasSelection;
            }
            else
            {
                hasSelection = selectTests(argv[i], argv[i], numTests) || hasSelection;
            }
        }
    }

    mint_timer_initialize();
    TimeWaster::Initialize();

    TestGroup required, optional;
    for (int i = 0; i < numTests; i++)
    {
        TestInfo& info = g_testInfos[i];

        TestGroup& group = info.allowFailure ? optional : required;
        if (!hasSelection || info.selected)
        {
            printf("[%d/%d] Test \"%s\"...", i + 1, numTests, info.description);

            mint_timer_tick_t start = mint_timer_get();
            bool success = info.func(info.numThreads);
            mint_timer_tick_t end = mint_timer_get();

            const char* status = success ? "pass" : info.allowFailure ? "fail (allowed)" : "*** FAIL ***";
            printf(" %s, %.3f ms\n", status, (end - start) * mint_timer_ticksToSeconds * 1000);

            group.addResult(success);
        }
        else
        {
            group.skipped();
        }
    }

    printf("\n----- Summary: -----\n");
    printf("Out of the tests required to pass, %d/%d passed.\n", required.numPassed, required.numTests - required.numSkipped);
    printf("Out of the tests allowed to fail, %d/%d passed.\n", optional.numPassed, optional.numTests - optional.numSkipped);

    return (required.numPassed == required.numTests) ? 0 : 1;
}
