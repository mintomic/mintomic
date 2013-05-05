#include <mintpack/random.h>
#include <mintomic/mintomic.h>

PseudoRandomNumberGenerator::PseudoRandomNumberGenerator(uint32_t seed)
{
    if (seed == (uint32_t) -1)
    {
        static mint_atomic32_t sharedSeed = { 0 };
        seed = mint_fetch_add_32_relaxed(&sharedSeed, 1);
    }

    // Initialize by filling with the seed, then iterating
    // the algorithm a bunch of times to shuffle things up.
    for (int i = 0; i < MT_LEN; i++)
        m_buffer[i] = seed;
    m_index = 0;
    for (int i = 0; i < MT_LEN * 100; i++)
        generateInt32();
}

uint32_t PseudoRandomNumberGenerator::generateInt32()
{
    // Indices
    int i = m_index;
    int i2 = m_index + 1; if (i2 >= MT_LEN) i2 = 0; // wrap-around
    int j = m_index + MT_IA; if (j >= MT_LEN) j -= MT_LEN; // wrap-around

    // Twist
    uint32_t s = (m_buffer[i] & 0x80000000) | (m_buffer[i2] & 0x7fffffff);
    uint32_t r = m_buffer[j] ^ (s >> 1) ^ ((s & 1) * 0x9908B0DF);
    m_buffer[m_index] = r;
    m_index = i2;

    // Swizzle
    r ^= (r >> 11);
    r ^= (r << 7) & 0x9d2c5680UL;
    r ^= (r << 15) & 0xefc60000UL;
    r ^= (r >> 18);
    return r;
}
