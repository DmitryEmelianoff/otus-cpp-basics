#include "check_value.h"

#include "random_value.h"

#include <iostream>

int check_value(const int max_value) {

	int number_of_attempts = 0;
	const int target_value = random_value(max_value);
	int current_value = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {

		std::cin >> current_value;

		++number_of_attempts;

		if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << number_of_attempts << std::endl << std::endl;
			break;
		}

	} while(true);

	return number_of_attempts;
}