cmake_minimum_required(VERSION 3.14)
#set(CMAKE_VERBOSE_MAKEFILE ON)
project(cppfuncomp LANGUAGES CXX)

set(EXTERN_DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#include(MunkeiVersionFromGit)
#include(msvc_cplusplus)
include(catch2)
#include(CTestConfig)
include(CTest)
include(warnings)
#include(checkedcmd)
#include(CppSkilledType)
#include(CppResultType)

enable_testing()

include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Tests)
set(SOURCE_FILES main.cpp )
add_executable(cppfuncomp ${SOURCE_FILES})
