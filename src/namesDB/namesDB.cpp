#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <cstring>

NamesDB::NamesDB(const std::string& name, size_t blockSize) : _name(name){
	FUN();
	DEBUG_EX("NamesDB::NamesDB()");

	LOGMEM("[NamesDB] Creating new names database with block size " + std::to_string(blockSize));

	this->_blockSize = blockSize;

	this->expand(1);
}

NamesDB::~NamesDB(){
	FUN();

	this->clean();
}

NamesDB::NamesDB(const NamesDB& other){
	FUN();
	LOGMEM("[NamesDB] Creating new database from existing one...");

	this->_name = other._name;
	this->_blockSize = other._blockSize;
	this->_blockCount = other._blockCount;
	this->_bytesAllocated = other._bytesAllocated;
	this->_bytesUsed = other._bytesUsed;
	this->_count_entries = other._count_entries;

	this->_entries = new uint8_t[this->_bytesAllocated];

	std::memcpy(this->_entries, other._entries, this->_bytesAllocated);
	this->_last_entry = getDBEntry(this->_count_entries-1);
}
