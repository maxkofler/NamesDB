#include "../t_namesDB.h"

TEST(NamesDB, clean_debug){
	FUN();

	std::string funName = "NamesDB::clean()";

	NamesDB* db;

	try{
		DEBUG_PREPARE_FAIL(funName);

		db = new NamesDB();
		db->clean();

		DEBUG_TEARDOWN_FAIL(funName);

		delete db;

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		DEBUG_TEARDOWN_FAIL(funName);
		delete db;
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		DEBUG_TEARDOWN_FAIL(funName);
		delete db;
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

/**
 * @brief	Tests if NamesDB::clean() works correctly
 */
TEST(NamesDB, clean_correct){
	FUN();

	NamesDB db;

	//Just mashed my keyboard at this point
	db._size_entries = 452987;
	db._used_bytes = 234978;
	db._count_entries = 13084;

	//Nothing happens with this pointer, it gets set to nullptr.
	db._last_entry = (entry_namesDB*) &db;

	try{
		db.clean();
	} catch (...) {
		FAIL() << "NamesDB::clean() touched something it should not";
	}
	
	EXPECT_EQ(0, db._size_entries);
	EXPECT_EQ(0, db._used_bytes);
	EXPECT_EQ(0, db._count_entries);
	EXPECT_EQ(nullptr, db._entries);
	EXPECT_EQ(nullptr, db._last_entry);
}
