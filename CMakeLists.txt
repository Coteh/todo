# require Cmake 2.8+
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# initial setup
SET(APP_NAME todo)
project(${APP_NAME})

# build options
option(TODO_BUILD_CLIAPP "Build todo command line interface app." ON)
option(TODO_BUILD_TESTS "Build todo unit tests." ON)

# other options
set(RAPIDJSON_INCLUDE "~/Development_libs/rapidjson/include" CACHE FILEPATH "Include directory for rapidjson")
set(COMPILER_PARANOID_MODE "Compiler paranoid mode" ON)

# checking for C++11/C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(WARNING "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

# include directories
include_directories(shared/include)
include_directories(${RAPIDJSON_INCLUDE})

# add definitions
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# add other compiler flags
if(COMPILER_PARANOID_MODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()

# set build path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

# add targets
add_subdirectory(shared)
if(TODO_BUILD_CLIAPP)
add_subdirectory(cli-app)
endif()
if(TODO_BUILD_TESTS)
  add_subdirectory(test)
endif()
