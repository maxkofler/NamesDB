#include "../t_namesDB.h"

TEST(NamesDB, iterator_begin_end_not_same){
	FUN();

	NamesDB db;
	db.add("db", &db);

	ASSERT_NE(db.begin(), db.end()) << "begin() and end() are the same";
}

TEST(NamesDB, iterator){
	FUN();

	NamesDB db;
	db.add("db", &db);

	size_t iterations = 0;
	for (auto entry : db){
		ASSERT_EQ(&db, entry.data) << "Did not iterate correctly!";
		iterations++;
	}

	ASSERT_EQ(db.getEntriesCount(), iterations);
}
