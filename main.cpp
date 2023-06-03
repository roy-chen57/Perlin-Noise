#include <iostream>
#include <string>
#include "lfsr.h"
#include "prng.h"

const int BITLENGTH = 8;


// raise the integer base to the power of the integer exp
int pow(const int base, const int exp) {
	int res = 1;
	for (int i = 0; i < exp; ++i) {
		res *= base;
	}
	return res;
}

int find_bitlength(const int num) {
	int i = 0;
	while (num >= pow(2, i)) {
		++i;
	}
	return i;
}
// outputs the integer array of size 4
void print_bin(int num, const int len) {
	int i = len - 1; // array index

	while (i >= 0) {
		if (num >= pow(2, i)) { //if num is larger than 2^i, then ith bit is 1
			std::cout << 1;
			num -= pow(2, i);
		}
		else {
			std::cout << 0;
		}
		--i;
	}
}


int main(){
	int seed = 0b10110101;
	/*
	Prng* test = new Lfsr(seed); // access lfsr's functions
	Lfsr rand = Lfsr(seed);

	int test_num = rand.generate();
	int test_num2 = test->generate(); // wrapper for generating number w/ lfsr
	std::cout << test_num << std::endl;
	std::cout << test_num2 << std::endl;


	delete test;
	*/
	
	Lfsr rand = Lfsr(seed);
	int number;

	std::cout << "rand bitlength: " << rand.get_bitlength() << std::endl;

	std::cout << "generating number: ";
	number = rand.generate();
	std::cout << number << std::endl;
	std::cout << "Binary of number: ";
	print_bin(number, 4);
	std::cout << std::endl;

	int counts[16] = { 0 };
	for (int i = 0; i < 100000; ++i) {
		switch (rand.generate()) {
			case 0:
				counts[0]++;
				break;
			case 1:
				counts[1]++;
				break;
			case 2:
				counts[2]++;
				break;
			case 3:
				counts[3]++;
				break;
			case 4:
				counts[4]++;
				break;
			case 5:
				counts[5]++;
				break;
			case 6:
				counts[6]++;
				break;
			case 7:
				counts[7]++;
				break;
			case 8:
				counts[8]++;
				break;
			case 9:
				counts[9]++;
				break;
			case 10:
				counts[10]++;
				break;
			case 11:
				counts[11]++;
				break;
			case 12:
				counts[12]++;
				break;
			case 13:
				counts[13]++;
				break;
			case 14:
				counts[14]++;
				break;
			case 15:
				counts[15]++;
				break;
		}
	}
	
	for (int i = 0; i < 16; ++i) {
		std::cout << i << ": " << counts[i] << std::endl;
	}
	/*
	char input;
	bool loop = true;
	while (loop) {
		try {
			std::cin >> input;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			continue;
		}

		switch (input) {
		case 'g':
			std::cout << "generating number: ";
			number = rand.generate();
			std::cout << number << std::endl;
			std::cout << "Binary of number: ";
			print_bin(number, 4);
			std::cout << std::endl;
			break;
		case 'q':
			loop = false;
			break;
		case 's':
			std::cout << "Current bitstring: ";
			print_bin(rand.get_bitstr(), 8);
			std::cout << std::endl;
			break;
		default:
			std::cout << "Unknown Command" << std::endl;
		}
		

		
	}

	bool mainloop = true;

	//seed for 8 bit numbers
	int b = 0b01010010;
	int bitlength;
	int state;
	int feedback;

	std::cout << "length of bit string: ";
	std::cin >> bitlength;

	int max = pow(2, bitlength) - 1;
	
	std::cout << "bitlength: " << bitlength << std::endl;

	std::cout << "initial state\t\t" << b << "\t";
	print_bin(b, bitlength);
	std::cout << std::endl;
	int four_bit[4] = { 0 };
	int i = 0;

	while (max > 0) {
		state = b & 1; // last bit of b
		b = b >> 1; // right shift b by one bit (discards last bit)
		feedback = state ^ ((b >> 2) & 1);
		b += (feedback << (bitlength - 1)); //add feedback bit to the leftmost position of b

		std::cout << "(b:binary of b:state)\t" << b << "\t";
		print_bin(b, bitlength);
		std::cout << ":" << state << std::endl;

		//std::cout << state;
		four_bit[i] = state;
		++i;
		if (i == 4) { 
			i = 0; 
			std::cout << ((four_bit[0] << 3) + 
						 (four_bit[1] << 2) + 
						 (four_bit[2] << 1) + 
						  four_bit[3]) << std::endl;
		}
		
		--max;
	}
	*/
}