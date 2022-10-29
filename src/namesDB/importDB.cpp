#include "log.h"
#include "debug.h"

#include "namesDBt.h"

#include <exception>

//TODO: Tests
bool NamesDBT::importDB(std::istream& instream){
	FUN();
	DEBUG_EX("NamesDB::importDB()");

	clean();

	instream.read((char*)&_bytesUsed, sizeof(size_t));
	LOGMEM("[NamesDB][importDB] Importing " + std::to_string(_bytesUsed) + " bytes to \"" + _title + "\"...");

	if (!instream){
		LOGE(	"[NamesDB][importDB] Failed to import stream contents to \"" + 
				_title + "\": EOF in length header, read bytes: " + std::to_string(instream.gcount()));
		clean();
		return false;
	}

	instream.read((char*)&_count_entries, sizeof(size_t));
	LOGMEM("[NamesDB][importDB] Importing " + std::to_string(_count_entries) + " entries to \"" + _title + "\"...");

	if (!instream){
		LOGE(	"[NamesDB][importDB] Failed to import stream contents to \"" + 
				_title + "\": EOF in count header, read bytes: " + std::to_string(instream.gcount()));
		clean();
		return false;
	}

	_bytesAllocated = _bytesUsed;
	_entries = new uint8_t[_bytesAllocated];

	instream.read((char*)_entries, _bytesUsed);
	if (!instream){
		LOGE(	"[NamesDB][importDB] Failed to import stream contents to \"" + 
				_title + "\": EOF in data segment, read bytes: " + std::to_string(instream.gcount()));
		clean();
		return false;
	}

	return true;
}
