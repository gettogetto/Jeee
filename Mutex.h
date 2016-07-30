#pragma once

#include<pthread.h>

class MutexLock
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void tryLock();
    void unlock();
    pthread_mutex_t* get_mutex_ptr();

    //nocopy
    MutexLock(const MutexLock&)=delete;
    MutexLock(MutexLock&&)=delete;
    MutexLock& operator=(const MutexLock&)=delete;
    MutexLock& operator=(MutexLock&&)=delete;
private:
    pthread_mutex_t m_lock;
    volatile bool is_locked;
    //todo :replace by "m_hoder" to indicate who is owning the lock
};

//a RAII class MutexLockGuard
class MutexLockGuard{
public:
    explicit MutexLockGuard(MutexLock&);//must not use like "MutexLockGuard(mutexlock);" .it is a tempory object.
    ~MutexLockGuard();

    MutexLockGuard(const MutexLockGuard&)=delete;
    MutexLockGuard(MutexLockGuard&&)=delete;
    MutexLockGuard& operator=(const MutexLockGuard&)=delete;
    MutexLockGuard& operator=(MutexLockGuard&&)=delete;
private:
    MutexLock& m_mutexlock;//MutexLOck nocopyable,so use reference
};
