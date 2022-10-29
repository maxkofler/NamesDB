#include "log.h"
#include "debug.h"

#include "namesDBt.h"

uint64_t NamesDBT::getEntry(size_t id){
	FUN();
	DEBUG_EX("NamesDB::getEntry()");

	entry_namesDB* curEntry = getDBEntry(id);

	#warning Check this return value
	if (curEntry == nullptr)
		return 0;
	else
		return curEntry->data;
}
