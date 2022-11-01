#include "../t_namesDBStress.h"

#include <chrono>

//Adds loads of names to the database
TEST(NamesDB_Stress, searchAll_loads_of_names){
	FUN();
	using namespace std::chrono;

	std::string name = "name";
	std::string finalName = "TheFinalName";

	NamesDB<std::string> db;
	size_t num = 1000;

	Log::level oldLevel = hlog->getLevel();
	hlog->setLevel(Log::U);
	for (size_t n = 0; n < num; n++){
		for (size_t i = 0; i < 1000; i++){
			db.add("Entry" + std::to_string(i), name);
		}
		db.add(finalName, finalName);
	}
	hlog->setLevel(oldLevel);

	db.updateIndex();

	{
		auto indexStart = high_resolution_clock::now();
		hlog->setLevel(Log::U);
		std::deque<namesDB_searchRes<std::string>> res = db.searchAll(finalName, false);
		hlog->setLevel(oldLevel);
		auto indexStop = high_resolution_clock::now();
		auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);
		LOGU("Multithreaded took " + std::to_string(indexDuration.count()) + " ms");

		ASSERT_EQ(num, res.size()) << "Wrong count!";
	}
	
	{
		db._db._threads_available = 1;
		auto indexStart = high_resolution_clock::now();
		hlog->setLevel(Log::U);
		std::deque<namesDB_searchRes<std::string>> res = db.searchAll(finalName, false);
		hlog->setLevel(oldLevel);
		auto indexStop = high_resolution_clock::now();
		auto indexDuration = duration_cast<milliseconds>(indexStop - indexStart);
		LOGU("Singlethreaded took " + std::to_string(indexDuration.count()) + " ms");

		ASSERT_EQ(num, res.size()) << "Wrong count!";
	}
	
}
