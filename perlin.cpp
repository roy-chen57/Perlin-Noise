#pragma once
#include "perlin.h"


//default constructor
Perlin::Perlin() : rand{ Lfsr(0b11111111) } {
	int num;
	perm.resize(512);
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm[i] = num;
		perm[i + 256] = num;
	}
	perm[255] = 0;
	perm[511] = 0;

	grid_num = 10;
	grid_size = 5;
};

//overloaded constructors
Perlin::Perlin(int seed) : rand{ Lfsr(seed, 8) }, grid_size{ 5 }, grid_num{ 10 }
{
	int num;
	perm.resize(512);
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm[i] = num;
		perm[i + 256] = num;
	}
	perm[255] = 0;
	perm[511] = 0;

	grid_num = 10;
	grid_size = 5;
};
Perlin::Perlin(int seed, int grid_size) : rand{ Lfsr(seed, 8) }, grid_size{ grid_size }, grid_num{ 10 }
{
	int num;
	perm.resize(512);
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm[i] = num;
		perm[i + 256] = num;
	}
	perm[255] = 0;
	perm[511] = 0;
};
Perlin::Perlin(int seed, int grid_size, int grid_num) : rand{ Lfsr(seed,8) }, grid_size{ grid_size }, grid_num{ grid_num }
{
	int num;
	perm.resize(512);
	for (int i = 0; i < 255; i++) {
		num = rand.generate();
		perm[i] = num;
		perm[i + 256] = num;
	}
	perm[255] = 0;
	perm[511] = 0;
}

// fade(num): original fade function that smooths boundaries
//		between grid borders defined by Ken Perlin
// float -> float
float Perlin::fade(float num) {
	// 6*num^5 - 15*num^4 + 10*num^3
	return ((6.0f * num - 15.0f) * num + 10.0f) * num * num * num;
}

/*
lerp(t, u, v): self-implemented linear interpolation function
float, float, float -> float
*/
float Perlin::lerp(float t, float u, float v) {
	return (1.0f - t) * u + t * v;
}

// get_grad_vector(num): return a pseudo random 2D constant gradient vector from 
//		(1,1), (-1,1), (-1,-1), (1,-1) from a given integer num
// int -> std::vector<float>[2]
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

// dot(v1, v2): self-implemented vector dot product
// std::vector<float>[2], std::vector<float>[2] -> float
// NOTE: requires v1 and v2 to be of the same size
float Perlin::dot(std::vector<float> v1, std::vector<float> v2) {
	float res = 0;
	for (int i = 0; i < v1.size(); ++i) {
		res += v1[i] * v2[i];
	}
	return res;
}

/*
calc_pt(x, y): computes the Perlin noise value
	at the x, y point
float, float -> float
NOTE: 
	- output of calc_pt function is roughly bound by [-1.0,1.0]
	- whole number part of x and y can be seen as the influence grid the 
		point is part of, while the decimal part represents the relative position
		of the point within the grid
*/
float Perlin::calc_pt(float x, float y) {
	// grid tag coordinate x, y falls into
	int grid_x = floor(x);
	int grid_y = floor(y);

	// coordinate of x,y relative to the coordinate of the grid
	float rel_x = x - grid_x;
	float rel_y = y - grid_y;

	// grid corner values that ensure neighbour grids that share the same
	// point also share the same value
	int val_topleft = perm[perm[grid_x] + grid_y + 1];
	int val_topright = perm[perm[grid_x + 1] + grid_y + 1];
	int val_botleft = perm[perm[grid_x] + grid_y];
	int val_botright = perm[perm[grid_x + 1] + grid_y];

	// vector from the corners of the grid to the input x,y
	std::vector<float> in_topleft{ rel_x, rel_y - 1.0f };
	std::vector<float> in_topright{ rel_x - 1.0f, rel_y - 1.0f };
	std::vector<float> in_botleft{ rel_x , rel_y };
	std::vector<float> in_botright{ rel_x - 1.0f, rel_y };

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

/*
generate(): returns a matrix of pixels generated through the perlin noise algorithm
void -> std::vector<std::vector<float> >
*/
std::vector<std::vector<float> > Perlin::generate() {
	std::vector<std::vector<float> > res;
	float x, y;
	
	// spreads out x, y entries within each grid
	float incr = 1.0 / grid_size;

	for (int j = 0; j < grid_size*grid_num; ++j) {
		std::vector<float> row;
		y = j * incr + 0.0001;
		for (int i = 0; i < grid_size*grid_num; ++i) {
			x = i * incr + 0.0001;
			row.push_back(calc_pt(x, y));
		}
		res.push_back(row);
	}

	return res;
}

/*
generate_fractal(octaves, lacunarity, persistence): returns a matrix of pixels generated
	with fractal noise using perlin noise for each layer.
int, int, int -> std::vector<std::vector<float> >
PARAMETERS:
	octaves: number of octaves(layers) to blend
	lacunarity: increases the sparseness of samples within each grid 
		("reduces" grid_size by 1/lacunarity and "doubles" grid_num by lacunarity)
	persistence: decrease/increase in weight of each following layer
NOTE:
	- persistence value between 0 and 1 reduces the effect of each following layer. persistence should be positive
	- integer values for lacunarity increases the sparseness by the multiple of the integer
		( i.e. lacunarity of 2 doubles sparseness)
	- octaves should be non-zero positive. octaves value of 1 is the same as regular perlin noise
*/
std::vector<std::vector<float> > Perlin::generate_fractal(int octaves, int lacunarity, float persistence) {
	std::vector<std::vector<float> > res;
	float x, y, pt_val;
	float per, lac;

	// spreads out x, y entries within each grid
	float incr = 1.0 / grid_size;

	for (int j = 0; j < grid_size * grid_num; ++j) {
		std::vector<float> row;
		y = j * incr + 0.001;
		for (int i = 0; i < grid_size * grid_num; ++i) {
			x = i * incr + 0.001;
			pt_val = 0;
			per = 1.0;
			lac = 1.0;
			for (int o = 0; o < octaves; ++o) {
				pt_val += per * calc_pt(x * lac, y * lac);
				per *= persistence;
				lac *= lacunarity;
			}
			row.push_back(pt_val);
		}
		res.push_back(row);
	}

	return res;
}



// get_perm(): perm accessor
std::vector<int> Perlin::get_perm() { return perm; }

// get_grid_size(): grid_size accessor 
int Perlin::get_grid_size() { return grid_size; }
// set_grid_size(): grid_size mutator
void Perlin::set_grid_size(const int size) { grid_size = size; }

// get_grid_num(): grid_num accessor
int Perlin::get_grid_num() { return grid_num; }
// set_grid_num(): grid_num mutator
void Perlin::set_grid_num(const int num) { grid_num = num; }

