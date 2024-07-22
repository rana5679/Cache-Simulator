#include <iostream>
#include  <iomanip>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024) // 64 Mbytes
#define		CACHE_SIZE		(64*1024) // 64 Kbytes

enum class cacheResType {MISS=0, HIT=1}; // types of cache results
unsigned int rep;

// lines in the cache
struct line
{ 
	bool v_bit = 0; // the valid bit
	int tag; // the tag stored in the cache
};

/* Global variables */
line* cache; // the cache memory
unsigned int line_num,line_size, offset_bits; // cache properties extracted at the beginning



/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55;    /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902;    /* must not be zero, nor 0x9068ffff */
unsigned int rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

/* the following functions generate the memory access behavior of 6 benchmark programs*/

unsigned int memGen1()
{
	static unsigned int addr=0;
	return (addr++)%(DRAM_SIZE);
}

unsigned int memGen2()
{
	static unsigned int addr=0;
	return  rand_()%(24*1024);
}

unsigned int memGen3()
{
	return rand_()%(DRAM_SIZE);
}

unsigned int memGen4()
{
	static unsigned int addr=0;
	return (addr++)%(4*1024);
}

unsigned int memGen5()
{
	static unsigned int addr=0;
	return (addr++)%(64*1024);
}

unsigned int memGen6()
{
	static unsigned int addr=0;
	return (addr+=32)%(64*4*1024);
}


// Direct Mapped Cache Simulator
cacheResType cacheSimDM(unsigned int addr)
{	
	// This function accepts the memory address for the memory transaction and 
	// returns whether it caused a cache miss or a cache hit

	unsigned int index, tag;
	// we extract the index and the tag after ignoring the offset bits (dividing by line size)
	// line_num = index size
	index = (addr / line_size) % line_num;
	// we extract the tag of the address
	tag = (addr / line_size) / line_num;
	// cout << tag << "\t" << index << "\t" << cache[index].v_bit << "\t" << cache[index].tag << "\t";
	// if the line at that index is valid and has the tag we want, it's a hit
	if (cache[index].v_bit && cache[index].tag == tag)
		return cacheResType::HIT;

	// else if it's a miss, place the new tag at the index
	cache[index].tag = tag;
	// and set the valid bit just in case
	cache[index].v_bit = true;

	return cacheResType::MISS;
}

// Fully Associative Cache Simulator
cacheResType cacheSimFA(unsigned int addr)
{	
	//cout << rep << "\t";
	unsigned int tag;
	tag = addr / line_size;

	// reads the tags of the cache lines sequencially 
	for(int i=0; i<line_num; i++)
		{
			// checks if the tag exists in the cache if it does then its a hit
			if(cache[i].v_bit && cache[i].tag == tag)
			{
				return cacheResType::HIT;
			}
			// if it does not exist in the cache then it adds it to the first available space in the cache
			if(cache[i].v_bit == 0)
			{
				cache[i].tag = tag;
				cache[i].v_bit = true;
				return cacheResType::MISS;
			}
					
		}

	// if there is no space left and no hit then it overwrites a random cache line
	cache[rand_() % line_num].tag = tag;
	//rep = rep % line_num; 
	//cache[rep].tag = tag; 
	//rep++;
	return cacheResType::MISS;
}

string msg[2] = {"Miss","Hit"};

#define		NO_OF_Iterations	1000000		// CHange to 1,000,000
int main(int argc, char *argv[])
{
	rep = 0; 
	unsigned int hit = 0;
	cacheResType r;
	
	unsigned int addr;
    unsigned char cache_type;

	cout << "Cache Simulator\n\nPlease input the line size: ";
	cin >> line_size; // receive the line size
	cout << "\n\n";

	// extracting cache properties
	offset_bits = log2(line_size);
	line_num = CACHE_SIZE / line_size;
	cache = new line[line_num];

	// determining the cache type
	cout << "Which [cache type] would you prefer to use?\n DM: 0\n FA: 1\nInput: ";
	cin >> cache_type;

	// validation function to ensure that the input character is correct
	while (cache_type != '0' && cache_type != '1') 
	{
		cout << "Invalid input\n Try again: ";
		cin >> cache_type;
	}

	//we have a file input 
	if (argc > 1)
	{	
		string line_temp;
		ifstream dataFile;
		dataFile.open(argv[1], ios::in);
		if (dataFile.is_open())
		{
			int count = 0;
			switch(cache_type)
			{
				case '0':
					while(getline(dataFile,line_temp))
					{
						addr = (unsigned int)(stoi(line_temp));
						r = cacheSimDM(addr); // attempt to retrieve this memory address from the cache
						if (r == cacheResType::HIT) hit++; // check if there was a hit or not
						cout << "0x" << setfill('0') << setw(8) << hex << addr << " (" << msg[(unsigned int)r] << ")\n"; // output the requested address
						count++;
					}
				break; 

				case '1':
					while(getline(dataFile,line_temp))
					{
						addr = (unsigned int)(stoi(line_temp)); 
						r = cacheSimFA(addr); // attempt to retrieve this memory address from the cache
						if (r == cacheResType::HIT) hit++; // check if there was a hit or not
						cout << "0x" << setfill('0') << setw(8) << hex << addr << " (" << msg[(unsigned int)r] << ")\n"; // output the requested address
						count++;
					}
				break;
			}
			cout << "Hit ratio = " << dec <<(100*hit/count)<< endl; 

		}
		else 
		{
			cout << "\nThe File cannot be opened\n"; 
			exit(0);
		}
	}
	else 
	{
		// Running the simulation
		// switch case for the cache types to avoid changing the code as much as possible
		switch (cache_type) 
		{
			case '0': 
				for (int inst = 0; inst < NO_OF_Iterations; inst++)
				{
					addr = memGen1(); // generate a random memory address [6 possible generators]
					r = cacheSimDM(addr); // attempt to retrieve this memory address from the cache 
					if (r == cacheResType::HIT) hit++; // check if there was a hit or not
					cout << "0x" << setfill('0') << setw(8) << hex << addr << " (" << msg[(unsigned int)r] << ")\n"; // output the requested address
				}
				break;
			case '1':
				for (int inst = 0; inst < NO_OF_Iterations; inst++)
				{
					addr = memGen1(); // generate a random memory address [6 possible generators]
					r = cacheSimFA(addr); // attempt to retrieve this memory address from the cache
					if (r == cacheResType::HIT) hit++; // check if there was a hit or not
					cout << "0x" << setfill('0') << setw(8) << hex << addr << " (" << msg[(unsigned int)r] << ")\n"; // output the requested address
				}
				break;
		}
		cout << "Hit ratio = " << dec <<(100*hit/NO_OF_Iterations)<< endl; 
	}

	delete[] cache;
}
