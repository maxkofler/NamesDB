#include "../t_namesDB.h"

TEST(NamesDB, getEntry_debug){
	FUN();

	std::string funName = "NamesDB::getEntry()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB<int> db;
		db.getEntry(db.add("NewEntry", 0));

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

//Tests if get() reacts correctly to a id that is out of bounds
TEST(NamesDB, getEntry_id_out_of_range){
	FUN();

	NamesDB<int> db;

	EXPECT_EQ(nullptr, db.getEntry(0));
	EXPECT_EQ(nullptr, db.getEntry(1));
	EXPECT_EQ(nullptr, db.getEntry(3498023));

	db.add("Name", 0);

	EXPECT_EQ(nullptr, db.getEntry(1));
}

TEST(NamesDB, getEntry_correct_return){
	FUN();

	std::string name = "This is my name!";
	std::string name2 = "This is a second name!";

	NamesDB<std::string> db;

	size_t id = db.add(name, name);
	size_t id2 = db.add(name2, name2);

	EXPECT_EQ(&name, db.getEntry(id));
	EXPECT_EQ(&name2, db.getEntry(id2));
}

TEST(NamesDB, getEntry_empty){
	FUN();

	NamesDB<int> db;

	EXPECT_EQ(nullptr, db.getEntry(0));
}
