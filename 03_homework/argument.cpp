#include "argument.h"

#include <iostream>
#include <string>

int argument(const int& argc, char**& argv) {

	const int max_value = 100;

	// argc - it is a count of arguments
	// But there is some detail - OS always pass one system argument - the name of the executable
	// So, is the application was executed without arguments at all, argc will be still == 1

	// To check - does use print some other argument we should check if the argc > 1
	if (argc > 1) {

		std::string arg1_value{ argv[1] };
		if (arg1_value == "-max") {

			// We've detected the '-max' argument. And we extect that after this argument there is a value:
			int parameter_value = 0;
			if (argc > 2) {

				// We need to parse the string to the int value
				parameter_value = std::stoi(argv[2]);

				return parameter_value;
			}
			std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
			return -1;
		}
		std::cout << "Wrong argument '" << arg1_value << "'!" << std::endl;
		return -1;
	}
	return max_value;
}