
if(LIBEXECSTREAM_SHARED)
    set(libtype SHARED)
else()
    set(libtype)
endif()

find_package(Threads REQUIRED)

add_library(execstream exec-stream.cpp ${libtype})
target_include_directories(execstream PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(execstream PUBLIC ${CMAKE_THREAD_LIBS_INIT})

if(NOT MSVC)
    target_compile_options(execstream PRIVATE -fPIC)
endif()
