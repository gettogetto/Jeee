#include"WaitCondition.h"

WaitCondition::WaitCondition(MutexLock& mutexlock):
    m_mutex_lock(mutexlock)
{
    CHECK(pthread_cond_init(&m_cond_var,NULL));
}

WaitCondition::~WaitCondition()
{
    CHECK(pthread_cond_destroy(&m_cond_var));
}

void WaitCondition::wait()
{
    CHECK(pthread_cond_wait(&m_cond_var,m_mutex_lock.getMutex()));
}

bool WaitCondition::waitTime(long seconds, long nanoseconds)
{

    timespec now;
    clock_gettime(CLOCK_REALTIME,&now);//from 1970.1.1 0:0:0
    const timespec timeout{now.tv_sec+static_cast<time_t>(seconds),now.tv_nsec+nanoseconds};
    return ETIMEDOUT==pthread_cond_timedwait(&m_cond_var,m_mutex_lock.getMutex(),&timeout);
}

void WaitCondition::wakeOne()
{
    CHECK(pthread_cond_signal(&m_cond_var));
}

void WaitCondition::wakeAll()
{
    CHECK(pthread_cond_broadcast(&m_cond_var));
}


