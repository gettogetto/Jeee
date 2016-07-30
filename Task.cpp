#include"Task.h"


Task::Task(const FuncType& func):m_func(func){

}
Task::~Task()
{

}
void Task::run()
{
    m_func();
}

