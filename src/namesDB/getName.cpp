#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <cstring>

#include <assert.h>
static_assert(sizeof(void*) + sizeof(uint8_t) == sizeof(entry_namesDB), "Size of entry_namesDB changed, adjust this file!");

std::string NamesDBT::getName(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getName()");

	//Check if the ID is out of bounds
	if (id >= _count_entries){
		LOGE(	"[NamesDB][getName] ID " + std::to_string(id) + " for database \"" + _title + 
				"\" is out of bounds");
		return std::string();
	}

	//Get the pointer to the entry
	entry_namesDB* curEntry = getDBEntry(id);

	return getEntryName(curEntry);
}

std::string NamesDBT::getEntryName(entry_namesDB* entry){
	FUN();

	//Allocate memory for the name to copy to, including the nullterminator
	char* name_cStr = new char[entry->nameLen+1];

	//Construct a pointer to the start of the name in the _entries data block
	uint8_t* start_name = (uint8_t*) entry + sizeof(entry_namesDB);

	//Copy the name using memcpy and append the nullterminator
	std::memcpy(name_cStr, start_name, entry->nameLen);
	name_cStr[entry->nameLen] = 0;

	//Put the name into a std::string
	std::string ret = std::string(name_cStr);
	
	//Remove the memory for the buffered name
	delete[] name_cStr;

	return ret;
}
