#include "log.h"
#include "debug.h"

void prepare_fun_failure(std::string funName);
void teardown_function_failure(std::string funName);

Fun_Fail_Guard::Fun_Fail_Guard(std::string funName){
	FUN();

	this->_funName = funName;
	prepare_fun_failure(this->_funName);
}

Fun_Fail_Guard::~Fun_Fail_Guard(){
	FUN();

	teardown_function_failure(this->_funName);
}
