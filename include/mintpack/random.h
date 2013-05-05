#ifndef __MINTPACK_RANDOM_H__
#define __MINTPACK_RANDOM_H__

#include <mintomic/core.h>


//-------------------------------------
//  PseudoRandomNumberGenerator
//  Implements the Mersenne Twister, a PRNG with good randomness
//  in a small number of instructions.
//-------------------------------------
#define MT_IA  397
#define MT_LEN 624

class PseudoRandomNumberGenerator
{
    uint32_t m_buffer[MT_LEN];
    int m_index;

public:
    PseudoRandomNumberGenerator(uint32_t seed = -1);
    // Declare noinline so that the function call acts as a compiler barrier
    MINT_NO_INLINE uint32_t generateInt32();
    inline uint64_t generateInt64()
    {
        return ((uint64_t) generateInt32() << 32) | generateInt32();
    }
};


#endif // __MINTPACK_RANDOM_H__
