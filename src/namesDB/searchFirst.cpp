#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <cstring>

namesDB_searchRes NamesDB::searchFirst(std::string search, bool exact, size_t search_start){
	FUN();
	DEBUG_EX("NamesDB::searchFirst()");

	LOGMEM("[NamesDB][searchFirst] Searching for \"" + search + "\" from position " + std::to_string(search_start) + "...");

	//Get the pointer to the first entry
	//entry_namesDB* curEntry = (entry_namesDB*)_entries;
	entry_namesDB* curEntry = getDBEntry(search_start);

	if (curEntry == nullptr){
		namesDB_searchRes res;
		res.code = -2;
		return res;
	}

	return searchFirstFromEntry(search, curEntry, search_start, exact);

}

namesDB_searchRes NamesDB::searchFirstFromEntry(std::string search, entry_namesDB* startEntry, size_t startID, bool exact){
	FUN();

	if (startEntry == nullptr){
		namesDB_searchRes res;
		res.code = SEARCHRES_INVALIDARG;
		return res;
	}

	namesDB_searchRes res;
	res.code = SEARCHRES_NOTFOUND;

	//Create a local c string for fast access
	size_t len_search = search.length();
	//char* name_cStr = new char[len_name+1];
	//std::memcpy(name_cStr, name.c_str(), len_name);
	//name_cStr[len_name] = 0;
	const char* search_cStr = search.c_str();

	//Get the pointer to the first entry
	//entry_namesDB* curEntry = (entry_namesDB*)_entries;
	entry_namesDB* curEntry = startEntry;

	size_t matching_chars = 0;
	char* name_entry = nullptr;

	for (size_t indexEntries = startID; indexEntries < _count_entries; indexEntries++){

		//If the name of the entry is shorter, skip this entry
		if (curEntry->nameLen < len_search){
			curEntry = (entry_namesDB*)(((uint8_t*)curEntry) + sizeof(entry_namesDB) + curEntry->nameLen);
			continue;
		}

		//If the name of the entry is longer, skip it too
		if (exact && curEntry->nameLen > len_search){
			curEntry = (entry_namesDB*)(((uint8_t*)curEntry) + sizeof(entry_namesDB) + curEntry->nameLen);
			continue;
		}

		name_entry = (char*)curEntry + sizeof(entry_namesDB);

		matching_chars = 0;
		size_t sPos = 0;
		for (sPos = 0; sPos < curEntry->nameLen && matching_chars < len_search; sPos++){
			if (search_cStr[matching_chars] == name_entry[sPos]){
				matching_chars++;
			} else 
				matching_chars = 0;
		}

		#ifdef DEBUG
		std::string name_entry_string = std::string(name_entry, curEntry->nameLen);

		LOGMEM(	"[NamesDB][searchFirst] Matching characters between " + search + " and " + name_entry_string + 
				" at pos " + std::to_string(indexEntries) + ": " + 
				std::to_string(matching_chars) + "/" + std::to_string(search.length()));
		#endif

		if (matching_chars == len_search){
			res.code = 0;
			res.data = curEntry->data;
			res.matchStart = sPos - len_search;
			res.matchRemaining = curEntry->nameLen - len_search;
			res.id = indexEntries;
			res.dbEntry = curEntry;
			break;
		}

		curEntry = (entry_namesDB*)(((uint8_t*)curEntry) + sizeof(entry_namesDB) + curEntry->nameLen);
	}

	LOGMEM("[NamesDB][searchFirst] Could not find name \"" + search + "\"");

	
	return res;
}
