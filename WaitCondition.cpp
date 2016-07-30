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
    CHECK(pthread_cond_wait(&m_cond_var,m_mutex_lock.get_mutex_ptr()));
}

void WaitCondition::wakeOne()
{
    CHECK(pthread_cond_signal(&m_cond_var));
}

void WaitCondition::wakeAll()
{
    CHECK(pthread_cond_broadcast(&m_cond_var));
}


