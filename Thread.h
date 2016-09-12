#pragma once
#include<pthread.h>
#include<functional>
#include<assert.h>
class ThreadData{
public:
    typedef std::function<void()> ThreadFunc;
    explicit ThreadData(const ThreadFunc &func);
    void run();
private:
    ThreadFunc m_func;
};





class Thread{
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc& func);
    ~Thread();

    //Thread(const Thread&)=delete;
    //Thread(Thread&&)=delete;
    //Thread& operator=(const Thread&)=delete;
    //Thread& operator=(Thread&&)=delete;

    int run();
    int join();
    bool isRunning();
    pthread_t getTid();


private:

    ThreadFunc m_func;
    bool m_isRunning;
    bool m_joined;
    pthread_t m_tid;
    ThreadData* m_data;
};
