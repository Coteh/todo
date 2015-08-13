# require Cmake 2.8+
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# initial setup
SET(CLI_APP todo_cli_app)

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
add_library(${CLI_APP}_lib STATIC include/TodoApp.h src/TodoApp.cpp include/FileIO.h src/FileIO.cpp
include/TodoPrinter.h src/TodoPrinter.cpp include/Helpers.h src/Helpers.cpp)
add_executable(${CLI_APP} src/main.cpp)
set_target_properties(${CLI_APP} PROPERTIES OUTPUT_NAME todo)
target_include_directories(${CLI_APP}_lib PUBLIC include)
target_include_directories(${CLI_APP} PUBLIC include)
target_link_libraries(${CLI_APP} ${CLI_APP}_lib)
target_link_libraries(${CLI_APP}_lib todo_shared)
