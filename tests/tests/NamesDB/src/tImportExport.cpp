#include "../t_namesDB.h"

#include <fstream>

TEST(NamesDB, export){
	FUN();

	std::string testString = "Test";
	std::string nullString = "null";

	NamesDB<std::string> db;
	db.add("db", testString);
	db.add("nullString", nullString);

	std::ofstream outFile;
	db.add("äueräerüafö!ßdftestString", testString);
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

	ASSERT_EQ(testString, *newDB.getEntry(0)) << "Import and export did not work (Changed values)";
	ASSERT_EQ(nullString, *newDB.getEntry(1)) << "Import and export did not work (Changed values)";
}
