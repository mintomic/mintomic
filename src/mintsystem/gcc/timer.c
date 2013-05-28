#include <mintsystem/timer.h>


double mint_timer_secondsToTicks = 0;
double mint_timer_ticksToSeconds = 0;

void mint_timer_initialize()
{
#if MINT_IS_APPLE
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    mint_timer_secondsToTicks = 1e9 * info.denom / info.numer;
    mint_timer_ticksToSeconds = 1e-9 * info.numer / info.denom;
#else
    mint_timer_secondsToTicks = 1e9;
    mint_timer_ticksToSeconds = 1e-9;
#endif
}
