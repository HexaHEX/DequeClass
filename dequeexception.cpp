#include "dequeexception.h"

DequeException::DequeException(unsigned int code, std::string msg):
_code_error(code),
_msg_error(msg)
{

}

DequeException::~DequeException(){

}

unsigned int DequeException::GetCodeError(){
    return this->_code_error;
}

std::string DequeException::GetMessageError(){
    return this->_msg_error;
}
