# require Cmake 2.8+
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# initial setup
SET(SHARED_LIB todo_shared)

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

# add definitions
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# add targets
add_library(${SHARED_LIB} STATIC include/DataTypes.h
include/TodoConfig.h src/TodoConfig.cpp)
