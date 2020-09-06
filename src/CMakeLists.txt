find_package(Threads REQUIRED)

if(LIBEXECSTREAM_SHARED)
    set(libtype SHARED)
else()
    set(libtype)
endif()

if(WIN32 OR CYGWIN OR MINGW OR MSYS)
    set(os_code
        win/exec-stream-helpers.cpp
        win/exec-stream-helpers.h
        win/exec-stream-impl.cpp
        win/exec-stream-impl.h)
elseif(APPLE OR UNIX)
    set(os_code
        posix/exec-stream-helpers.cpp
        posix/exec-stream-helpers.h
        posix/exec-stream-impl.cpp
        posix/exec-stream-impl.h)
endif()

add_library(execstream ${libtype}
    ../include/libexecstream/exec-stream.h
    exec-stream.cpp
    ${os_code})
target_include_directories(execstream PUBLIC ../include ./)
target_link_libraries(execstream PUBLIC ${CMAKE_THREAD_LIBS_INIT})

if(NOT MSVC)
    target_compile_options(execstream PRIVATE -fPIC)
endif()
