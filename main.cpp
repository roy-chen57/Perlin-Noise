#include <iostream>
#include <fstream>
#include <vector>
#include "lfsr.h"
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
	//int bitlength = 8;

	// number of grids in the final image
	int grid_num = 2;
	// number of input points in each grid
	int grid_size = 100;

	//Lfsr rand = Lfsr(seed, bitlength);
	Perlin noise = Perlin(seed, grid_size, grid_num);

	std::ofstream ofile;
	ofile.open("../height.csv");
	

	// creates column name for the csv output file
	for (int n = 0; n < grid_num * grid_size; ++n) {
		ofile << n << ',';
	}
	ofile << "\n";


	//std::vector<std::vector<int> > pixels = noise.generate();
	std::vector<std::vector<float> > pixels = noise.generate_fractal(8,2,0.5);

	for (int dy = 0; dy < grid_num * grid_size; ++dy) {
		ofile << dy << ',';//create row name for csv output file
		for (int dx = 0; dx < grid_num * grid_size; ++dx) {
			ofile << static_cast<int>((pixels[dy][dx]+1)/2 * 255) << ',';
		}
		ofile << "\n";
	}

	ofile.close();
	
	
}