#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

#include <unistd.h>

template <typename T>
class Queue
{
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<T> q;
public:
    void push(const T& item) 
    {
        std::unique_lock<std::mutex> lck(mtx);
        q.push(item);
        cv.notify_one();
    }

    T next() 
    {
        T elem;
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [this] {return !q.empty(); });
        if (!q.empty()) {
            elem = q.front();
            q.pop();
        }
        return elem;
    }

};

class Controller
{
    Queue<std::string> m_queue;
public:
    std::function<void(std::string)> doit()
    {
        return [this](std::string s) {
            std::cout << "pushing " << s << std::endl;
            m_queue.push(s);
        };
    }

    void print()
    {
        while (true) {
            std::string elem = m_queue.next();
            std::cout << elem << std::endl;
            sleep(1);
        }
    }
};

void threadfunc(std::function<void(std::string)> f,int tid)
//void threadfunc(int i)
{
    //std::cout << i;
    for (int i = 0;i < 5; i++) {
        std::string input = "tid-" + std::to_string(tid) + ":" + std::to_string(i);
        f(input);
        sleep(1);
    }
}

int main()
{
    Controller c;
    
    std::vector< std::function<void(std::string)> > f;
    std::thread* t[5];

    for (int i = 0;i < 5; i++) {
        //f.push_back(c.doit());
        //std::thread t[i](threadfunc,c.doit());
        t[i] = new std::thread(threadfunc,c.doit(),i);
    }

    //std::thread T;
    //T(threadfunc,[](std::string){});

    /*
    for (int i = 0;i < 5; i++) {
        f[i]("counter " + std::to_string(i));
    }
    */
    
    c.print();
}
