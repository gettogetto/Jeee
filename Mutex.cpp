#include"Mutex.h"
#include<assert.h>

#define CHECK(ret) ({__typeof__(ret) err=(ret);\
                    assert(err==0);})

/*************************MutexLock***************************/
MutexLock::MutexLock()
    :is_locked(false)
{
    CHECK(pthread_mutex_init(&m_lock,NULL));

}

MutexLock::~MutexLock()
{
    //while(is_locked);
    assert(is_locked==false);
    //unlock();
    pthread_mutex_destroy(&m_lock);//why CHECK the ret here will assert error?
}

void MutexLock::lock()
{

    CHECK(pthread_mutex_lock(&m_lock));
    is_locked=true;
}
void MutexLock::tryLock()
{
    CHECK(pthread_mutex_trylock(&m_lock));
    is_locked=true;
}

void MutexLock::unlock()
{
    is_locked=false;//do it before unlocking to avoid race condition
    CHECK(pthread_mutex_unlock(&m_lock));
}

pthread_mutex_t* MutexLock::getMutex()
{
    return &m_lock;
}



/*************************MutexLockGuard***************************/
MutexLockGuard::MutexLockGuard(MutexLock& mutexlock)
    :m_mutexlock(mutexlock)
{
    m_mutexlock.lock();
}

MutexLockGuard::~MutexLockGuard(){
    m_mutexlock.unlock();
}



