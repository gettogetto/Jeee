#pragma once

#include<pthread.h>
#include<functional>

/*
class Task
{
public:
    Task(void(*fn_ptr)(void*),void* arg);
    ~Task();

    //void operator()();
    void run();
private:
    void(*m_fn_ptr)(void*);
    void* m_arg;
};
*/

class Task
{
public:
    typedef std::function<void()> FuncType;
    explicit Task(const FuncType&);
    ~Task();

    void run();
private:
    FuncType m_func;
};
