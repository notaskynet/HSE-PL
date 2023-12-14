#include <string>
#include <sstream>
#include <iostream>
#include "RLE.hpp"

int main() {
    std::stringstream input("ABBBCCCCCDDDDEEEE");
    
    RLE<8> rle_encoder(input, std::cout);
    rle_encoder.Process();
    std::cout << std::endl;
    std::stringstream input2("11A000000010B000000101C000000100D000000100E");
    
    RLEDecoder<8> rle_decoder(input2, std::cout);
    rle_decoder.Process();

    return 0;
}
