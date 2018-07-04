#include <iostream>

int n = 123;
std::string s = "value = " + std::to_string(n);

class test2 {
public:
    test2() {
        std::cout << __FILE__ << std::endl;
    }
};

test2 test2_instance;
