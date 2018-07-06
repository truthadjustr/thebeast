#include <iostream>
#include <functional>

class Obj
{
private:
    int m_counter = 0;
public:
    ~Obj() { std::cout << "destx\n"; }
    Obj() { std:: cout << &m_counter << std::endl; }
    void g()
    {
        std::cout << m_counter;
    }

    std::function<int()> f()
    {
        return [this]() -> int {
            std::cout << m_counter << " " << &m_counter << std::endl;
            m_counter++;
            return m_counter;
        };
    }
};

int main()
{
    std::function<int()> ff;
    {
        Obj obj;
        ff = obj.f();
    }
    int val = ff();
    std::cout << val << std::endl;
}
