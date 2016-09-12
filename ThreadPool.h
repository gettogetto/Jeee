#include<pthread.h>
#include<unistd.h>
#include<deque>
#include<vector>
#include<iostream>
#include<errno.h>
#include<string.h>
#include"Mutex.h"
#include"Task.h"
#include"WaitCondition.h"
#include"Global.h"
#include"Thread.h"
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(int pool_size);
    ~ThreadPool();
    int initialize_threadpool();
    int destroy_threadpool();

    void execute_thread();
    int add_task(Task*);
    size_t dequeSize();
private:
    int m_pool_size;
    MutexLock m_task_mutex;
    WaitCondition m_task_cond_var;

    std::vector<Thread> m_ThreadVec;
    std::deque<Task*> m_tasks;
    volatile int m_pool_state;


};
