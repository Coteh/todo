# require Cmake 2.8+
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# initial setup
SET(appName todo)
project(${appName})

# build options
option(TODO_BUILD_CLIAPP "Build todo command line interface app." ON)
option(TODO_BUILD_TESTS "Build todo unit tests." ON)

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
include_directories(${todo_SOURCE_DIR}/include)
set(RAPIDJSON_INCLUDE "~/Development_libs/rapidjson/include" CACHE FILEPATH "Include directory for rapidjson")
include_directories(${RAPIDJSON_INCLUDE})

# add definitions
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# add targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
add_library(${appName}_lib STATIC include/DataTypes.h 
include/TodoConfig.h src/TodoConfig.cpp)

if(TODO_BUILD_CLIAPP)
add_subdirectory(cli-app)
endif()
if(TODO_BUILD_TESTS)
  add_subdirectory(test)
endif()
