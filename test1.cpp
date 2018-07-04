#include <iostream>
#include <chrono>
#include <thread>

//#include <string>

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
        std:: cout << m_str + std::to_string(n) << std::endl;
    }
    /*
    void operator=(std::string s) {
    }
    void operator=(const char *s) {
    }
    */
};

template<typename A,typename B>
void f(A a,B b)
{
    //std::cout << a + b;
    a + b;
}

void f1()
{
    f<int,int>(4,8);
    f<std::string,std::string>("apple","banana");
    f<Mystring,int>("apple",4);
}

void test_chrono()
{
    auto t0 = std::chrono::system_clock::now();
    //std::cout << t0;// << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto t1 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = t1 - t0;
    std::cout << elapsed_seconds.count() << std::endl;

    std::time_t t_0 = std::chrono::system_clock::to_time_t(t0);
    std::time_t t_1 = std::chrono::system_clock::to_time_t(t1);
    std::cout << t_0 << std::endl << t_1;

    std::cout << std::endl << std::ctime(&t_0);
}

extern int n;
extern std::string s;

int main()
{
    f1();
    std::cout << "\n----------------\n";
    std::cout << n << s;
}
