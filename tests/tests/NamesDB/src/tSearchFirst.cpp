#include "../t_namesDB.h"

TEST(NamesDB, searchFirst_debug){
	FUN();

	std::string funName = "NamesDB::searchFirst()";

	try{
		DEBUG_FAIL_FUN(funName);

		NamesDB<int> db;
		db.searchFirst("noName", true);

		F_NOTHROW(funName + " - debug");
	} catch (DebugException* e){
		if (e->what() != funName){
			F_WRONGTHROW(funName, e);
		}
	} catch (...){
		F_WRONGEXCEPTION(funName + " - debug");
	}
}

TEST(NamesDB, searchFirst_find_name){
	FUN();

	std::string name = "SomeRandomName";
	std::string name2 = "SomeOtherRandomName2";

	NamesDB<std::string> db;

	size_t id = db.add(name, name);
	size_t id2 = db.add(name2, name2);

	ASSERT_EQ(0, db.searchFirst(name, true).code) << "Could not find the entry";
	ASSERT_EQ(&name, db.searchFirst(name, true).data);

	ASSERT_EQ(0, db.searchFirst(name2, true).code) << "Could not find the entry";
	ASSERT_EQ(&name2, db.searchFirst(name2, true).data);
}

//Tests if searchFirst() finds a name that is scattered throughout a string
TEST(NamesDB, searchFirst_find_scattered_name){
	FUN();

	std::string name = "SCmyOisgnNdfsnhklnTnoeENladT";

	NamesDB<std::string> db;

	size_t id = db.add(name, name);

	ASSERT_NE(0, db.searchFirst("CONTENT", false).code) << "Found a scattered name, this should not be";
}

//Tests if searchFirst() finds a similar string, what it should not do
TEST(NamesDB, searchFirst_similar){
	FUN();

	std::string contentWrong = "myContentIsWrong";
	std::string contentTrue = "Content";

	NamesDB<std::string> db;

	size_t idW = db.add(contentWrong, contentWrong);
	size_t idT = db.add(contentTrue, contentTrue);

	{	//Check if the search find the wrong entry
		namesDB_searchRes res = db.searchFirst("Content", true);

		ASSERT_EQ(0, res.code) << "Could not find the required string";
		EXPECT_NE(&contentWrong, res.data) << "Found the wrong item that was similar";
	}

	{	//Check if the search for "myContent" works correctly
		namesDB_searchRes res = db.searchFirst("myContent", true);

		ASSERT_NE(0, res.code) << "Found a match that should not be";
	}

}

TEST(NamesDB, searchFirst_find_content_start){
	FUN();

	std::string content = "Content";
	std::string name = content + "IsHere";

	NamesDB<std::string> db;

	size_t id = db.add(name, content);

	ASSERT_EQ(0, db.searchFirst(content, false).code) << "Could not find the required string";
	ASSERT_EQ(&content, db.searchFirst(content, false).data) << "Found the wrong entry";
}

TEST(NamesDB, searchFirst_find_content_middle){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWith" + content + "IsHere";

	NamesDB<std::string> db;

	size_t id = db.add(name, content);

	ASSERT_EQ(0, db.searchFirst(content, false).code) << "Could not find the required string";
	ASSERT_EQ(&content, db.searchFirst(content, false).data) << "Found the wrong entry";	//FAILS BECAUSE IMPLEMENTATION IS FLAWED!
}

TEST(NamesDB, searchFirst_find_content_end){
	FUN();

	std::string content = "Content";
	std::string name = "SomeNameWithLoadsOfCharactersAndTheContentIsAtTheEnd" + content;

	NamesDB<std::string> db;

	size_t id = db.add(name, content);

	ASSERT_EQ(0, db.searchFirst(content, false).code) << "Could not find the required string";
	ASSERT_EQ(&content, db.searchFirst(content, false).data) << "Found the wrong entry";	//FAILS BECAUSE IMPLEMENTATION IS FLAWED!
}

//Tests if the argument "search_start" works
TEST(NamesDB, searchFirst_find_from_start_index){
	FUN();

	std::string searchedString = "Content";
	std::string otherString = "Some random entry in the database...";

	NamesDB<std::string> db;

	//std::string* firstPointer = (std::string*) 1;
	//std::string* secondPointer = (std::string*) 2;

	db.add(searchedString, searchedString);
	db.add(otherString, otherString);
	db.add(searchedString, searchedString);

	{
		namesDB_searchRes res = db.searchFirst(searchedString, true);

		ASSERT_EQ(0, res.code) << "Database search failed";
		ASSERT_EQ(&searchedString, res.data) << "searchFirst() could not find the first occurence";
	}

	{
		namesDB_searchRes res = db.searchFirst(searchedString, true);

		ASSERT_EQ(0, res.code) << "Database search failed";
		ASSERT_EQ(&searchedString, res.data) << "searchFirst() could not find the second occurence";
	}

}
