#include "log.h"
#include "debug.h"

#include "namesDBt.h"

uint64_t NamesDBT::getEntry(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getEntry()");

	entry_namesDB* curEntry = getDBEntry(id);

	if (curEntry == nullptr)
		return NAMESDB_OUT_OF_BOUNDS;
	else
		return curEntry->data;
}
