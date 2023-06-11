#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lfsr.h"
#include "prng.h"
#include "perlin.h"

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
	int seed = 0b11110001;
	int bitlength = 8;
	//std::cout << "shifting 8: " << (seed >> 7) << std::endl;

	Lfsr rand = Lfsr(seed, bitlength);
	Perlin noise = Perlin(seed, bitlength);


	//std::cout << "(0.678431,5.89804): " << noise.generate(0.678431, 5.89804) << std::endl;
	//std::cout << "(1,1): " << noise.generate(1,1) << std::endl;

	std::ofstream ofile;
	ofile.open("../height.csv");
	

	int grid_num = 10;
	int grid_size = 5;
	for (int n = 0; n < grid_num*grid_size; ++n) {
		ofile << n << ',';
	}
	ofile << "\n";
	
	float x, y, res;
	for (int j = 0; j < grid_num; ++j) {
		for (int dy = 0; dy < grid_size; ++dy) {
		ofile << j*3 + dy << ',';
			for (int i = 0; i < grid_num; ++i) {
			//x = i + (rand.generate() / 255.0);
			//y = j + (rand.generate() / 255.0);
				for (int dx = 0; dx < grid_size; ++dx) {
					x = i + (1.0 * dx / grid_size) + 0.01;
					y = j + (1.0 * dy / grid_size) + 0.01;
					res = (noise.generate(x, y) + 1) / 2;
					//std::cout << '(' << x << ',' << y << "): " << res << std::endl;
					ofile << static_cast<int>(res * 255) << ',';
				}
			}
			ofile << "\n";
		}
	}
	ofile.close();
	
	/*
	Prng* test = new Lfsr(seed); // access lfsr's functions
	Lfsr rand = Lfsr(seed);

	int test_num = rand.generate();
	int test_num2 = test->generate(); // wrapper for generating number w/ lfsr
	std::cout << test_num << std::endl;
	std::cout << test_num2 << std::endl;


	delete test;
	*/
	/*
	Lfsr rand = Lfsr(seed, bitlength);
	int number;

	std::cout << "rand bitlength: " << rand.get_bitlength() << std::endl;

	std::cout << "generating number: ";
	number = rand.generate();
	std::cout << number << std::endl;
	std::cout << "Binary of number: ";
	print_bin(number, bitlength);
	std::cout << std::endl;
	
	int counts[256] = { 0 };
	for (int i = 0; i < 255; ++i) {
		number = rand.generate();
		counts[number] += 1;
		
	}
	
	for (int i = 0; i < 256; ++i) {
		std::cout << i << ": " << counts[i] << std::endl;
	}
	*/
}