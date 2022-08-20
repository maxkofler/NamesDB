#include "../t_.h"

TEST(, _debug){
	FUN();

	std::string funName = "";

	try{
		DEBUG_FAIL_FUN(funName);



		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

TEST(, ){
	FUN();

}
