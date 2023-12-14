#include "bigint.h"
#include <iostream>

#define OPTION_SIZE 9


int main() {
    int choice;
    bool flag = true;

    while(flag) {
        std::cout   << "1. +" << std::endl
                    << "2. -" << std::endl
                    << "3. *" << std::endl
                    << "4. /"<< std::endl
                    << "5. / with %" << std::endl
                    << "6. GCD" << std::endl
                    << "7. Eratosthenes" << std::endl
                    << "8. sqrt" << std::endl
                    << "9. Exit" << std::endl;

        std::cin >> choice;

        if(choice > OPTION_SIZE || choice < 0) {
            std::cout << "Please try again!" << std::endl;
        }
        else {
            switch(choice) {
                case 1: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);

                    bigint::add(a, b).print();

                    break;
                }
                case 2: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);

                    bigint::sub(a, b).print();

                    break;
                }
                case 3: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);

                    bigint::mul(a, b).print();

                    break;
                }
                case 4: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);

                    bigint::div(a, b).print();

                    break;
                }
                case 5: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);
                    bigint c;

                    bigint::div(a, b, c).print();
                    c.print();

                    break;
                }
                case 6: {
                    long num1, num2;
                    std::cout << "Enter 2 nums!" << std::endl;
                    std::cin >> num1;
                    std::cin >> num2;

                    bigint a(num1);
                    bigint b(num2);

                    bigint::gcd(a, b).print();

                    break;
                }
                case 7: {
                    size_t  size, counter;

                    std::cout << "Enter size of a sieve!" << std::endl;
                    std::cin >> size;

                    bigint *sieve = new bigint[size + 1];
                    counter = bigint::Eratosthenes(sieve, size);
                    std::cout << counter << std::endl;

                    delete[] sieve;
                    break;
                }
                case 8: {
                    unsigned long value;
                    std::cout << "Enter a value!" << std::endl;
                    std::cin >> value;

                    if(value < 0) {
                        std::cerr << "Value must be greater than 0!" << std::endl;
                    }
                    bigint a(value);
                    bigint::sqrt(a).print();
                }
                case 9: {
                    flag = false;
                    break;
                }
            }
        }
    }
	return 0;
}
