#include "../t_namesDB.h"

TEST(NamesDB, updateIndex){
    FUN();

    int testInt = 1;
    int nullInt = 0;

    NamesDB<int> db("Test");
    db.add("null", nullInt);
    db.add("DB", testInt);
    db.updateIndex();

    entry_namesDB* dbEntry = (entry_namesDB*)((size_t)db._db._entries + (size_t)db._db._index_entries_offset[1]);
    ASSERT_EQ(db._db.getDBEntry(1), dbEntry) << "Index does not calculate offset correctly!";
}
