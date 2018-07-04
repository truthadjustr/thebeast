#include "stdafx.h"

#include <string>
#include <iostream>
#include <functional>

std::string s = std::to_string(123);

std::function<int(int,int)> gg();

class Myobj {
public:
    Myobj() {
        gg();
        s = "hello " + s;
    }
};

#if 1
auto G = [] {
    std::cout << "nonymous";
};
#endif

int n = 69;
int sum = n + 1;
Myobj o;

std::function<int(int,int)> gg()
{
    static int ss = 0;

    int *m = &n;
    for (int i = 0; i < 3; i++) {
        n += i;
    }

    auto H = [m](int a,int b) mutable -> int {        
        //n = 0;
        *m = a + b;
        return a + b + *m;
    };
    
    if (ss == 0) {
        int ret;
        ret = H(1,2);
    }
    ss++;
    G();

    return H;
}
