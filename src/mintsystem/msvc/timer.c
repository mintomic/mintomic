#include <mintsystem/timer.h>


double mint_timer_ticksToSeconds = 0;
double mint_timer_secondsToTicks = 0;

void mint_timer_initialize()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    mint_timer_ticksToSeconds = 1.0 / freq.QuadPart;
    mint_timer_secondsToTicks = (double) freq.QuadPart;
}
