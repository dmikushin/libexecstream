cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0054 NEW)

option(LIBEXECSTREAM_SHARED "Build shared library" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(libexecstream)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(-D_WIN32_WINNT=0x0601 /W4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

install(TARGETS execstream DESTINATION lib)
install(DIRECTORY include DESTINATION include)
