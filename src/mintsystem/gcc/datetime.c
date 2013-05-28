#include <mintsystem/datetime.h>
#include <time.h>


uint64_t mint_get_current_utc_time()
{
    struct timespec tick;
    clock_gettime(CLOCK_REALTIME, &tick);
    return (uint64_t) tick.tv_sec * 1000000ull + tick.tv_nsec / 1000 + 11644473600000000ull;
}

