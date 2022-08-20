#include "../t_namesDBStress.h"

//Adds loads of names to the database
TEST(NamesDB_Stress, searchFirst_loads_of_names){
	FUN();

	std::string finalName = "TheFinalName";

	NamesDB db;

	for (size_t i = 0; i < 500; i++){
		db.add("Entry" + std::to_string(i),  &db);
	}

	db.add(finalName, &finalName);

	entry_namesDB* res = db.searchFirst(finalName);

	ASSERT_NE(nullptr, res) << "Could not find the required string";
	EXPECT_EQ(&finalName, res->entry) << "Found the wrong entry";
}
