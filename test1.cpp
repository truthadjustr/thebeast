#include <iostream>
#include <chrono>
#include <thread>

int main()
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
