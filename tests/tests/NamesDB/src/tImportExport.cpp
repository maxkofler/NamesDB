#include "../t_namesDB.h"

#include <fstream>

TEST(NamesDB, export){
	FUN();

	std::string testString = "Test";

	NamesDB<std::string> db;
	db.add("db", &testString);
	db.add("nullptr", nullptr);

	std::ofstream outFile;
	db.add("äueräerüafö!ßdftestString", &testString);
	outFile.open("db.bin", std::ios::binary | std::ios::out);

	db.exportDB(outFile);

	outFile.flush();
	outFile.close();

	NamesDB<std::string> newDB("newDB");
	std::ifstream inFile;
	inFile.open("db.bin", std::ios::binary | std::ios::in);
	if (!inFile.is_open())
		FAIL() << "Failed to open infile!";

	inFile.clear();

	ASSERT_TRUE(newDB.importDB(inFile));
}
