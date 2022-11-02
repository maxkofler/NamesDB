#include "log.h"
#include "debug.h"

#include "namesDBt.h"

//TODO: Tests
void NamesDBT::exportDB(std::ostream& outStream){
	FUN();
	DEBUG_EX("NamesDB::exportDB()");

	outStream.write((char*)&_bytesUsed, sizeof(size_t));
	outStream.write((char*)&_count_entries, sizeof(size_t));
	outStream.write((char*)_entries, _bytesUsed);
}
