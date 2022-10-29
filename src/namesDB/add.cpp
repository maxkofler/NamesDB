#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <cstring>

#include <assert.h>
static_assert(sizeof(uint64_t) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

size_t NamesDB::add(const std::string& str, uint64_t entry_insert){
	FUN();
	DEBUG_EX("NamesDB::add()");

	LOGMEM("[NamesDB][add] Adding new name to database \"" + _title + "\": \"" + str + "\"");

	//Note the amount of bytes needed for this entry
	uint8_t size_entry = sizeof(entry_namesDB) + str.length();

	//Allocate enough memory for this operation
	while(_bytesAllocated < (_bytesUsed + size_entry))
		expand();

	//Get a pointer to the begin of this new entry
	entry_namesDB* entry = (entry_namesDB*)(_entries + _bytesUsed);

	//Set the entries carried entry
	entry->data = entry_insert;

	//Set the entry name length and copy the name
	entry->nameLen = str.length();
	uint8_t* nameStart = _entries + _bytesUsed + sizeof(entry_namesDB);
	std::memcpy(nameStart, str.c_str(), str.length());

	//Update the database
	_bytesUsed += size_entry;
	_last_entry = entry;

	//Determine the id of this entry, add it and return it
	size_t id = _count_entries;
	_count_entries++;

	return id;
}
