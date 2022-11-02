#ifndef __NAMESDB_T_H__
#define __NAMESDB_T_H__

#include <stdlib.h>				//size_t
#include <string>
#include <deque>
#include <ostream>
#include <istream>

#ifdef _WIN32
    #define GNU_ATTRIBUTE_PACKED
#else
    #define GNU_ATTRIBUTE_PACKED __attribute__((packed))
#endif

#ifdef _WIN32
	#pragma pack(push, 1)
#endif

struct entry_namesDB{
	uint64_t					data;
	uint8_t						nameLen;
} GNU_ATTRIBUTE_PACKED;

#ifdef _WIN32
	#pragma pack(pop)
#endif

#define SEARCHRES_NOTFOUND -1
#define SEARCHRES_INVALIDARG -2

#define NAMESDB_OUT_OF_BOUNDS UINT64_MAX

struct namesDBt_searchRes{
	int8_t						code = 0;
	uint8_t						matchStart = 0;		//The place the match starts in the results name
	uint8_t						matchRemaining = 0;	//The remaining characters that did not match of the name (is name.length - search.length)
	uint64_t					data;
	size_t						id;
	entry_namesDB*				dbEntry;
};

class NamesDBT{

public:
	
	/**
	 * @brief	Creates a new names database
	 * @param	title			The title of the database
	 * @param	blockSize		The size of the blocks that get allocated
	 */
	NamesDBT(const std::string& title = "Untitled", size_t blockSize = 1024);
	~NamesDBT();

	/**
	 * @brief	Creates a new database from an existing one
	 * @param	other			The database to copy
	 */
	NamesDBT(const NamesDBT& other);
	
	/**
	 * @brief	Expands the internal database by the supplied amount of blocks
	 * @param	count			The amount of blocks to expand by
	 * @return	If false, the database could not be expanded, DELETE IT AFTER A FAILURE!!!
	 * 			Typically this happens when the system is out of memory
	 */
	bool						expand(uint8_t count = 1);

	/**
	 * @brief	Cleans the whole database, including every allocated object
	 */
	void						clean();

	/**
	 * @brief	Adds the supplied string to the database
	 * @param	str				The string to add
	 * @param	entry			The entry to register
	 * @return	size_t			The id of the name
	 */
	size_t						add(const std::string& str, uint64_t entry);

	/**
	 * @brief	Changes the name of the database
	 * @param	title			The new title of the database
	 */
	void						setTitle(const std::string& title);

	/**
	 * @brief	Returns the title of the database
	 */
	std::string					getTitle();

	/**
	 * @brief	Appends the contents of the supplied database to this
	 * @param	db				The db to append the contents of
	 */
	void						append(NamesDBT& db);

	/**
	 * @brief	Gets the entry with the specified id of this database (Can be slow if updateIndex() is omitted)
	 * @param	id				The id to search (received from add())
	 * @return	uint64_t		The entry stored in the database, NAMESDB_OUT_OF_BOUNDS if out of bounds
	 */
	uint64_t					getEntry(size_t id);

	/**
	 * @brief	Searches for the database entry with the supplied id and returns a pointer to it
	 * @param	id				The id of the searched entry
	 * @return	entry_namesDB*	A pointer to the db entry
	 */
	entry_namesDB*				getDBEntry(size_t id);

	/**
	 * @brief	Gets the name string of the specified id (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	std::string		The name previously supplied to add(), empty if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	std::string					getName(size_t id);

	/**
	 * @brief	Gets the name string of the specified entry
	 * @param	entry			The entry to get the name from
	 * @return	std::string		The name previously supplied to add()
	 */
	static std::string			getEntryName(entry_namesDB* entry);

	/**
	 * @brief	Searches for the first occurrence of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exactly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	namesDB_searchRes	The search result
	 */
	namesDBt_searchRes			searchFirst(std::string name, bool exact, size_t startID = 0, size_t endID = SIZE_MAX);

	/**
	 * @brief	Searches for the first occurence of the specified name
	 * @param	name			The name to search for
	 * @param	nameLen			The length of the name
	 * @param	exact			If the string has to match exactly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	namesDB_searchRes	The search result
	 */
	namesDBt_searchRes			searchFirst(const char* name, size_t nameLen, bool exact, size_t startID = 0, size_t endID = SIZE_MAX);

	/**
	 * @brief	Searches all occurences of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exacltly or if it can be a substring
	 * @param	start_id		The id to start searching from
	 * @param	end_id			The id to stop searching at (inclusive)
	 * @return	A deque holding instances of namesDB_searchRes
	 */
	std::deque<namesDBt_searchRes>	searchAll(std::string name, bool exact, size_t start_id = 0, size_t end_id = SIZE_MAX);

	/**
	 * @brief	Returns the amount of entries stored in this database
	 */
	size_t						getEntriesCount();

	/**
	 * @brief	Returns the bytes used by this database
	 */
	size_t						getBytesUsed();

	/**
	 * @brief	Exports this databases contents to the supplied stream
	 * @param	outStream		The stream to export to
	 */
	void						exportDB(std::ostream& outStream);

	/**
	 * @brief	Imports the contents of this database form the supplied stream
	 * @note	This clears the contents of this database
	 * @param	inStream		The stream to import from
	 */
	bool						importDB(std::istream& inStream);

	/**
	 * @brief	Updates the internal index for fast access
	 * @note	This should be done before using id-based access after creating a new DB or updating it
	 */
	void						updateIndex();

	/**
	 * @brief	Calculates the next database entry pointer from the provided pointer
	 * @param	cur				The entry to calculate from
	 * @return	entry_namesDB*	The calculated next entry (not guaranteed to be valid)
	 */
	static entry_namesDB*		getNextEntry(entry_namesDB* cur);

#ifndef FRIEND_NAMES_DB_T
private:
#endif

	/**
	 * @brief	The title of the database (default="Untitled_xx")
	 */
	std::string					_title;

	/**
	 * @brief	The size of the  allocations
	 */
	size_t						_blockSize;

	/**
	 * @brief	The amount of blocks reserved
	 */
	size_t						_blockCount = 0;

	/**
	 * @brief	The amount of bytes allocated to the entries field (is _blockSize * _blockCount)
	 */
	size_t						_bytesAllocated = 0;

	/**
	 * @brief	The bytes used of the entries field
	 */
	size_t						_bytesUsed = 0;

	/**
	 * @brief	The amount of entries stored in this database
	 */
	size_t						_count_entries = 0;

	/**
	 * @brief	All the entries
	 * This is the entry point into the names, this is NOT an array!
	 * This is allocated in bytes, hence the uint8_t
	 */
	uint8_t*					_entries = nullptr;

	/**
	 * @brief	The last entry to fill in the next pointer
	 */
	entry_namesDB*				_last_entry = nullptr;

	/**
	 * @brief	Stores an array of quick indexes to the entries offsets in bytes from _entries
	 */
	size_t*						_index_entries_offset = nullptr;

	/**
	 * @brief	Stores the size of the index, this can be different from _count_entries if
	 * 			the index does not get update immediately
	 */
	size_t						_size_index_entries = 0;

	/**
	 * @brief	The amount of threads the searching progress can use (default=system threads)
	 */
	size_t						_threads_available = 0;

	/**
	 * @brief	Searches all occurences of the specified name in a single thread
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exacltly or if it can be a substring
	 * @param	start_id		The id to start searching from
	 * @param	end_id			The id to stop searching at (inclusive)
	 * @return	A deque holding instances of namesDB_searchRes
	 */
	std::deque<namesDBt_searchRes>	searchAllST(std::string name, bool exact, size_t start_id = 0, size_t end_id = SIZE_MAX);

};

#endif
