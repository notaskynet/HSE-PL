#include <iostream>
#include "map.hpp"

int main() {
    Map<std::string, int> map;

    map["One"]   = 1;
    map["Two"]   = 2;
    map["Three"] = 3;
    map["Four"]  = 4;
    map["Five"]  = 5;
    map["Six"]   = 6;
    map["Seven"] = 7;
    map["Eight"] = 8;
    map["Nine"]  = 9;
    map["Zero"]  = 0;

    for(auto it = map.begin(); it != map.end(); ++it)
        std::cout << it->second << " ";

    std::cout << std::endl;

    std::cout << map["One"] << " "
              << map["Zero"] << " "
              << map["Five"] << " "
              << map["Seven"] << std::endl;
    return 0;
}
