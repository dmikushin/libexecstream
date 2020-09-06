add_executable(exec-stream-test exec-stream-test.cpp)
target_link_libraries(exec-stream-test PRIVATE execstream)
set_property(TARGET exec-stream-test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:exec-stream-test>")
