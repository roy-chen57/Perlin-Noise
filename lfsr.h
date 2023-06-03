#pragma once
#include "prng.h"

class Lfsr : public Prng{
	int bitstr;
	int bitlength;
	int shift();
	int find_bitlength(const int num);
public:
	Lfsr();
	Lfsr(int seed);
	
	int get_bitstr();
	int get_bitlength();
	int generate();
};