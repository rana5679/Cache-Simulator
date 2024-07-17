#include "cache.h"
#include <math.h>

using namespace std;

cache::cache(unsigned int line_size)
{
	m_offset_bits = log2(line_size);
	m_index_bits = log2(m_line_num); 
	m_line_num = m_cache_size / line_size;
	m_cacheMem = new line[m_line_num];
}

cache::~cache()
{
	delete[] m_cacheMem;
}

// Direct Mapped Cache Simulator
cacheResType cache::cacheSimDM(unsigned int addr)
{
	// This function accepts the memory address for the memory transaction and 
	// returns whether it caused a cache miss or a cache hit

	unsigned int index, tag;

	// we extract the index in the cache after ignoring the offset bits
	// line_num = index size
	index = (addr >> m_offset_bits) % m_line_num;
	// we extract the tag of the address
	tag = (addr >> m_offset_bits) / m_line_num;

	// if the line at that index is valid and has the tag we want, it's a hit
	if (m_cacheMem[index].v_bit && m_cacheMem[index].tag == tag)
		return cacheResType::HIT;

	// else if it's a miss, place the new tag at the index
	m_cacheMem[index].tag == tag;
	// and set the valid bit just in case
	m_cacheMem[index].v_bit = true;

	return cacheResType::MISS;
}

// Fully Associative Cache Simulator
cacheResType cache::cacheSimFA(unsigned int addr)
{
	// This function accepts the memory address for the read and 
	// returns whether it caused a cache miss or a cache hit

	// The current implementation assumes there is no cache; so, every transaction is a miss
	return cacheResType::MISS;
}