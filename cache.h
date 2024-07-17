#pragma once
#include "Defs.h"

class cache {


	struct line { // lines in the cache
		bool v_bit = 0; // the valid bit
		int tag;
	};
	line* m_cacheMem; // the cache memory
	const unsigned int m_cache_size = 64 * 1024; // cache size is 64 Kbytes
	unsigned int m_line_size;
	unsigned int m_offset_bits; 
	unsigned int m_line_num;
	
	

public:
	cache(unsigned int);
	~cache();
	cacheResType cacheSimDM(unsigned int addr);
	cacheResType cacheSimFA(unsigned int addr);
};

