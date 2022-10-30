#ifndef __NAMESDB_H__
#define __NAMESDB_H__

#define FRIEND_NAMES_DB_T
#include "namesDBt.h"

template<typename T>
class NamesDB{

public:
	/**
	 * @brief	Creates a new names database
	 * @param	title			The title of the database
	 * @param	blockSize		The size of the blocks that get allocated
	 */
	NamesDB(const std::string& title = "Untitled", size_t blockSize = 1024)
		: _db(title, blockSize){
		FUN();
	}
	~NamesDB(){
		FUN();
	}

	/**
	 * @brief	Creates a new database from an existing one
	 * @param	other			The database to copy
	 */
	NamesDB(const NamesDB<T>& other)
		: _db(other._db){
		FUN();
	}
	
	/**
	 * @brief	Expands the internal database by the supplied amount of blocks
	 * @param	count			The amount of blocks to expand by
	 * @return	If false, the database could not be expanded, DELETE IT AFTER A FAILURE!!!
	 * 			Typically this happens when the system is out of memory
	 */
	bool						expand(uint8_t count = 1){
		FUN();
	}

	/**
	 * @brief	Cleans the whole database, including every allocated object
	 */
	void						clean(){
		FUN();
	}

	/**
	 * @brief	Adds the supplied string to the database
	 * @param	str				The string to add
	 * @param	entry			The entry to register
	 * @return	size_t			The id of the name
	 */
	size_t						add(const std::string& str, uint64_t entry){
		FUN();
	}

	/**
	 * @brief	Changes the name of the database
	 * @param	title			The new title of the database
	 */
	void						setTitle(const std::string& title){
		FUN();
	}

	/**
	 * @brief	Returns the title of the database
	 */
	std::string					getTitle(){
		FUN();
	}

	/**
	 * @brief	Appends the contents of the supplied database to this
	 * @param	db				The db to append the contents of
	 */
	void						append(NamesDBT& db){
		FUN();
	}

	/**
	 * @brief	Gets the entry with the specified id of this database (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	void*			The entry previously supplied to add(), nullptr if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	uint64_t					getEntry(size_t id){
		FUN();
	}

	/**
	 * @brief	Searches for the database entry with the supplied id and returns a pointer to it
	 * @param	id				The id of the searched entry
	 * @return	entry_namesDB*	A pointer to the db entry
	 */
	entry_namesDB*				getDBEntry(size_t id){
		FUN();
	}

	/**
	 * @brief	Gets the name string of the specified id (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	std::string		The name previously supplied to add(), empty if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	std::string					getName(size_t id){
		FUN();
	}

	/**
	 * @brief	Gets the name string of the specified entry
	 * @param	entry			The entry to get the name from
	 * @return	std::string		The name previously supplied to add()
	 */
	static std::string			getEntryName(entry_namesDB* entry){
		FUN();
	}

	/**
	 * @brief	Searches for the first occurrence of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exactly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	namesDB_searchRes	The search result
	 */
	namesDB_searchRes			searchFirst(std::string name, bool exact, size_t startID = 0, size_t endID = SIZE_MAX){
		FUN();
	}

	/**
	 * @brief	Searches for the first occurence of the specified name
	 * @param	name			The name to search for
	 * @param	nameLen			The length of the name
	 * @param	exact			If the string has to match exactly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	namesDB_searchRes	The search result
	 */
	namesDB_searchRes			searchFirst(const char* name, size_t nameLen, bool exact, size_t startID = 0, size_t endID = SIZE_MAX);{
		FUN();
	}

	/**
	 * @brief	Searches all occurences of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exacltly or if it can be a substring
	 * @param	start_id		The id to start searching from
	 * @param	end_id			The id to stop searching at (inclusive)
	 * @return	A deque holding instances of namesDB_searchRes
	 */
	std::deque<namesDB_searchRes>	searchAll(std::string name, bool exact, size_t start_id = 0, size_t end_id = SIZE_MAX){
		FUN();
	}

	/**
	 * @brief	Returns the amount of entries stored in this database
	 */
	size_t						getEntriesCount(){
		FUN();
	}

	/**
	 * @brief	Returns the bytes used by this database
	 */
	size_t						getBytesUsed(){
		FUN();
	}

	/**
	 * @brief	Exports this databases contents to the supplied stream
	 * @param	outStream		The stream to export to
	 */
	void						exportDB(std::ostream& outStream){
		FUN();
	}

	/**
	 * @brief	Imports the contents of this database form the supplied stream
	 * @note	This clears the contents of this database
	 * @param	inStream		The stream to import from
	 */
	bool						importDB(std::istream& inStream){
		FUN();
	}

	/**
	 * @brief	Updates the internal index for fast access
	 * @note	This should be done before using id-based access after creating a new DB or updating it
	 */
	void						updateIndex(){
		FUN();
	}

#ifndef FRIEND_NAMES_DB
private:
#endif

	NamesDBT					_db;

};

#endif
