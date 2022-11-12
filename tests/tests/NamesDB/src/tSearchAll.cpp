#include "../t_namesDB.h"

TEST(NamesDB, searchAll_debug){
	FUN();

	std::string funName = "NamesDB::searchAll()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB<int> db;
		db.add("NewEntry", 0);

		db.searchAll("Entry", false, true);

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

	std::string str1 = "String1";
	std::string str2 = "String2";

	NamesDB<std::string> db;
	db._db._threads_available = 1;
	db.add("newEntry", str1);
	db.add("newSecondEntry", str2);

	auto res = db.searchAll("new", false, true, 0, 0);
	ASSERT_EQ(1, res.size()) << "Found wrong count of entries";

	db._db._threads_available = 2;
	res = db.searchAll("new", false, true, 0, 0);
	ASSERT_EQ(1, res.size()) << "Found wrong count of entries when using multithreading";
}
