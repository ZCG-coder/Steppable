enable_testing()

foreach (ITEM IN LISTS TEST_TARGETS)
    add_executable(${ITEM} ${ITEM}.cpp)
    target_link_libraries(${ITEM} calc)
    add_test(NAME ${ITEM} COMMAND ${CMAKE_BINARY_DIR}/tests/${ITEM})
    message(STATUS "Added test case: ${ITEM}: ${ITEM}.cpp")
endforeach ()
