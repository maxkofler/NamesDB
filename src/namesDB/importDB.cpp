#include "log.h"
#include "debug.h"

#include "namesDB.h"

#include <exception>

//TODO: Tests
bool NamesDB::importDB(std::istream& instream){
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

	size_t block_to_allocate = (_bytesUsed / _blockSize) + 1;
	expand(block_to_allocate);

	instream.read((char*)_entries, _bytesUsed);
	if (!instream){
		LOGE(	"[NamesDB][importDB] Failed to import stream contents to \"" + 
				_title + "\": EOF in data segment, read bytes: " + std::to_string(instream.gcount()));
		clean();
		return false;
	}

	return true;
}
