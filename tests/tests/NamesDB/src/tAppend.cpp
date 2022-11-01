#include "../t_namesDB.h"

TEST(NamesDB, append){
	FUN();

	int int1 = 1;
	int int2 = 2;
	int intnul = 0;

	NamesDB<int> db1;
	db1.add("int1", int1);

	NamesDB<int> db2;
	db2.add("int2", int2);
	db2.add("dbnul", intnul);

	ASSERT_EQ(1, db1.getEntriesCount()) << "DB1 has more than 1 entry";
	ASSERT_EQ(2, db2.getEntriesCount()) << "DB2 has more than 2 entry";

	db1.append(db2);

	ASSERT_EQ(3, db1.getEntriesCount()) << "DB2 was not appended to DB1 correctly";
}
