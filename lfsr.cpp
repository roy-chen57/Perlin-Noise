#pragma once 
#include <iostream>
#include "lfsr.h"

// Default Constructor
Lfsr::Lfsr() : bitstr{ Prng::seed }, bitlength{ find_bitlength(bitstr) }{};
// Constructors
Lfsr::Lfsr(int seed) : bitstr{ seed }, bitlength{ find_bitlength(seed) }{};
Lfsr::Lfsr(int seed, int bitlength) : bitstr{ seed }, bitlength{ bitlength }{};

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
	// feedback function to determine the new bit
	// (guarantees a maximal cycle only for 8 bit seeds
	// x^8 + x^6 + x^5 + x + 1
	int feedback = state ^ ((bitstr >> 2) & 1) ^ ((bitstr >> 3) & 1) ^ ((bitstr >> 6) & 1);

	bitstr = bitstr >> 1;
	// append feedback bit to start of the bit string 
	bitstr += (feedback << (bitlength - 1));

	return state;
}

// generate a string of bits with half the length of the bitlength member variable
// void -> int
int Lfsr::generate() {
	int result = 0;
	for (int i = 0; i < bitlength; ++i) {
		result += (shift() << i);
	}
	return result;
}