#include "../t_namesDB.h"

#include <fstream>

TEST(NamesDB, export){
	FUN();

	NamesDB db;
	db.add("db", &db);
	db.add("nullptr", nullptr);

	std::ofstream outFile;
	db.add("äueräerüafö!ßdfOutFile", &outFile);
	outFile.open("db.bin", std::ios::binary | std::ios::out);

	db.exportDB(outFile);

	outFile.flush();
	outFile.close();

	NamesDB newDB("newDB");
	std::ifstream inFile;
	inFile.open("db.bin", std::ios::binary | std::ios::in);
	if (!inFile.is_open())
		FAIL() << "Failed to open infile!";

	inFile.clear();

	ASSERT_TRUE(newDB.importDB(inFile));
}
