// procon.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include <Windows.h>

#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue
{
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<T> q;
public:
    // pop an element and return a copy. Block if queue empty.
    //T pop();
    //  push an element to the back of the queue.
    void push(const T& item) {
        std::unique_lock<std::mutex> lck(mtx);
        //if (item != nullptr) {
            q.push(item);
            cv.notify_one();
        //}
    }

    T next() {
        T elem;// = nullptr;
        std::unique_lock<std::mutex> lck(mtx);
        //cv.wait(lck, [] {return true; });
        cv.wait(lck, [this] {return !q.empty(); });
        if (!q.empty()) {
            elem = q.front();
            q.pop();
        }
        return elem;
    }
};

Queue<std::string> ourQueue;

int threadfunc(int a,int b)
//int threadfunc()
{
    std::string item;
    char buf[100];

    while (1)
    {
        item = ourQueue.next();
        //std::string iTemp = ourQueue.pop();
        //std::cout << iTemp.c_str() << std::endl;
        //ourQueue.pop();
        snprintf(buf, sizeof(buf), "[%s]\n", item.c_str());
        //snprintf(buf, sizeof(buf), "[%s]\n", "this is a test");
        std::cout << buf;
    }

    return 0;
}

int main()
{
    std::string s0;
    //std::string s = "apple";
    //std::cout << s.c_str();
    int i = 0;
    //HANDLE  hThreadArray[MAX_THREADS];
    //DWORD dwThreadId;

#if 0
    hThreadArray[i] = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        NULL,          // argument to thread function 
        0,             // use default creation flags 
        &dwThreadId);   // returns the thread identifier 
#endif

    std::thread t(threadfunc,3,4);

    char ch[100];
    std::string input;

    while (true) {
        //std::cin >> ch;        
        std::getline(std::cin, input);
        //std::cout << "[" << ch << "]\n";
        //ourQueue.push(std::string(ch));
        ourQueue.push(input);
    }

    t.join();

    return 0;
}
