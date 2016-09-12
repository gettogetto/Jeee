#include"Thread.h"
#include"BlockingQueue.h"
#include<iostream>
#include<cstdio>
using namespace std;
BlockingQueue<int> queue;

void producer(void)
{
    printf("producer\n");

    int i;
    for(i=0;i<10000;i++){
        queue.push(i);
        printf("push %d\n",i);
    }
}

void consumer(void)
{
    printf("consumer\n");

    int i;
    for(;;){
        int take=queue.take();
        printf("take %d\n",take);
    }

}

int main(){

    Thread::ThreadFunc pfunc(std::bind(&producer));
    Thread::ThreadFunc cfunc(std::bind(&consumer));

    Thread producerthread(pfunc);
    Thread consumerthread(cfunc);

    consumerthread.run();
    producerthread.run();



    producerthread.join();
    consumerthread.join();
    std::cout<<"quit"<<std::endl;
    return 0;
}
