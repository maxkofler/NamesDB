#include "log.h"
#include "debug.h"

DebugException::DebugException(std::string funName){
	FUN();

	this->_funName = funName;
}

std::string DebugException::what(){
	FUN();

	return this->_funName;
}
