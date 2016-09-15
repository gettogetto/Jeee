#include"CountDownLatch.h"
#include"Thread.h"
#include<iostream>
CountDownLatch latch(10);
void func1()
{
    latch.await();
    std::cout<<"func1 done"<<std::endl;
}

void func2()
{
    for(int i=0;i<5;i++){
        latch.countDown();
        std::cout<<"count down"<<std::endl;
    }
    std::cout<<"func2 done"<<std::endl;
}

int main(){
    Thread thread1(std::bind(func1));
    Thread thread2(std::bind(func2));

    thread1.run();
    thread2.run();

    thread1.join();
    thread2.join();
}
