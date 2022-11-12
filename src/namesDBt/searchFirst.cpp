#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <cstring>

namesDBt_searchRes NamesDBT::searchFirst(std::string search, bool exact, bool matchCase, uint64_t search_start, uint64_t search_end){
	FUN();
	
	return searchFirst(search.c_str(), search.length(), exact, matchCase, search_start, search_end);
}

namesDBt_searchRes NamesDBT::searchFirst(const char* searchOrig, size_t searchOrig_len, bool exact, bool matchCase, uint64_t startID, uint64_t endID){
	FUN();
	DEBUG_EX("NamesDB::searchFirst()");

	char* search = new char[searchOrig_len];
	size_t search_len = searchOrig_len;

	//If matchCase is turned off, put every character in the searched string to lowercase
	if (matchCase){
		std::strcpy(search, searchOrig);
	} else {
		for(size_t i = 0; i < search_len; i++)
			search[i] = std::tolower(searchOrig[i]);
	}

	//Plot some information about the operation
	if (endID != SIZE_MAX)
		LOGMEM(	"[NamesDB][searchFirst] Searching \"" + _title + "\" for \"" + search + 
				"\" from position " + std::to_string(startID) + " to " + std::to_string(endID) + "...");	
	else
		LOGMEM(	"[NamesDB][searchFirst] Searching \"" + _title + "\" for \"" + search + 
				"\" from position " + std::to_string(startID) + "...");

	namesDBt_searchRes res;

	//Get the entry where the search should start from
	entry_namesDB* curEntry = getDBEntry(startID);

	//Check the entry for existance
	if (curEntry == nullptr){
		res.code = SEARCHRES_INVALIDARG;
		delete[] search;
		return res;
	}

	//Setup some variables
	res.code = SEARCHRES_NOTFOUND;
	uint64_t matching_chars, name_pos = 0;
	char* name_curEntry = nullptr;

	for (uint64_t indexEntries = startID; indexEntries <= endID && indexEntries < _count_entries; indexEntries++, curEntry = getNextEntry(curEntry)){

		//If the name of the entry is shorter than the searched string, skip this entry
		if (curEntry->nameLen < search_len)
			continue;

		//If searching exactly AND the name length is longer than the search string, skip this entry
		if (exact && curEntry->nameLen > search_len)
			continue;

		//Get a pointer to the name
		name_curEntry = (char*)curEntry + sizeof(entry_namesDB);

		//Iterate over every character in the name and check if it is matching, else skip it
		matching_chars = name_pos = 0;
		for (name_pos = 0; name_pos < curEntry->nameLen && matching_chars < search_len; name_pos++){
			//If matchCase is turned off, change the character to lowercase first
			if (matchCase){
				if (search[matching_chars] == name_curEntry[name_pos])
					matching_chars++;
				else 
					matching_chars = 0;
			} else {
				if (search[matching_chars] == std::tolower(name_curEntry[name_pos]))
					matching_chars++;
				else 
					matching_chars = 0;
			}	
		}

		//If debugging is enabled, print a message
		#ifdef DEBUG
			std::string name_entry_string = std::string(name_curEntry, curEntry->nameLen);
			LOGMEM(	"[NamesDB][searchFirst] Matching characters between " + std::string(search) + " and " + name_entry_string + 
					" at pos " + std::to_string(indexEntries) + ": " + 
					std::to_string(matching_chars) + "/" + std::to_string(search_len));
		#endif

		//If we have a match, return
		if (matching_chars == search_len){
			res.code = 0;
			res.data = curEntry->data;
			res.matchStart = name_pos - search_len;
			res.matchRemaining = curEntry->nameLen - search_len;
			res.id = indexEntries;
			res.dbEntry = curEntry;
			break;
		}

	}

	if (res.code == SEARCHRES_NOTFOUND)
		LOGMEM("[NamesDB][searchFirst] Could not find name \"" + std::string(search) + "\" in database \"" + _title + "\"");

	delete[] search;
	return res;
}
