#include <iostream>

void f(int n)
{
    std::cout << "int\n";
}

void f(char *s)
{
    std::cout << "char*\n";
} 

int main(int argc,char *argv[])
{
    f('\0');
    f(nullptr);
    const int x = argc;
    //std::cin >> x;
    std::cout << x;

    //constexpr int q = x;
}
