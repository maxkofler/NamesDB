cmake_minimum_required(VERSION 3.5)
project(FileIndexTests)

include_directories(../Log/include)

add_definitions(-DDEBUG)

include_directories(
	../include
	./include
)

add_subdirectory(test_main)

add_subdirectory(tests/Sanity)

add_subdirectory(tests/NamesDB)
add_subdirectory(tests/NamesDB_Stress)
