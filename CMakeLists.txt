#####################################################################################################
#  Copyright (c) 2023-2024 NWSOFT                                                                   #
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

CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(Steppable)

# Ensure that Python is available to run the development scripts, and build with bindings.
set(Python_FIND_VIRTUALENV FIRST)

find_package(
Python
COMPONENTS Development Interpreter
REQUIRED)

find_package(
Python3
COMPONENTS Development Interpreter
REQUIRED)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_C_STANDARD 20)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(STP_BASE_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE STRING "The source directory of Steppable"
)

EXECUTE_PROCESS(
    COMMAND uname -o
    COMMAND tr -d '\n'
    OUTPUT_VARIABLE OPERATING_SYSTEM
)
IF(${OPERATING_SYSTEM} MATCHES "Android")
    SET(ANDROID 1)
    MESSAGE(STATUS "Building for Android.")
    SET(LINUX CACHE INTERNAL "Is Linux or Android" 1)
ENDIF()

IF(WIN32)
    ADD_COMPILE_DEFINITIONS(WINDOWS NOMINMAX) # Do not add min() and max() macros.
    IF(MSVC) # MSVC Has no UTF-8 support by default
        ADD_COMPILE_OPTIONS(/utf-8)
    ENDIF()
    SET(WINDOWS TRUE)
ELSEIF(APPLE)
    ADD_COMPILE_DEFINITIONS(MACOSX)
ELSEIF(LINUX)
    ADD_COMPILE_DEFINITIONS(LINUX)
ELSE()
    MESSAGE(ERROR "Platform not defined")
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_COMPILE_DEFINITIONS(DEBUG)
    SET(DEBUG TRUE)
ENDIF()

FUNCTION(capitalize IN OUT)
    STRING(SUBSTRING ${IN} 0 1 FIRST_LETTER)
    STRING(SUBSTRING ${IN} 1 -1 THE_REST)
    STRING(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
    STRING(CONCAT CAPITALIZED ${FIRST_LETTER} ${THE_REST})
    SET(${OUT}
        ${CAPITALIZED}
        PARENT_SCOPE
    )
ENDFUNCTION()

SET(COMPONENTS
    abs
    add
    baseConvert
    subtract
    multiply
    decimalConvert
    comparison
    power
    division
    root
    factorial
 trig hyp log)
# NEW_COMPONENT: PATCH Do NOT remove the previous comment.

SET(TARGETS ${COMPONENTS} util)
SET(TEST_TARGETS_TEMP util fraction number factors format ${COMPONENTS})

FOREACH(TEST_TARGET IN LISTS TEST_TARGETS_TEMP)
    SET(TARGET_NAME "test")
    CAPITALIZE(${TEST_TARGET} FILE_NAME)
    STRING(CONCAT TARGET_NAME ${TARGET_NAME} ${FILE_NAME})
    LIST(APPEND TEST_TARGETS ${TARGET_NAME})
ENDFOREACH()

ADD_SUBDIRECTORY(src/)
ADD_SUBDIRECTORY(lib/)
ADD_SUBDIRECTORY(tests/)
ADD_SUBDIRECTORY(include/) # The CMakeLists file there adds the include/ directory to everything

FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

IF(DEBUG)
    # Patch the compile_commands.json using the Python script
    ADD_CUSTOM_TARGET(
        fix_ccjson ALL
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/patch_compile_commands.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Patching compile_commands.json"
    )

    ADD_CUSTOM_TARGET(
        add_header_comments ALL
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/add_copyright_header.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Adding header comments"
    )
ENDIF()
