#include"Exception.h"
/*
Exception::Exception(const char* what)
    :m_message(what)
{

}*/

Exception::Exception(const std::string &what)
    :m_message(what)
{
    fillStackTrace();
}



Exception::~Exception()
{

}

void Exception::fillStackTrace()
{
    const int n=20;
    void *array[n];
    size_t size = backtrace(array,n);

    char** strings = backtrace_symbols(array,size);

    if(strings)
    {
        for(int i=0;i<size;i++){
            m_stack.append(strings[i]);
            m_stack.push_back('\n');
        }
    }

    free(strings);//after backtrace_symbols() must free
}


const char* Exception::what() const throw()
{
    return m_message.c_str();
}

const char* Exception::stackTrace() const throw()
{
    return m_stack.c_str();
}

