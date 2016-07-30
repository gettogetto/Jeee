#include"Thread.h"
#include<stdio.h>
ThreadData::ThreadData(const ThreadFunc &func):
    m_func(func)
{

}

void ThreadData::run()
{
    m_func();
}

/*independent function*/
void *startThread(void* arg)
{
    ThreadData* data=static_cast<ThreadData*>(arg);
    data->run();
    delete data;
    return nullptr;
}


Thread::Thread(const ThreadFunc& func):
    m_func(func),m_isRunning(false),m_joined(false),m_tid(0),m_data(nullptr)
{

}
Thread::~Thread()
{
    //if(m_isRunning&&!m_joined){
       // pthread_detach(m_tid);
    //}

   // delete m_data;
    //m_data=nullptr;

}

int Thread::run()
{
    assert(!m_isRunning);
    m_isRunning=true;
    m_data=new ThreadData(m_func);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
    if(pthread_create(&m_tid,&attr,startThread,static_cast<void*>(m_data))==0){
        return 0;
    }else{
        fprintf(stderr,"pthread_create\n");
        m_isRunning=false;
        delete m_data;
        return -1;
    }

}

int Thread::join()
{
    assert(m_isRunning);
    assert(!m_joined);
    m_joined=true;
    return pthread_join(m_tid,NULL);
}

bool Thread::isRunning()
{
    return m_isRunning;
}

pthread_t Thread::getTid()
{
    return m_tid;
}

