#include"ThreadPool.h"
#include"Thread.h"
#include<functional>
ThreadPool::ThreadPool():
    m_pool_size(DEFAULT_POOL_SIZE),
    m_task_cond_var(m_task_mutex)
{

}

ThreadPool::ThreadPool(int pool_size):
    m_pool_size(pool_size),
    m_task_cond_var(m_task_mutex)
{

}
ThreadPool::~ThreadPool()
{
    if(m_pool_state!=STOPPED)
    {
        destroy_threadpool();
    }
}

int ThreadPool::initialize_threadpool()
{
    //todo :lazy loading threads instead of creating threads at once
    m_pool_state=STARTED;
    m_ThreadVec.reserve(m_pool_size);
    for(int i=0;i<m_pool_size;i++){
        Thread thread(std::bind(&ThreadPool::execute_thread,this));

        m_ThreadVec[i]=thread;
        m_ThreadVec[i].run();
    }
    std::cout<<m_pool_size<<" in initialize_threadpool() threads created by the thread pool"<<std::endl;
    return 0;
}

int ThreadPool::destroy_threadpool()
{
    m_task_mutex.lock();
    m_pool_state=STOPPED;
    m_task_mutex.unlock();

    std::cout<<"in destroy_threadpool() Brocasting STOP signals to all threads..."<<std::endl;
    m_task_cond_var.wakeAll();

    int ret=-1;
    for(int i=0;i<m_pool_size;i++)
    {

        ret=m_ThreadVec[i].join();
        std::cout<<"in destroy_threadpool() pthread_join() returned "<<ret<<":"<<strerror(errno)<<std::endl;
        m_task_cond_var.wakeAll();//trying waking up a bunch of threads that are still waiting

    }
    std::cout<<m_pool_size<<" in destroy_threadpool() threads exited from the threadpool"<<std::endl;
    return 0;
}
int ThreadPool::add_task(Task *task)
{
    m_task_mutex.lock();
    //todo :put a limit on how many task canbe added at most
    m_tasks.push_back(task);
    m_task_cond_var.wakeOne();//wake up one thread that is waiting

    m_task_mutex.unlock();

    return 0;

}

void ThreadPool::execute_thread(){
    Task* task=NULL;
    std::cout<<"in execute_thread() starting thread "<<pthread_self()<<std::endl;
    while(true){
        //to pick a task
        std::cout<<"in execute_thread() locking: "<<pthread_self()<<std::endl;
        m_task_mutex.lock();
        //we need to put pthread_cond_wait in a loop for two reasons:
        //1 there can be spurious wakeups(due to signal/ENITR)
        //2 when mutex is released for waiting ,another thread can be waken up
        //from a signal/broadcast and that thread can messup the condition.
        //so when the currrnt thread wakes up the condition may no longer be actually true
        while((m_pool_state!=STOPPED)&&(m_tasks.empty())){
            //wait until there is a task in the queue
            //unlock mutex while wait,then lock it back when signaled
            std::cout<<"in execute_thread() unlock and waiting:"<<pthread_self()<<std::endl;
            m_task_cond_var.wait();
            std::cout<<"in execute_thread() signaled and locking"<<std::endl;
        }

        if(m_pool_state==STOPPED){
            std::cout<<"in execute_thread() unlocking and exiting"<<pthread_self()<<std::endl;
            m_task_mutex.unlock();
            pthread_exit(NULL);
        }

        task=m_tasks.front();
        m_tasks.pop_front();
        std::cout<<"in execute_thread() unlocking: "<<pthread_self()<<std::endl;
        m_task_mutex.unlock();

        task->run();
        delete task;
    }
    return ;
}

size_t ThreadPool::dequeSize()
{
    MutexLockGuard lockguard(m_task_mutex);
    return m_tasks.size();
}
