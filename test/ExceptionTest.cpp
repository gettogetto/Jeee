#include"Exception.h"
#include<iostream>
using namespace std;

int main()
{
    Exception e("123");

    std::cout<<e.stackTrace();

    return 0;
}
