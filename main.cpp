#include <iostream>
#include  <iomanip>
#include <string>
#include "cache.h"

using namespace std;

#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)

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
	return (addr++)%(1024*64);
}

unsigned int memGen6()
{
	static unsigned int addr=0;
	return (addr+=32)%(64*4*1024);
}



string msg[2] = {"Miss","Hit"};

#define		NO_OF_Iterations	100		// CHange to 1,000,000
int main()
{
	unsigned int line_size;
	unsigned int hit = 0;
	cacheResType r;
	
	unsigned int addr;
	cout << "Direct Mapped Cache Simulator\n\nPlease input the line size: ";
	cin >> line_size; // receive the line size (variable)
	cout << "\n\n";
	cache cacheSim(line_size);

	for(int inst=0;inst<NO_OF_Iterations;inst++)
	{
		addr = memGen2(); // generate a random memory address
		r = cacheSim.cacheSimDM(addr); // attempt to retrieve this memory address from the cache
		if(r == cacheResType::HIT) hit++; // check if there was a hit or not
		cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[(unsigned int)r] <<")\n"; // output the requested address
	}
	cout << "Hit ratio = " << (100*hit/NO_OF_Iterations)<< endl; // output the hit ratio [miss ratio is 1 - HR; do we need to output it?]


	// should output the results to an excel sheet so we use it to create the graphss
}