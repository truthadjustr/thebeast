#include <iostream>

void f(int n)
{
    std::cout << "int\n";
}

void f(char *s)
{
    std::cout << "char*\n";
} 

int main()
{
    f('\0');
    f(nullptr);
}
