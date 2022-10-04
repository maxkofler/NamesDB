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

	entry_namesDB* curEntry = nullptr;

	//If the id is in the indexed entries, use the index to look it up
	if (id < _size_index_entries){
		curEntry = (entry_namesDB*)(((size_t)_entries) + _index_entries_offset[id]);
	} else {
		LOGDW("[NamesDB][getDBEntry] Index miss! You should consider updating the index by calling updateIndex()!");
		//Get the pointer to the first entry
		curEntry = (entry_namesDB*)_entries;

		//Iterate over every entry until we found the entry
		for (size_t i = 1; i <= id && i < _count_entries; i++){
			curEntry = getNextEntry(curEntry);
		}
	}

	return curEntry;
}