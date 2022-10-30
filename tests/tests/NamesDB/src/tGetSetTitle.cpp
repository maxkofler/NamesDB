#include "../t_namesDB.h"

TEST(NamesDB, getTitle){
	FUN();

	NamesDB<int> db("MyTitle");
	ASSERT_EQ("MyTitle", db._db._title);
}

TEST(NamesDB, setTitle){
	FUN();

	NamesDB<int> db;

	std::string oldTitle = db.getTitle();
	db.setTitle("NewTitle" + oldTitle);

	ASSERT_NE(oldTitle, db.getTitle());
	ASSERT_EQ("NewTitle"+oldTitle, db.getTitle());
}
