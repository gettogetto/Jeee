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
//#include"Global.h"
#include"Thread.h"
#define DEFAULT_POOL_SIZE 10

#define STARTED 0
#define STOPPED 1
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(int pool_size);
    ~ThreadPool();

    int destroy();

    void workerThread();
    int addTask(const Task&);
    size_t dequeSize();
private:
    int init();

private:
    int m_pool_size;
    MutexLock m_task_mutex;
    WaitCondition m_task_cond_var;

    std::vector<Thread> m_ThreadVec;
    std::deque<Task> m_tasks;
    volatile int m_pool_state;


};
