#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <cstring>
#include <thread>

static size_t untitled_num = 0;

NamesDBT::NamesDBT(const std::string& title, size_t blockSize) : _title(title){
	FUN();
	DEBUG_EX("NamesDB::NamesDB()");

	_threads_available = std::thread::hardware_concurrency();
	if (_threads_available == 0)
		_threads_available = 1;

	LOGD("[NamesDB] Using up to " + std::to_string(_threads_available) + " threads");

	if (_title == "Untitled"){
		_title += "_" + std::to_string(untitled_num);
		untitled_num++;
	}

	LOGMEM("[NamesDB] Creating new names database \"" + _title + "\" with block size " + std::to_string(blockSize));

	this->_blockSize = blockSize;

	this->expand(1);
}

NamesDBT::~NamesDBT(){
	FUN();

	this->clean();
}

NamesDBT::NamesDBT(const NamesDBT& other){
	FUN();

	_threads_available = std::thread::hardware_concurrency();

	LOGMEM("[NamesDB] Creating new database \"" + other._title + "\" from existing one...");

	this->_title = other._title + "_copy" + std::to_string(untitled_num);
	untitled_num++;
	this->_blockSize = other._blockSize;
	this->_blockCount = other._blockCount;
	this->_bytesAllocated = other._bytesAllocated;
	this->_bytesUsed = other._bytesUsed;
	this->_count_entries = other._count_entries;

	this->_entries = new uint8_t[this->_bytesAllocated];

	std::memcpy(this->_entries, other._entries, this->_bytesAllocated);
	this->_last_entry = getDBEntry(this->_count_entries-1);
}
