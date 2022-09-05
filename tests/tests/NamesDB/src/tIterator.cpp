#include "../t_namesDB.h"

TEST(NamesDB, iterator){
	FUN();

	NamesDB db;
	db.add("db", &db);

	for (auto entry : db){
		ASSERT_EQ(&db, entry.data) << "Did not iterate correctly!";
	}
}
