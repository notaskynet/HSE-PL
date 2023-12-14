#include <iostream>
#include <string>

#include "fraction.h"

#define OPTION_SIZE 9

int main() {
    int choice;
    bool flag = true;
    std::string options[] = {
                        "1. fraction + fraction",
                        "2. fraction - fraction",
                        "3. fraction * fraction",
                        "4. fraction : fraction",
                        "5. fraction + int",
                        "6. fraction - int",
                        "7. fraction * int",
                        "8. fraction / int",
                        "9. Exit"
    };

    std::cout << "Hello! I`m a stupid integer calculator!" << std::endl;
    while(flag) {
        for(size_t i = 0; i < OPTION_SIZE; ++i) {
            std::cout << options[i] << std::endl;
        }

        std::cin >> choice;
        if(choice > OPTION_SIZE || choice < 0) {
            std::cout << "Please try again!" << std::endl;
            std::cout << std::endl;
        }
        else {
            switch(choice) {
                case 1: {
                    fraction a, b;

                    std::cin >> a;
                    std::cin >> b;
                    std::cout << (a + b) << std::endl;

                    break;

                }
                case 2: {
                    fraction a, b;

                    std::cin >> a;
                    std::cin >> b;
                    std::cout << (a - b) << std::endl;

                    break;
                }
                case 3: {
                    fraction a, b;

                    std::cin >> a;
                    std::cin >> b;
                    std::cout << (a * b) << std::endl;

                    break;
                }
                case 4: {
                    fraction a, b;

                    std::cin >> a;
                    std::cin >> b;
                    std::cout << (a / b) << std::endl;

                    break;
                }
                case 5: {
                    fraction a;
                    int c;

                    std::cin >> a;
                    std::cin >> c;
                    std::cout << (a + c) << std::endl;

                    break;
                }
                case 6: {
                    fraction a;
                    int c;

                    std::cin >> a;
                    std::cin >> c;
                    std::cout << (a - c) << std::endl;

                    break;
                }
                case 7: {
                    fraction a;
                    int c;

                    std::cin >> a;
                    std::cin >> c;
                    std::cout << (a * c) << std::endl;

                    break;
                }
                case 8: {
                    fraction a;
                    int c;

                    std::cin >> a;
                    std::cin >> c;
                    std::cout << (a / c) << std::endl;

                    break;
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