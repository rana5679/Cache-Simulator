#include "Defs.h"

unsigned int rand_()
{
    unsigned int m_w = 0xABABAB55; /* must not be zero, nor 0x464fffff */
    unsigned int m_z = 0x05080902; /* must not be zero, nor 0x9068ffff */

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}