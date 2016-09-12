#ifndef BOARDEDBLOCKINGQUEUE_H
#define BOARDEDBLOCKINGQUEUE_H

#include"Mutex.h"
#include"WaitCondition.h"
#include<vector>


#define DEFAULTSIZE 20

template<class T>
class BoardedBlockingQueue
{
public:
    BoardedBlockingQueue(int size = DEFAULTSIZE)
        :m_mutex(),m_notEmpty(m_mutex),
          m_notFull(m_mutex),head(0),tail(0),
          m_size(size),
          queue(std::vector<T> (m_size))
    {

    }

    ~BoardedBlockingQueue()
    {

    }

    void push(const T& item)
    {
        MutexLockGuard lockguard(m_mutex);
        while((head+1)%m_size == tail)
        {
            m_notFull.wait();
        }
        queue[head]=item;
        head=(head+1)%m_size;
        m_notEmpty.wakeOne();
    }

    T take()
    {
        MutexLockGuard lockguard(m_mutex);
        while(head==tail)
        {
            m_notEmpty.wait();
        }
        T res(queue[tail]);
        tail = (tail+1)%m_size;
        m_notFull.wakeOne();

        return res;
    }

private:
    MutexLock m_mutex;

    WaitCondition m_notFull;
    WaitCondition m_notEmpty;

    int head;//first index can push
    int tail;//first index can take

    size_t m_size;
    std::vector<T> queue;
};


#endif
