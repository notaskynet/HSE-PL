#include "fraction.hpp"
#include <iostream>


int main() {
    Fraction<int> frac1, frac2;
    int num;

    std::cout << "Enter 2 fractions(Format: (sign)num/den" << std::endl;
    std::cin  >> frac1;
    std::cin  >> frac2;

    std::cout << "Enter inetger value" << std::endl;
    std::cin  >> num;

    std::cout << "Results:" << std::endl;
    std::cout << "f1 + f2 = " << frac1 + frac2 << std::endl;
    std::cout << "f1 - f2 = " << frac1 - frac2 << std::endl;
    std::cout << "f1 * f2 = " << frac1 * frac2 << std::endl;
    std::cout << "f1 / f2 = " << frac1 / frac2 << std::endl;

    std::cout << "f1 + num = " << frac1 + num << std::endl;
    std::cout << "f1 - num = " << frac1 - num << std::endl;
    std::cout << "f1 * num = " << frac1 * num << std::endl;
    std::cout << "f1 / num = " << frac1 / num << std::endl;
    
    return 0;
}