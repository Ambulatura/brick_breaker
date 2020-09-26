#ifndef UTILS_H
#define UTILS_H

#include <random>

unsigned int random_number() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 100.0);

	return static_cast<unsigned int>(dist(mt));
}

#endif // !UTILS_H
