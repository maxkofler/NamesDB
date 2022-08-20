#include "log.h"
#include "debug.h"

#include "namesDB.h"

void* NamesDB::getEntry(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getEntry()");

	entry_namesDB* curEntry = getDBEntry(id);

	if (curEntry == nullptr)
		return nullptr;
	else
		return curEntry->data;
}
