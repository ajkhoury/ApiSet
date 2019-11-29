cmake_minimum_required(VERSION 3.4)

#
# Define the ApiSet project
#
project(apiset C)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    # Force GCC and Clang to compile with proper unicode support for Windows.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -municode -fshort-wchar")
    message(STATUS "Using GCC compiler: ${CMAKE_C_COMPILER}")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    # Compile as static runtime binary.
    message(STATUS "Using MSVC compiler: ${CMAKE_C_COMPILER}")
    # https://gitlab.kitware.com/cmake/community/wikis/FAQ#dynamic-replace
    foreach(flag_var CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MD")
        if(${flag_var} MATCHES "/MDd")
            string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/MDd")
    endforeach(flag_var)
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
