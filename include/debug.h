#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

class DebugException{
public:
	DebugException(std::string funName);
	std::string			what();
private:
	std::string			_funName;
};

/**
 * @brief	Is a context guard, as long as this is on the stack, the specified function will fail
 */
class Fun_Fail_Guard{
public:
	Fun_Fail_Guard(std::string funName);
	~Fun_Fail_Guard();
private:
	std::string			_funName;
};

#ifdef DEBUG
	bool function_should_fail(std::string funName);
	void prepare_fun_failure(std::string funName);
	void teardown_function_failure(std::string funName);

	#define DEBUG_FAIL_FUN(function_full_name) Fun_Fail_Guard functionFailGuard(function_full_name)

	#define DEBUG_PREPARE_FAIL(function_full_name) prepare_fun_failure(function_full_name)
	#define DEBUG_TEARDOWN_FAIL(function_full_name) teardown_function_failure(function_full_name)

	#define DEBUG_RET(function_full_name) if (function_should_fail(function_full_name)) return false
	#define DEBUG_EX(function_full_name) if (function_should_fail(function_full_name)) throw new DebugException(function_full_name)
#else
	#define DEBUG_RET(function_full_name)
	#define DEBUG_EX(function_full_name)
#endif


#endif
