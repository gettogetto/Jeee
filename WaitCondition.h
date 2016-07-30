#pragma once

#include<pthread.h>
#include<assert.h>
#include"Mutex.h"

#define CHECK(ret) ({__typeof__(ret) err=(ret);\
                    assert(err==0);})

class WaitCondition
{
public:
    explicit WaitCondition(MutexLock&);
    ~WaitCondition();

    void wait();

    void wakeOne();
    void wakeAll();
//nocopy
    WaitCondition(const WaitCondition&)=delete;
    WaitCondition(WaitCondition&&)=delete;
    WaitCondition& operator=(const WaitCondition&)=delete;
    WaitCondition& operator=(WaitCondition&&)=delete;
private:
    pthread_cond_t m_cond_var;
    MutexLock& m_mutex_lock;
};
