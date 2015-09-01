# require Cmake 2.8+
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# initial setup
SET(UNIT_TESTS
    base_tester
    shared_test
    cli_app_test)

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
set(base_tester_exists FALSE)
foreach (unit_test ${UNIT_TESTS})
  set(unit_test_files "")
  set(is_unit_test_lib FALSE)

  if (${unit_test} STREQUAL "base_tester")
    set(unit_test_files ${unit_test}/include/BaseTest.h ${unit_test}/src/BaseTest.cpp)
    set(is_unit_test_lib TRUE)
    set(base_tester_exists TRUE)
  elseif (${unit_test} STREQUAL "shared_test")
    set(unit_test_files ${unit_test}/include/TodoSharedTest.h ${unit_test}/src/TodoSharedTest.cpp ${unit_test}/src/main.cpp)
  elseif (${unit_test} STREQUAL "cli_app_test")
    set(unit_test_files ${unit_test}/include/TodoCLITest.h ${unit_test}/src/TodoCLITest.cpp ${unit_test}/include/TodoCLITestWrapper.h ${unit_test}/src/TodoCLITestWrapper.cpp ${unit_test}/src/main.cpp)
  endif()

  if (is_unit_test_lib)
    add_library(${unit_test} ${unit_test_files})
  else()
    add_executable(${unit_test} ${unit_test_files})
  endif()

  target_include_directories(${unit_test} PUBLIC ${unit_test}/include)
  target_link_libraries(${unit_test} todo_shared)
  if (${unit_test} STREQUAL "cli_app_test")
    if(TODO_BUILD_CLIAPP)
      target_include_directories(${unit_test} PUBLIC ${todo_cli_app_SOURCE_DIR}/include)
      target_link_libraries(${unit_test} todo_cli_app_lib)
    endif()
  endif()
  if (${base_tester_exists} AND NOT ${unit_test} STREQUAL "base_tester")
    target_include_directories(${unit_test} PUBLIC base_tester/include)
    target_link_libraries(${unit_test} base_tester)
  endif()
endforeach()
