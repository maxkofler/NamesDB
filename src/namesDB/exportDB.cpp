#include "log.h"
#include "debug.h"

#include "namesDB.h"

//TODO: Tests
void NamesDB::exportDB(std::ostream& outStream){
	FUN();
	DEBUG_EX("NamesDB::exportDB()");

	outStream.write((char*)&_bytesUsed, sizeof(size_t));
	outStream.write((char*)_entries, _bytesUsed);
}
