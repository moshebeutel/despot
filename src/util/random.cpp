#include "../../include/despot/util/random.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <random>

using namespace std;

namespace despot {

Random Random::RANDOM((unsigned) 0);

Random::Random(double seed) :
 seed_((unsigned) (RAND_MAX * seed)) {
	std::srand(seed);
}
Random::Random(unsigned seed) :
	seed_(seed) {
}

unsigned Random::seed() {
	return seed_;
}

unsigned Random::NextUnsigned() {
//###	return rand_r(&seed_);
	return  std::rand();
}

int Random::NextInt(int n) {
	// return (int) (n * ((double) rand_r(&seed_) / RAND_MAX));
//###	return rand_r(&seed_) % n;
	return  std::rand() % n;
}

int Random::NextInt(int min, int max) {
	//###	return rand_r(&seed_) % (max - min) + min;
	return std::rand() % (max - min) + min;
}

double Random::NextDouble(double min, double max) {
//###	return (double) rand_r(&seed_) / RAND_MAX * (max - min) + min;
	return static_cast<double>(std::rand()) / RAND_MAX * (max - min) + min;
}

double Random::NextDouble() {
//###	return (double) rand_(&seed_) / RAND_MAX;
	return static_cast<double>(std::rand()) / RAND_MAX;
}

double Random::NextGaussian() {
	double u = NextDouble(), v = NextDouble();
	return sqrt(-2 * log(u)) * cos(2 * std::_Pi * v);
}

int Random::NextCategory(const vector<double>& category_probs) {
	return GetCategory(category_probs, NextDouble());
}

int Random::GetCategory(const vector<double>& category_probs, double rand_num) {
	int c = 0;
	double sum = category_probs[0];
	while (sum < rand_num) {
		c++;
		sum += category_probs[c];
	}
	return c;
}

} // namespace despot
