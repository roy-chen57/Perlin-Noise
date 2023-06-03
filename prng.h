#pragma once

class Prng {
protected:
	int seed = 0b11111111;
public:
	Prng();
	Prng(int seed);
	int get_seed() const;
	int pow(const int base, const int exp) const;
	virtual int generate();
};
