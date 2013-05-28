#ifndef __MINTPACK_RANDOM_H__
#define __MINTPACK_RANDOM_H__

#include <mintomic/mintomic.h>


//-------------------------------------
//  PRNG that seeds itself using various information from the environment.
//  generate() is uniformly distributed across all 32-bit integer values.
//  generateUnique() returns unique integers 2^32 times in a row, then repeats the sequence.
//-------------------------------------
class Random
{
private:
    static const int kNumOffsets = 8;
    static mint_atomic32_t m_sharedCounter;
    uint32_t m_value;
    uint32_t m_offsets[kNumOffsets];

public:
    Random();
    uint32_t generate();
    uint32_t generateUnique();
};


#endif // __MINTPACK_RANDOM_H__
