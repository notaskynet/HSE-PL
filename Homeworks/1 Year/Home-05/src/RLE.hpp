#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <cmath>

class StreamProcessor {
protected:
    std::istream& input_;
    std::ostream& output_;

public:
    StreamProcessor(std::istream& input, std::ostream& output) : input_(input), output_(output) {}
    virtual ~StreamProcessor() = default;
    virtual void Process() = 0;
};

template<size_t N = 8>
class RLE : public StreamProcessor {
public:
    RLE(std::istream& input, std::ostream& output) : StreamProcessor(input, output) {}

    void Process() override {
        char prev_char = '\0';
        int count = 0;
        bool first_char = true;
        while (input_) {
            char cur_char = input_.get();
            if (input_.eof()) {
                if (count > 0) {
                    output_run(prev_char, count);
                }
                break;
            }
            if (first_char) {
                prev_char = cur_char;
                count = 1;
                first_char = false;
            } else if (prev_char == cur_char && count < (1 << N) - 1) {
                count++;
            } else {
                output_run(prev_char, count);
                prev_char = cur_char;
                count = 1;
            }
        }
    }

private:
    void output_run(char ch, int count) {
        if (count == 1) {
			output_ << "11";
            output_.put(ch);
        } else if (count <= (1 << N) - 1) {
            std::string buffer;
			std::string zeroes = "";
			do{
				buffer+=char('0' + count % 2);
				count = count / 2;
			}while (count > 0);
			std::reverse(buffer.begin(), buffer.end());
			for(size_t i = 0; i < (N-buffer.size());i++) {zeroes +="0";}
			output_ << "0" << zeroes << buffer;
            output_.put(ch);
        }
    }
};

template<size_t N = 8>
class RLEDecoder : public StreamProcessor {
public:
    RLEDecoder(std::istream& input, std::ostream& output) : StreamProcessor(input, output) {}

    void Process() override {
        while (input_) {
            char ch = input_.get();
            if (input_.eof()) {
                break;
            }
            if (ch == '1') {
				input_.get();
				char c = input_.get();
				output_ << c;
            } else {
				int count1 = 0;
				
                for(int i = N-1; i >= 0; i--){
					count1 += static_cast<int>(input_.get()-'0')*pow(2, i);
				}
				
				char repeat_char = input_.get();
                for (int i = 0; i < count1; i++) {
                    output_.put(repeat_char);
                }
            }
        }
    }
};
