#set(EXTERN_CATCH_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/catch)
#include(catch2)

#set(EXTERN_DOCTEST_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/doctest)
#include(doctest)
set(SOURCE_FILES TestMain.cpp funcompTest.cpp)
add_executable(tests ${SOURCE_FILES})
add_test(
        NAME tests
        COMMAND tests
)
