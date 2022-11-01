#ifndef __DARRAY_H__
#define __DARRAY_H__

#include <cstddef>
#include <cstring>

#ifndef DARRAY_DEFAULT_CHUNK_SIZE
    #define DARRAY_DEFAULT_CHUNK_SIZE 32
#endif

template <typename T>
class DArray{

public:
    DArray(){

    }

    ~DArray(){
        if (_data != nullptr)
            delete _data;
    }

    /**
     * @brief   Adds the supplied entry to the array
     * @param   t           The entry to add
     */
    void add(T t){
        while(_blocks_used+1 >= _blocks_allocated)
            expand();

        //_data[_blocks_used] = t;
        std::memcpy(&_data[_blocks_used], &t, sizeof(T));
        _blocks_used++;
    }

    /**
     * @brief   Expands the array by the supplied amount of slots
     * @param   amount      The amount of slots to add (DARRAY_DEFAULT_CHUNK_SIZE)
     */
    void expand(size_t amount = DARRAY_DEFAULT_CHUNK_SIZE){
        size_t newAllocated = _blocks_allocated + amount;
        size_t bytesNeeded = newAllocated*sizeof(T);
        //T* newData = new T[newAllocated];
        T* newData = (T*)std::malloc(bytesNeeded);

        std::memcpy(newData, _data, _blocks_used*sizeof(T));
        //for (size_t i = 0; i < _blocks_used; i++)
        //   newData[i] = _data[i];

        delete _data;
        _data = newData;
        _blocks_allocated = newAllocated;
    }

    void clean(){
        delete _data;
        _blocks_used = 0;
        _blocks_allocated = 0;
    }

    void append(const DArray<T>& other){
        expand(other._blocks_used);
        for (size_t i = 0; i < other._blocks_used; i++){
            this->add(other._data[i]);
        }
    }

    size_t lastID(){
        return _blocks_used-1;
    }

    size_t size(){
        return _blocks_used;
    }

    /**
     * @brief   The amount of allocated slots
     */
    size_t              _blocks_allocated = 0;

    /**
     * @brief   The amount of used slots
     */
    size_t              _blocks_used = 0;

    /**
     * @brief   The core array
     */
    T*                  _data = nullptr;

};

#endif
