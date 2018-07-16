#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <future>

struct Contact {
    char mobile[30];
    int n;
};

struct Person {
    int counter;
    int m_age;
    char name[20];
    Contact ck;
};

int pred = 0;
std::mutex m;
std::condition_variable cv;
std::atomic<bool> flag = true;

void f(void *data)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    int counter = 0;

    while (flag) {
        std::lock_guard<std::mutex> lk(m);
        //std::unique_lock<std::mutex> lk(m);
        pred++;
        std::cout << pred << ","; 
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_one();
        counter++;
        //if (counter == 1000) break;
    }
    std::cout << "Bye\n";
}

std::function<void()> f()
{
    return []{
        for (int i = 0;i < 5; i++) {
            std::cout << "i is " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };
}

int fn()
{
    for (int i = 0;i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "*" << std::flush;
    }
    return 42;
}

int main()
{
    std::future<int> the_answer = std::async(fn);
    for (int i = 0;i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "." << std::flush;
    }
    std::cout << the_answer.get() << std::endl;
#if 0
    std::cout << std::thread::hardware_concurrency();
    std::thread t{f()};
    // std::thread t(f()); // also works

    //t.join();
    t.detach();

    std::this_thread::sleep_for(std::chrono::seconds(10));
#endif

#if 0
    std::atomic<double> p;
    std::atomic<Person> p2;
    int counter = 0;
    std::thread t(f,nullptr);

    std::thread([](void *data) mutable -> int {
        for (int i = 0;i < 10; i++) {
            std::cout << "i = " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return 0;
    },nullptr).join();

    while (true) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { 
            if (pred > 0) {
                std::cout << "+\n";
                pred = 0;
                return true;
            } else {
                std::cout << "-\n";
                return false;
            }
        });
        //pred = 0;
        if (counter == 5) break;
        counter++;
    }
    flag = false;
    t.join();
    return 0;
#endif
}
