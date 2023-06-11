#pragma once
#include <vector>
#include "lfsr.h"

class Perlin {
	std::vector<int> perm;
	Lfsr rand;
	float fade(float num);
	float lerp(float t, float u, float v);
	std::vector<float> get_grad_vector(int num);
	float dot(std::vector<float> v1, std::vector<float> v2);
public:
	Perlin();
	Perlin(int seed);
	Perlin(int seed, int bitlength);
	float generate(float x, float y);
	std::vector<int> get_perm();
	
};