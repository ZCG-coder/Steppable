# Add include directory to all targets
foreach (TARGET IN LISTS TARGETS TEST_TARGETS)
    target_include_directories(${TARGET} PUBLIC ./)
endforeach (TARGET)
