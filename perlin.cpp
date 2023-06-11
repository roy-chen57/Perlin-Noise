#pragma once
#include "perlin.h"


Perlin::Perlin() : rand{ Lfsr(0b11111111) } {
	int num;
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);

	
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);
	
};

Perlin::Perlin(int seed) : rand{ Lfsr(seed, 8) } {
	int num;
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);

	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);
};

Perlin::Perlin(int seed, int bitlength) : rand{ Lfsr(seed, bitlength) } {
	int num;
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);

	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm.push_back(num);
	}
	perm.push_back(0);
};

// fade function defined by Ken Perlin in his paper
float Perlin::fade(float num) {
	// 6*num^5 - 15*num^4 + 10*num^3
	return ((6.0f * num - 15.0f) * num + 10.0f) * num * num * num;
}

float Perlin::lerp(float t, float u, float v) {
	return (1.0f - t) * u + t * v; //(not interchangable?)
}

// return a random constant gradient vector from
// (1,1), (-1,1), (-1,-1), (1,-1)
std::vector<float> Perlin::get_grad_vector(int num) {
	int mod = num % 3;
	switch (mod) {
	case 0:
		return std::vector<float>{1.0f, 1.0f};
	case 1:
		return std::vector<float>{-1.0f, 1.0f};
	case 2:
		return std::vector<float>{-1.0f, -1.0f};
	case 3:
		return std::vector<float>{1.0f, -1.0f};
	}
}

float Perlin::dot(std::vector<float> v1, std::vector<float> v2) {
	float res = 0;
	for (int i = 0; i < v1.size(); ++i) {
		res += v1[i] * v2[i];
	}
	return res;
}

// x, y absolute coordinate of the point from 0 to 1 (should not be integer)
float Perlin::generate(float x, float y) {
	int grid_x = floor(x);
	int grid_y = floor(y);

	float rel_x = x - grid_x;
	float rel_y = y - grid_y;

	// grid corner values that ensure neighbour grids that share the same
	// point also share the same value
	int val_topleft = perm[perm[grid_x] + grid_y + 1];
	int val_topright = perm[perm[grid_x + 1] + grid_y + 1];
	int val_botleft = perm[perm[grid_x] + grid_y];
	int val_botright = perm[perm[grid_x + 1] + grid_y];

	// vector from the corners of the grid to the input point
	std::vector<float> in_topleft{ rel_x, rel_y - 1.0f };
	std::vector<float> in_topright{ rel_x - 1.0f, rel_y - 1.0f };
	std::vector<float> in_botleft{ rel_x , rel_y };
	std::vector<float> in_botright{ rel_x - 1.0f, rel_y };

	std::vector<float> grad_botleft = Perlin::get_grad_vector(val_botleft);
	std::vector<float> grad_botright = Perlin::get_grad_vector(val_botright);

	// dot prouct of input and gradient vector for each corner of the grid
	float dot_topleft = Perlin::dot(in_topleft, Perlin::get_grad_vector(val_topleft));
	float dot_topright = Perlin::dot(in_topright, Perlin::get_grad_vector(val_topright));
	float dot_botleft = Perlin::dot(in_botleft, Perlin::get_grad_vector(val_botleft));
	float dot_botright = Perlin::dot(in_botright, Perlin::get_grad_vector(val_botright));

	// linear interpolation of left corner values
	float lerp_l = Perlin::lerp(Perlin::fade(rel_y),dot_botleft, dot_topleft);
	// linear interpolation of right corner values
	float lerp_r = Perlin::lerp(Perlin::fade(rel_y), dot_botright, dot_topright);
	// final linear interpolation
	float result = Perlin::lerp(Perlin::fade(rel_x), lerp_l, lerp_r);
	return result;
}

std::vector<int> Perlin::get_perm() { return perm; }

