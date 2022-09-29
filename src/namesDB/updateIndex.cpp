#include "log.h"
#include "debug.h"

#include "namesDB.h"

void NamesDB::updateIndex(){
    FUN();
    DEBUG_EX("NamesDB::updateIndex()");
    
    LOGF("[NamesDB][updateIndex] Updating index of db \"" + _title + "\"...");

    if (_index_entries_offset != nullptr)
        delete _index_entries_offset;

    _size_index_entries = _count_entries;
    _index_entries_offset = new size_t[_size_index_entries];

    entry_namesDB* curEntry = (entry_namesDB*)_entries;
    if (_size_index_entries > 0)
        _index_entries_offset[0] = 0;

    for (size_t i = 1; i < _size_index_entries; i++){
        curEntry = getNextEntry(curEntry);
        _index_entries_offset[i] = ((size_t)curEntry) - ((size_t)_entries);
    }
}
