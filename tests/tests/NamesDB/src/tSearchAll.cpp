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
	FUN();

	NamesDB db;
	db._threads_available = 1;
	db.add("newEntry", &db);
	db.add("newSecondEntry", &db);

	auto res = db.searchAll("new", false, 0, 0);
	ASSERT_EQ(1, res.size()) << "Found wrong count of entries";

	db._threads_available = 2;
	res = db.searchAll("new", false, 0, 0);
	ASSERT_EQ(1, res.size()) << "Found wrong count of entries when using multithreading";
}
