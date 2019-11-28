cmake_minimum_required(VERSION 3.4)

#
# Define the ApiSet project
#
project(apiset C)

# Force GCC to compile with proper unicode support for Windows.
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -municode -fshort-wchar")
    message(STATUS "Using GCC compiler: ${CMAKE_C_COMPILER}")
endif()

set(APISET_SOURCES
        string.c
        nls.c
        apiset.c
        resolve.c
        main.c
        unicode.c)
add_executable(apiset ${APISET_SOURCES})
target_link_libraries(apiset ntdll)

