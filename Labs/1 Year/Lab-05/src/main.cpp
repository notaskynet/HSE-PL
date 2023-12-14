#include "bigint.h"
#include <iostream>
#include <string>

#define OPTION_SIZE 6

int main() {
    int choice; bool flag = true;
    std::string options[] = {
                        "1. +",
                        "2. -",
                        "3. *",
                        "4. /",
                        "5. / with %",
                        "6. Exit"
    };

    while(flag) {
        for(size_t i = 0; i < OPTION_SIZE; ++i) {
            std::cout << options[i] << std::endl;
        }
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
                    flag = false;
                    break;
                }
            }
        }
    }
    return 0;
}