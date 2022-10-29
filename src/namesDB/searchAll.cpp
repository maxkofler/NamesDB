#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <future>

std::deque<namesDB_searchRes> NamesDBT::searchAll(std::string search, bool exact, size_t startID, size_t endID){
	FUN();
	DEBUG_EX("NamesDB::searchAll()");

	size_t real_end = endID;
	if (endID == SIZE_MAX)
		real_end = _count_entries;

	size_t jobsPerThread = (real_end - startID) / _threads_available;
	std::deque<std::future<std::deque<namesDB_searchRes>>> futures;

	size_t thread_startID;
	size_t usable_threads = _threads_available;

	//Safety for not finding entries multiple times
	if (_count_entries < usable_threads*2)
		usable_threads = 1;

	for (size_t i = 0; i < usable_threads-1; i++){
		thread_startID = startID + (jobsPerThread*i);
		futures.push_back(std::async(&NamesDBT::searchAllST, this, search, exact, thread_startID, thread_startID+jobsPerThread-1));
	}

	//Handle the last job separately
	thread_startID = startID + (jobsPerThread * (_threads_available-1));
	futures.push_back(std::async(&NamesDBT::searchAllST, this, search, exact, thread_startID, SIZE_MAX));

	//Wait for all results to come in
	std::deque<namesDB_searchRes> res;
	size_t futuresSize = futures.size();

	for (size_t i = 0; i < futuresSize; i++){
		//LOGU("Thread " + std::to_string(i) + " joined!");
		for (namesDB_searchRes n : futures.at(i).get())
			res.push_back(n);
	}
	
	//return searchAllST(search, exact, startID, endID);
	return res;
}

std::deque<namesDB_searchRes> NamesDBT::searchAllST(std::string search, bool exact, size_t startID, size_t endID){
	FUN();
	DEBUG_EX("NamesDB::searchAllST()");

	LOGMEM("[NamesDB][searchAll] Searching for all occurences of  \"" + search + "\" from position " + std::to_string(startID) + "...");

	std::deque<namesDB_searchRes> res;

	const char* search_cStr = search.c_str();
	size_t search_len = search.length();

	namesDB_searchRes searchRes;
	size_t curStartID = startID;

	for (curStartID = startID; curStartID <= endID; curStartID++){
		searchRes = searchFirst(search_cStr, search_len, exact, curStartID, endID);

		if (searchRes.code == SEARCHRES_NOTFOUND || searchRes.code == SEARCHRES_INVALIDARG){
			//The end of the search has been reached
			break;
		} else if (searchRes.code != 0)
			continue;

		//From here on we are safe, the result code is 0, everything went fine
		res.push_back(searchRes);
		curStartID = searchRes.id+1;
	}

	return res;
}
