#include "../t_namesDB.h"

TEST(NamesDB, NamesDB_constructor_debug){
	FUN();

	std::string funName = "NamesDB::NamesDB()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB db;

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

TEST(NamesDB, NamesDB_constructor_default_blocksize){
	FUN();

	NamesDB db;

	ASSERT_EQ(1024, db._blockSize);
}

TEST(NamesDB, NamesDB_constructor_specified_blocksize){
	FUN();

	NamesDB db(100234);

	ASSERT_EQ(100234, db._blockSize);
}
