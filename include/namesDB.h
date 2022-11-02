#ifndef __NAMESDB_H__
#define __NAMESDB_H__

#define FRIEND_NAMES_DB_T
#include "namesDBt.h"

#include <vector>

template<typename T>
struct namesDB_searchRes{
	int8_t						code = 0;
	uint8_t						matchStart = 0;		//The place the match starts in the results name
	uint8_t						matchRemaining = 0;	//The remaining characters that did not match of the name (is name.length - search.length)
	T*							data;
	size_t						id;
};

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
		
	}
	~NamesDB(){
		
	}

	/**
	 * @brief	Creates a new database from an existing one
	 * @param	other			The database to copy
	 */
	NamesDB(const NamesDB<T>& other)
		: _db(other._db){
		
	}
	
	/**
	 * @brief	Expands the internal database by the supplied amount of blocks
	 * @param	count			The amount of blocks to expand by
	 * @return	If false, the database could not be expanded, DELETE IT AFTER A FAILURE!!!
	 * 			Typically this happens when the system is out of memory
	 */
	bool						expand(uint8_t count = 1){
		
		return _db.expand(count);
	}

	/**
	 * @brief	Cleans the whole database, including every allocated object
	 */
	void						clean(){
		
		_db.clean();
	}

	/**
	 * @brief	Adds the supplied string to the database
	 * @param	str				The string to add
	 * @param	entry			The entry to register
	 * @return	size_t			The id of the name
	 */
	size_t						add(const std::string& str, const T& entry){
		_entries.push_back(entry);
		return _db.add(str, (uint64_t) _entries.size()-1);
	}

	/**
	 * @brief	Adds the supplied string to the database
	 * @param	str				The string to add
	 * @param	entry			The entry to register
	 * @return	size_t			The id of the name
	 */
	size_t						add(const std::string& str, T&& entry){
		
		_entries.push_back(entry);
		return _db.add(str, (uint64_t) _entries.size()-1);
	}

	/**
	 * @brief	Changes the name of the database
	 * @param	title			The new title of the database
	 */
	void						setTitle(const std::string& title){
		
		_db.setTitle(title);
	}

	/**
	 * @brief	Returns the title of the database
	 */
	std::string					getTitle(){
		
		return _db.getTitle();
	}

	/**
	 * @brief	Appends the contents of the supplied database to this
	 * @param	db				The db to append the contents of
	 */
	void						append(NamesDB<T>& db){
		
		_db.append(db._db);
		_entries.insert(_entries.end(), db._entries.begin(), db._entries.end());
	}

	/**
	 * @brief	Gets the entry with the specified id of this database (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	T*				The entry previously supplied to add(), nullptr if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	T*							getEntry(size_t id){
		
		if (id > _entries.size()-1){
			LOGUE("[NamesDB][getEntry] Index " + std::to_string(id) + " is out of bounds!");
			return nullptr;
		}
		return &_entries[id];
	}

	/**
	 * @brief	Searches for the database entry with the supplied id and returns a pointer to it
	 * @param	id				The id of the searched entry
	 * @return	entry_namesDB*	A pointer to the db entry
	 */
	/*entry_namesDB*				getDBEntry(size_t id){
		
		return nullptr;
		#warning removed
	}*/

	/**
	 * @brief	Gets the name string of the specified id (is really slow, read note)
	 * @param	id				The id to search (received from add())
	 * @return	std::string		The name previously supplied to add(), empty if out of range
	 * @note	This function is slow, it iterates over every entry, don't use it if not necessary
	 */
	std::string					getName(size_t id){
		
		return _db.getName(id);
	}

	/**
	 * @brief	Searches for the first occurrence of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exactly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	namesDB_searchRes	The search result
	 */
	namesDB_searchRes<T>		searchFirst(std::string name, bool exact, size_t startID = 0, size_t endID = SIZE_MAX){
		
		auto resT = _db.searchFirst(name, exact, startID, endID);
		return toSearchRes(resT);
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
	namesDB_searchRes<T>			searchFirst(const char* name, size_t nameLen, bool exact, size_t startID = 0, size_t endID = SIZE_MAX){
		
		auto resT = _db.searchFirst(name, exact, startID, endID);
		return toSearchRes(resT);
	}

	/**
	 * @brief	Searches all occurences of the specified name
	 * @param	name			The name to search for
	 * @param	exact			If the string has to match exacltly or if it can be a substring
	 * @param	startID			The id to start searching from
	 * @param	endID			The id to stop searching at (inclusive)
	 * @return	A deque holding instances of namesDB_searchRes
	 */
	std::deque<namesDB_searchRes<T>> searchAll(std::string name, bool exact, size_t startID = 0, size_t endID = SIZE_MAX){
		
		auto resT = _db.searchAll(name, exact, startID, endID);
		std::deque<namesDB_searchRes<T>> res;
		for (auto entry : resT)
			res.push_back(toSearchRes(entry));
		return res;
	}

	/**
	 * @brief	Returns the amount of entries stored in this database
	 */
	size_t						getEntriesCount(){
		
		return _db.getEntriesCount();
	}

	/**
	 * @brief	Returns the bytes used by this database
	 */
	size_t						getBytesUsed(){
		
		return _db.getBytesUsed();
	}

	/**
	 * @brief	Exports this databases contents to the supplied stream
	 * @param	outStream		The stream to export to
	 */
	void						exportDB(std::ostream& outStream){
		
		_db.exportDB(outStream);
		size_t bytesUsed = _entries.size()*sizeof(T);
		outStream.write((char*)_entries.data(), bytesUsed);
	}

	/**
	 * @brief	Imports the contents of this database form the supplied stream
	 * @note	This clears the contents of this database
	 * @param	inStream		The stream to import from
	 */
	bool						importDB(std::istream& instream){
		
		_entries.clear();

		bool ok = _db.importDB(instream);
		if (!ok)
			return ok;

		size_t bytesNeeded = _db._count_entries*sizeof(T);

		T* temp = new T[_db._count_entries];

		instream.read((char*)temp, bytesNeeded);
		if (!instream){
			LOGE(	"[NamesDB][importDB] Failed to import stream contents to \"" + 
					_db._title + "\": EOF in data segment, read bytes: " + std::to_string(instream.gcount()));
			clean();
			return false;
		}

		for (size_t i = 0; i < _db._count_entries; i++)
			_entries.push_back(temp[i]);
		
		delete[] temp;
		return true;
	}

	/**
	 * @brief	Updates the internal index for fast access
	 * @note	This should be done before using id-based access after creating a new DB or updating it
	 */
	void						updateIndex(){
		
		_db.updateIndex();
	}

#ifndef FRIEND_NAMES_DB
private:
#endif

	NamesDBT					_db;

	std::vector<T>				_entries;

	namesDB_searchRes<T>		toSearchRes(const namesDBt_searchRes& resT){
		namesDB_searchRes<T> res {
			resT.code,
			resT.matchStart,
			resT.matchRemaining,
			resT.code == 0 ? &_entries[resT.data] : nullptr,
			resT.id
		};
		return res;
		/*res.code = resT.code;
		res.matchStart = resT.matchStart;
		res.matchRemaining = resT.matchRemaining;
		res.data = _entries._data[resT.data];
		res.id = resT.id;
		return res;*/
	}

};

#endif
