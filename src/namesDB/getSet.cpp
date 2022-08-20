#include "log.h"
#include "namesDB.h"

#include <assert.h>
static_assert(sizeof(void*) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

size_t NamesDB::getEntriesCount(){
	return _count_entries;
}

size_t NamesDB::getBytesUsed(){
	return _bytesUsed;
}

entry_namesDB* NamesDB::getNextEntry(entry_namesDB* current){
	FUN();

	return (entry_namesDB*)(((uint8_t*)current) + sizeof(entry_namesDB) + current->nameLen);
}
