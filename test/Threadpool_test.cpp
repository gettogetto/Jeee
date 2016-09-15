

#include"ThreadPool.h"

#include<iostream>

using namespace std;
const int MAX_TASKS=50;
void hello(void* arg){
    int i=0;
    while(i++<=100000);
    cout<<"hello "<<rand()%100<<endl;

}

int main(int argc, char *argv[])
{
    ThreadPool tp(2);

    for(int i=0;i<MAX_TASKS;i++){

        Task t(std::bind(&hello,nullptr));
        cout<<"in main() adding to pool,task "<<i<<endl;
        tp.addTask(t);
    }
    sleep(2);
    //tp.destroy();
    return 0;
}



