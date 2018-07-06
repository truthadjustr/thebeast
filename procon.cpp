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
        cv.wait(lck, [this] {return !q.empty(); });
        if (!q.empty()) {
            elem = q.front();
            q.pop();
        }
        return elem;
    }
};

//Queue<std::string> ourQueue;
Queue<int> ourQueue;

template <typename T>
int threadfunc(int a,int b)
{
    //std::string item;
    T item;
    char buf[100];

    while (1)
    {
        item = ourQueue.next();
        std::cout << "[" << item << "]" << std::endl;
    }

    return 0;
}

int main()
{
    //std::string s = "apple";
    //std::cout << s.c_str();
    int i = 0;

#if 0
    HANDLE  hThreadArray[MAX_THREADS];
    DWORD dwThreadId;

    hThreadArray[i] = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        NULL,          // argument to thread function 
        0,             // use default creation flags 
        &dwThreadId);   // returns the thread identifier 
#endif

    //std::thread t(threadfunc<std::string>,2,4);
    std::thread t(threadfunc<int>,2,4);

    char ch[100];
    std::string input;
    int item;
    //std::string item;

    while (true) {
        std::getline(std::cin, input);
        item = atoi(input.c_str());
        //item = input;
        ourQueue.push(item);
    }

    t.join();

    return 0;
}
