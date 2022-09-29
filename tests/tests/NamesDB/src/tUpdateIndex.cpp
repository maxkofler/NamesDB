#include "../t_namesDB.h"

TEST(NamesDB, updateIndex){
    FUN();

    NamesDB db("Test");
    db.add("null", nullptr);
    db.add("DB", &db);
    db.updateIndex();

    entry_namesDB* dbEntry = (entry_namesDB*)((size_t)db._entries + (size_t)db._index_entries_offset[1]);
    ASSERT_EQ(db.getDBEntry(1), dbEntry) << "Index does not calculate offset correctly!";
}
