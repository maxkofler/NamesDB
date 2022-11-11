#include "../t_namesDB.h"

#include <fstream>

TEST(NamesDB, import_export){
	FUN();

	std::string string1 = "string1";
	std::string string2 = "string2";
	std::string string3 = "string3äü?!'*#";

	NamesDB<std::string> db;
	db.add(string1, string1);
	db.add(string2, string2);
	db.add(string3, string3);


	{	//Export
		std::ofstream outFile;
		outFile.open("db.bin", std::ios::binary | std::ios::out);
		db.exportDB(outFile);

		outFile.flush();
		outFile.close();
	}

	NamesDB<std::string> newDB("newDB");
	

	{	//Import
		std::ifstream inFile;
		inFile.open("db.bin", std::ios::binary | std::ios::in);
		if (!inFile.is_open())
			FAIL() << "Failed to open infile!";
		inFile.clear();

		ASSERT_TRUE(newDB.importDB(inFile));
	}

	ASSERT_EQ(string1, *newDB.getEntry(0)) << "Import and export did not work (Changed values)";
	ASSERT_EQ(string2, *newDB.getEntry(1)) << "Import and export did not work (Changed values)";
	ASSERT_EQ(string3, *newDB.getEntry(2)) << "Import and export did not work (Changed values)";

	ASSERT_EQ(string1, *newDB.searchFirst(string1, true).data) << "Import and export did not work (Changed values in search)";
	ASSERT_EQ(string2, *newDB.searchFirst(string2, true).data) << "Import and export did not work (Changed values in search)";
	ASSERT_EQ(string3, *newDB.searchFirst(string3, true).data) << "Import and export did not work (Changed values in search)";
}
