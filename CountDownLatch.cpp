#include"CountDownLatch.h"

CountDownLatch::CountDownLatch(int count)
    :m_mutex(),m_cond(m_mutex),m_count(count)
{

}

CountDownLatch::~CountDownLatch()
{

}

void CountDownLatch::await()
{
    MutexLockGuard guard(m_mutex);
    while(m_count>0)
    {
        m_cond.wait();
    }
}

void CountDownLatch::countDown()
{
    MutexLockGuard guard(m_mutex);
    m_count--;
    if(m_count==0){
        m_cond.wakeAll();
    }
}

int CountDownLatch::count()
{
    MutexLockGuard guard(m_mutex);
    return m_count;
}


