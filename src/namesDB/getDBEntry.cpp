#include "log.h"
#include "debug.h"

#include "namesDB.h"

entry_namesDB* NamesDB::getDBEntry(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getDBEntry()");

	//Check if the ID is out of bounds
	if (id > _count_entries){
		LOGE(	"[NamesDB][getDBEntry] ID " + std::to_string(id) + " for database \"" + _title +
				"\" is out of bounds");
		return nullptr;
	}

	//Get the pointer to the first entry
	entry_namesDB* curEntry = (entry_namesDB*)_entries;

	//Iterate over every entry until we found the entry
	for (size_t i = 1; i <= id; i++){
		if (curEntry->data != nullptr)
			curEntry = (entry_namesDB*)(((uint8_t*)curEntry) + sizeof(entry_namesDB) + curEntry->nameLen);
	}

	return curEntry;
}