#include "../t_namesDB.h"

TEST(NamesDB, append){
	FUN();

	NamesDB db1;
	db1.add("db1", &db1);

	NamesDB db2;
	db2.add("db2", &db2);
	db2.add("dbnul", nullptr);

	ASSERT_EQ(1, db1.getEntriesCount()) << "DB1 has more than 1 entry";
	ASSERT_EQ(2, db2.getEntriesCount()) << "DB2 has more than 2 entry";

	db1.append(db2);

	ASSERT_EQ(3, db1.getEntriesCount()) << "DB2 was not appended to DB1 correctly";
}
