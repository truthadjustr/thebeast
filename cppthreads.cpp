#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

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

void f(void *data)
{
    std::this_thread::sleep_for(std::chrono::seconds(25));

    while (true) {
        std::lock_guard<std::mutex> lk(m);
        pred++;
        cv.notify_one();
    }
}

int main()
{
    std::atomic<double> p;
    std::atomic<Person> p2;
    std::thread t(f,nullptr);

    while (true) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { 
            if (pred > 0) {
                std::cout << "something todo\n";
                return true;
            } else {
                std::cout << "nope\n";
                return false;
            }
        });
        pred = 0;
    }

    t.join();
    return 0;
}
