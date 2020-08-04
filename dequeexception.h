#ifndef DEQUEEXCEPTION_H
#define DEQUEEXCEPTION_H

#include <iostream>

class DequeException : public std::exception{
public:
    DequeException(unsigned int code = 0, std::string msg = "");
    ~DequeException();

    unsigned int GetCodeError();
    std::string  GetMessageError();

private:
    unsigned int _code_error;
    std::string  _msg_error;
};

#endif // DEQUEEXCEPTION_H
