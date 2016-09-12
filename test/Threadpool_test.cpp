

#include"ThreadPool.h"

#include<iostream>

using namespace std;
const int MAX_TASKS=50;
void hello(void* arg){
    int* x=(int*)arg;
    int i=0;
    while(i++<=100000);
    cout<<"calculate finished "<<*x<<std::endl;
}

int main(int argc, char *argv[])
{
    ThreadPool tp(2);
    int ret=tp.initialize_threadpool();
    if(ret==-1){
        cerr<<"in main() failed to initialize threadpool\n";
        return 0;
    }
    for(int i=0;i<MAX_TASKS;i++){
        int* x=new int();
        *x=i+1;

        Task *t=new Task(std::bind(&hello,static_cast<void*>(x)));
        cout<<"in main() adding to pool,task "<<i+1<<endl;
        tp.add_task(t);
    }
    sleep(2);
    tp.destroy_threadpool();
    cout<<"in main() all finished\n";


    return 0;
}



