#include <iostream>

int n2 = 123;
std::string s2 = "value = " + std::to_string(n2);

class test3 {
public:
    test3() {
        std::cout << __FILE__ << std::endl;
    }
};

test3 test3_instance;
