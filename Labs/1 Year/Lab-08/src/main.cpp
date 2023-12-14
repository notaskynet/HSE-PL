#include <iostream>
#include "BigFraction.h"


int main() {
	BigFraction f1, f2;

	while(true) {
		std::cout << "Enter first fraction" << std::endl;
		std::cin >> f1;
		std::cout << "Enter second fraction" << std::endl;
		std::cin >> f2;
		std::cout << f1 + f2 << std::endl;
		std::cout << f1 - f2 << std::endl;
		std::cout << f1 * f2 << std::endl;
		std::cout << f1 / f2 << std::endl;
		std::cout << static_cast<double>(f1) << std::endl;
	}
	return 0;
}