 #include <iostream>
 #include "stack.hpp"

int main() {
    Stack<int> nums;

    for(size_t i = 0; i < 130; ++i) {
        nums.push(i + 1);
    }
    
    for(Stack<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << "\n";
    }
    
    return 0;
}