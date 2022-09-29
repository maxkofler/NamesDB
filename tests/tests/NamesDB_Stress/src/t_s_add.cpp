#include "../t_namesDBStress.h"

//Adds loads of names to the database
TEST(NamesDB_Stress, add_loads_of_names){
	FUN();

	NamesDB db;

	try{
		for(size_t i = 0; i < 100000; i++)
			db.add("Name" + std::to_string(i), nullptr);

		db.updateIndex();
		ASSERT_EQ(db._count_entries, db._size_index_entries) << "Index does not contain equal amount of entries!";
	} catch (std::bad_alloc& ba){
		FAIL() << "Adding of loads of entries failed with bad_alloc exception: " + std::string(ba.what());
	} catch (...) {
		FAIL() << "Failed to add loads of entries with exception";
	}
}
