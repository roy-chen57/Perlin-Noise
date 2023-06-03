#include "prng.h"

// Default Constructor
Prng::Prng() {}
// Constructor
Prng::Prng(int seed) :
	seed{ seed } {}

// get_seed() returns the seed member variable
// void -> int 
int Prng::get_seed() const { return seed; }

// generate() virtual function for derived class to overwrite
int Prng::generate() { return 0; }

/*
	pow(base, exp) self defined exponent operatior. Raises the integer base
		to the power of the integer exp and returns the result.
	int, int -> int
*/
int Prng::pow(const int base, const int exp) const{
	int res = 1;
	for (int i = 0; i < exp; ++i) {
		res *= base;
	}
	return res;
}