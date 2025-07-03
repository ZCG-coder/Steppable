#####################################################################################################
#  Copyright (c) 2023-2025 NWSOFT                                                                   #
#                                                                                                   #
#  Permission is hereby granted, free of charge, to any person obtaining a copy                     #
#  of this software and associated documentation files (the "Software"), to deal                    #
#  in the Software without restriction, including without limitation the rights                     #
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                        #
#  copies of the Software, and to permit persons to whom the Software is                            #
#  furnished to do so, subject to the following conditions:                                         #
#                                                                                                   #
#  The above copyright notice and this permission notice shall be included in all                   #
#  copies or substantial portions of the Software.                                                  #
#                                                                                                   #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                       #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                         #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                      #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                           #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                    #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                    #
#  SOFTWARE.                                                                                        #
#####################################################################################################

ENABLE_TESTING()

FOREACH(TEST_TARGET IN LISTS TEST_TARGETS_TEMP)
    SET(TARGET_NAME "test")
    STRING(REPLACE "::" ";" TEST_TARGET_PARTS ${TEST_TARGET})
    LIST(GET TEST_TARGET_PARTS 0 DIR_NAME)
    LIST(GET TEST_TARGET_PARTS 1 FILE_NAME)
    STRING(REPLACE "::" "_" TEST_TARGET ${TEST_TARGET})

    CAPITALIZE(${DIR_NAME} DIR_NAME)
    CAPITALIZE(${FILE_NAME} FILE_NAME)
    CAPITALIZE(${TEST_TARGET} TEST_TARGET)
    STRING(CONCAT DIR_NAME "test" ${DIR_NAME})
    STRING(CONCAT FILE_NAME "test" ${FILE_NAME})
    STRING(CONCAT TEST_TARGET "test" ${TEST_TARGET})

    ADD_EXECUTABLE(${TEST_TARGET} ${DIR_NAME}/${FILE_NAME}.cpp)
    TARGET_LINK_LIBRARIES(${TEST_TARGET} PRIVATE func)
    ADD_TEST(NAME ${TEST_TARGET} COMMAND ${CMAKE_BINARY_DIR}/tests/${TEST_TARGET})

    LIST(APPEND TEST_TARGETS ${TEST_TARGET})
    MESSAGE(TRACE "Added test case: ${TEST_TARGET}: ${DIR_NAME}/${FILE_NAME}.cpp")
ENDFOREACH()

SET(TEST_TARGETS ${TEST_TARGETS} PARENT_SCOPE)

ADD_CUSTOM_TARGET(tests)
ADD_DEPENDENCIES(tests ${TEST_TARGETS})
