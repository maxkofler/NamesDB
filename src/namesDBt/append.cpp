#include "log.h"
#include "debug.h"

#include "namesDBt.h"

//TODO: Tests

void NamesDBT::append(NamesDBT& db){
	FUN();
	DEBUG_EX("NamesDB::append()");

	LOGF("[NamesDB][append] Appending data from \"" + db._title + "\" to \"" + _title + "\"...");

	
	entry_namesDB* entry = (entry_namesDB*) db._entries;
	std::string name;
	for (size_t i = 0; i < db._count_entries; i++, entry = getNextEntry(entry)){
		name = getEntryName(entry);
		LOGMEM("[NamesDB][append] Appending \"" + name + "\"...");
		add(name, entry->data);
	}
}
