project(libexecstream)
cmake_minimum_required(VERSION 2.8)

option(LIBEXECSTREAM_SHARED "Build shared library" OFF)

if(LIBEXECSTREAM_SHARED)
    set(libtype SHARED)
else()
    set(libtype)
endif()

find_package(Threads REQUIRED)

add_library(execstream ${libtype} src/exec-stream.cpp)
target_include_directories(execstream PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(execstream PUBLIC ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET execstream PROPERTY POSITION_INDEPENDENT_CODE ON)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
