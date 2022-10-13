#include "../t_namesDB.h"

TEST(NamesDB, searchAll_debug){
	FUN();

	std::string funName = "NamesDB::searchAll()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;
		db.add("NewEntry", nullptr);

		db.searchAll("Entry", false);

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

//Checks if searchAll does take the bounds seriously
TEST(NamesDB, searchAll_bounds){
	//searchAll should NOT use 0 as "search to end", this does not allow searching only the first entry
}
