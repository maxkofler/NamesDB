#include "log.h"
#include "debug.h"

#include <map>

static std::map<std::string, bool> function_failures;

void prepare_fun_failure(std::string funName){
	FUN();

	LOGD("Setting up function failure for \"" + funName + "\"");

	function_failures[funName] = true;
}

void teardown_function_failure(std::string funName){
	FUN();

	LOGD("Tearing down function failure for \"" + funName + "\"");

	if (function_failures.count(funName) > 0)
		function_failures[funName] = false;
}

bool function_should_fail(std::string funName){
	FUN();

	LOGFUNCALLS("Checking if \"" + funName + "\" should fail");

	if (function_failures.count(funName) > 0)
		if (function_failures[funName])
			return true;
	
	return false;
}
