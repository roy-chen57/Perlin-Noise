#include <iostream>
#include "lfsr.h"

// Default Constructor
Lfsr::Lfsr() : bitstr{ Prng::seed }, bitlength{ find_bitlength(bitstr) }{};
// Constructor
Lfsr::Lfsr(int seed) : bitstr{ seed }, bitlength{ find_bitlength(seed) }{};

/*
	find_bitlength(num) takes an integer num and returns the length of 
		the binary string representation of num
	const int -> int
*/
int Lfsr::find_bitlength(const int num) {
	int i = 0;
	while (num >= Prng::pow(2, i)) {
		++i;
	}
	return i;
}


// get_bitstr() returns the value of the bitstr member variable
// void -> int
int Lfsr::get_bitstr() { return bitstr; }
// get_bitlength() returns the value of the bitlength member variable
// void -> int
int Lfsr::get_bitlength() { return bitlength; }



/*
	shift(num) right-shifts the bitstr member variable by one positon(loses the rightmost bit)
		and appends a new bit to the left of bitstr and returns the bit popped off the bitstr
	MUTATION: changes the value of bitstr member variable
	void -> int
*/
int Lfsr::shift() {
	int state = (bitstr & 1); //last bit of num
	bitstr = bitstr >> 1;
	// feedback function to determine the new bit
	int feedback = state ^ ((bitstr >> 2) & 1);
	// append feedback bit to start of the bit string 
	bitstr += (feedback << (bitlength - 1));
	return state;
}

// generate a string of bits with half the length of the bitlength member variable
// void -> int
int Lfsr::generate() {
	int result = 0;
	for (int i = 0; i < bitlength/2; ++i) {
		result += (shift() << i);
	}
	return result;
}