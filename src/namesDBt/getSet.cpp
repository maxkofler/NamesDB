#include "log.h"
#include "namesDBt.h"

#include <assert.h>
static_assert(sizeof(void*) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

void NamesDBT::setTitle(const std::string& title){
	_title = title;
}

std::string NamesDBT::getTitle(){
	return _title;
}

size_t NamesDBT::getEntriesCount(){
	return _count_entries;
}

size_t NamesDBT::getBytesUsed(){
	return _bytesUsed;
}

entry_namesDB* NamesDBT::getNextEntry(entry_namesDB* current){
	FUN();

	return (entry_namesDB*)(((uint8_t*)current) + sizeof(entry_namesDB) + current->nameLen);
}
