cmake_minimum_required(VERSION 3.1)

project(execstream)

find_package(Threads REQUIRED)

add_library(${PROJECT_NAME} SHARED src/${PROJECT_NAME}.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME}_test test/${PROJECT_NAME}_test.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})

