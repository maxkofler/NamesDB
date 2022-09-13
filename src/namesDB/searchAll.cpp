#include "log.h"
#include "debug.h"

#include "namesDB.h"

std::deque<namesDB_searchRes> NamesDB::searchAll(std::string search, bool exact, size_t search_start){
	FUN();
	DEBUG_EX("NamesDB::searchAll()");

	entry_namesDB* startEntry = getDBEntry(search_start);

	if (startEntry == nullptr){
		std::deque<namesDB_searchRes> res;
		return res;
	}

	return searchAllFromEntry(search, startEntry, search_start, exact);
}

std::deque<namesDB_searchRes> NamesDB::searchAllFromEntry(std::string search, entry_namesDB* startEntry, size_t startID, bool exact){
	FUN();
	DEBUG_EX("NamesDB::searchAll()");

	LOGMEM("[NamesDB][searchAll] Searching for all occurences of  \"" + search + "\" from position " + std::to_string(startID) + "...");

	std::deque<namesDB_searchRes> res;

	bool continue_searching = true;
	namesDB_searchRes searchRes;
	entry_namesDB* curStartEntry = startEntry;
	size_t curStartID = startID;

	while(continue_searching){

		searchRes = searchFirstFromEntry(search, curStartEntry, curStartID, exact);

		if (searchRes.code == SEARCHRES_NOTFOUND){
			//The end of the search has been reached
			continue_searching = false;
			continue;
		} else if (searchRes.code != 0)
			continue;

		//From here on we are safe, the result code is 0, everything went fine
		res.push_back(searchRes);

		curStartEntry = NamesDB::getNextEntry(searchRes.dbEntry);
		curStartID = searchRes.id+1;
	}

	return res;
}
