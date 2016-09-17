#ifndef EXCEPTION_H
#define EXCEPTION_H
#include<string>
//#include<exception>
#include<execinfo.h>
class Exception{
public:
    //explicit Exception(const char* what);
    explicit Exception(const std::string& what);

    virtual ~Exception() throw();
    const char* what() const throw();


    const char* stackTrace() const throw();
private:

    void fillStackTrace();
    std::string m_message;
    std::string m_stack;
};

#endif
