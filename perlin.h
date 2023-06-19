#pragma once
#include <vector>
#include "lfsr.h"

class Perlin {
	std::vector<int> perm;
	Lfsr rand;
	int grid_size;
	int grid_num;
	float fade(float num);
	float lerp(float t, float u, float v);
	std::vector<float> get_grad_vector(int num);
	float dot(std::vector<float> v1, std::vector<float> v2);
	float calc_pt(float x, float y);
public:
	Perlin();
	Perlin(int seed);
	Perlin(int seed, int grid_size);
	Perlin(int seed, int grid_size, int grid_num);
	
	std::vector<std::vector<float> > generate();
	std::vector<std::vector<float> > generate_fractal(int octaves, int lacunarity, float persistence);
	std::vector<int> get_perm();
	int get_grid_size();
	int get_grid_num();
	void set_grid_size(const int size);
	void set_grid_num(const int num);
};