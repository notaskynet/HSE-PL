#include <gtest/gtest.h>
#include <sstream>
#include "RLE.hpp"


TEST(RLETest, EncodeTest) {
    std::stringstream input("ABBBCCCCCDDDDEEEE");
    std::stringstream output;
    
    RLE<8> rle_encoder(input, output);
    rle_encoder.Process();

    EXPECT_EQ(output.str(), "11A000000011B000000101C000000100D000000100E");
    
}
TEST(RLETest, DecodeTest) {
    std::stringstream input("11A000000011B000000101C000000100D000000100E");
    std::stringstream output;
    
    RLEDecoder<8> rle_decoder(input, output);
    rle_decoder.Process();

    EXPECT_EQ(output.str(), "ABBBCCCCCDDDDEEEE");
    
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
