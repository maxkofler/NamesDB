cmake_minimum_required(VERSION 3.5)

project(NamesDB)

option(NAMESDB_TESTS "Build NamesDB tests" OFF)
option(NAMESDB_OWNLOG "Use an own Log module (requires the Log submodule)" OFF)

set(OUTPUT "namesdb")

include_directories(include)

if (NAMESDB_TESTS)
	set(LOG_MAXLEVEL 20 CACHE STRING "Set the maximum log level")
	message("[NamesDB INFO] Using own Log library for testing!")
	include_directories(Log/include)
	add_subdirectory(Log)
endif()

if (NAMESDB_OWNLOG)
	message("[NamesDB INFO] Using own Log library!")
	include_directories(Log/include)
	add_subdirectory(Log)
endif()

file(GLOB_RECURSE CXX_SOURCES "src/**.cpp")
file(GLOB_RECURSE HEADERS "include/**.h")

add_library(${OUTPUT} STATIC ${HEADERS} ${CXX_SOURCES})
add_dependencies(${OUTPUT} log)
target_compile_features(${OUTPUT} PRIVATE cxx_std_17)
target_link_libraries(${OUTPUT} log)

if (NAMESDB_TESTS)
	enable_testing()
	message("[NamesDB INFO] Building NamesDB tests...")
	add_subdirectory(googletest)
	add_subdirectory(tests)
	target_compile_definitions(${OUTPUT} PRIVATE DEBUG)
endif()
