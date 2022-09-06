#include "log.h"
#include "debug.h"

#include "namesDB.h"

void NamesDB::clean(){
	FUN();
	DEBUG_EX("NamesDB::clean()");

	LOGF("[NamesDB][clean] Cleaning contents of database \"" + _title + "\"...");

	if (_entries != nullptr){
		delete _entries;
		_entries = nullptr;
	}

	_blockCount = 0;
	_bytesAllocated = 0;
	_bytesUsed = 0;
	_count_entries = 0;
	_last_entry = nullptr;
}
