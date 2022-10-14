#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <thread>

std::deque<namesDB_searchRes> NamesDB::searchAll(std::string search, bool exact, size_t startID, size_t endID){
	FUN();
	DEBUG_EX("NamesDB::searchAll()");

	LOGMEM("[NamesDB][searchAll] Searching for all occurences of  \"" + search + "\" from position " + std::to_string(startID) + "...");

	std::deque<namesDB_searchRes> res;

	const char* search_cStr = search.c_str();
	size_t search_len = search.length();

	namesDB_searchRes searchRes;
	size_t curStartID = startID;

	for (curStartID = startID; curStartID <= endID; curStartID++){
		searchRes = searchFirst(search_cStr, search_len, exact, curStartID, endID);

		if (searchRes.code == SEARCHRES_NOTFOUND){
			//The end of the search has been reached
			break;
		} else if (searchRes.code != 0)
			continue;

		//From here on we are safe, the result code is 0, everything went fine
		res.push_back(searchRes);
	}

	return res;
}
