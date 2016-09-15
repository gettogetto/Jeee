#ifndef COUNTDOWNLATCH_H
#define COUNTDOWNLATCH_H

#include"Mutex.h"
#include"WaitCondition.h"

class CountDownLatch{
public:
    CountDownLatch(int count);
    ~CountDownLatch();

    void await();
    void countDown();
    int count();
    CountDownLatch(const CountDownLatch&) = delete;
    CountDownLatch& operator = (const CountDownLatch&) =delete;
private:
    MutexLock m_mutex;
    WaitCondition m_cond;
    int m_count;
};

#endif
