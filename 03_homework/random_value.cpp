#include "random_value.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

int random_value(const int max_value) {

	std::srand(unsigned int(std::time(nullptr))); // use current time as seed for random generator

	const int random_value = std::rand() % (max_value + 1);

	return random_value;
}