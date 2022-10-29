#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <cstring>

namesDB_searchRes NamesDBT::searchFirst(std::string search, bool exact, size_t search_start, size_t search_end){
	FUN();
	
	return searchFirst(search.c_str(), search.length(), exact, search_start, search_end);
}

namesDB_searchRes NamesDBT::searchFirst(const char* search, size_t search_len, bool exact, size_t startID, size_t endID){
	FUN();
	DEBUG_EX("NamesDB::searchFirst()");

	if (endID != SIZE_MAX)
		LOGMEM(	"[NamesDB][searchFirst] Searching \"" + _title + "\" for \"" + search + 
				"\" from position " + std::to_string(startID) + " to " + std::to_string(endID) + "...");	
	else
		LOGMEM(	"[NamesDB][searchFirst] Searching \"" + _title + "\" for \"" + search + 
				"\" from position " + std::to_string(startID) + "...");

	entry_namesDB* curEntry = getDBEntry(startID);

	if (curEntry == nullptr){
		namesDB_searchRes res;
		res.code = SEARCHRES_INVALIDARG;
		return res;
	}

	namesDB_searchRes res;
	res.code = SEARCHRES_NOTFOUND;

	size_t matching_chars = 0;
	char* name_entry = nullptr;

	for (size_t indexEntries = startID; indexEntries <= endID && indexEntries < _count_entries; indexEntries++){

		//If the name of the entry is shorter than the searched string, skip this entry
		if (curEntry->nameLen < search_len){
			curEntry = getNextEntry(curEntry);
			continue;
		}

		//If searching exactly AND the name length is longer than the search string, skip this entry
		if (exact && curEntry->nameLen > search_len){
			curEntry = getNextEntry(curEntry);
			continue;
		}

		name_entry = (char*)curEntry + sizeof(entry_namesDB);

		matching_chars = 0;
		size_t sPos = 0;
		for (sPos = 0; sPos < curEntry->nameLen && matching_chars < search_len; sPos++){
			if (search[matching_chars] == name_entry[sPos]){
				matching_chars++;
			} else 
				matching_chars = 0;
		}

		#ifdef DEBUG
		std::string name_entry_string = std::string(name_entry, curEntry->nameLen);
		LOGMEM(	"[NamesDB][searchFirst] Matching characters between " + std::string(search) + " and " + name_entry_string + 
				" at pos " + std::to_string(indexEntries) + ": " + 
				std::to_string(matching_chars) + "/" + std::to_string(search_len));
		#endif

		if (matching_chars == search_len){
			res.code = 0;
			res.data = curEntry->data;
			res.matchStart = sPos - search_len;
			res.matchRemaining = curEntry->nameLen - search_len;
			res.id = indexEntries;
			res.dbEntry = curEntry;
			break;
		}

		curEntry = getNextEntry(curEntry);
	}

	if (res.code == SEARCHRES_NOTFOUND)
		LOGMEM("[NamesDB][searchFirst] Could not find name \"" + std::string(search) + "\" in database \"" + _title + "\"");

	return res;
}
