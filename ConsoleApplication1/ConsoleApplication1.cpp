// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <functional>
#include <Windows.h>

#include "Header.h"

class Mystring {
private:
    std::string m_str;
public:
    Mystring(const char *s) {
        std::cout << "conx";
        m_str = std::string(s);
    }
    Mystring(std::string s) {
        std::cout << "conx2";
    }

    void operator+(int n) {
        std::cout << "op+";
        std::cout << m_str + std::to_string(n) << std::endl;
        
    }
    /*
    void operator=(std::string s) {
    }
    void operator=(const char *s) {
    }
    */
};

extern std::string s;
extern int n;

auto F = [] {
    for (int i = 0; i < 3; i++) {
        std::cout << "anonymous";
    }
};

//extern std::function<void(void)> G;
std::function<int(int,int)> gg();

std::function<void(void)> testing_closure(int a,int b)
{
    static int p = 0;
    int c = p;
    p++;
    return [c] {
        std::cout << "c = " << c << std::endl;
        // c = 5; // cannot modify unless declared mutable
    };
}

int main()
{
    int sum = addnum(2, 5);

    auto f1 = testing_closure(1,2);
    auto f2 = testing_closure(3,4);
    Sleep(20000);
    f1();
    f2();

    std::cout << "n = " << n << std::endl;
    //G();
    auto gfunc = gg();
    int retval = gfunc(3,4);
    std::cout << "n = " << n << std::endl;

    F();
    std::cout << s;
    return 0;
}

