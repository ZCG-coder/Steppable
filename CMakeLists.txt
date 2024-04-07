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

cmake_minimum_required(VERSION 3.20)
project(Steppable)

# Ensure that Python is available to run the development scripts, and build with bindings.
find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STP_BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "The source directory of Steppable")

if (WIN32)
    add_compile_definitions(WINDOWS)
    if (MSVC) # MSVC Has no UTF-8 support by default
        add_compile_options(/utf-8)
    endif ()
    set(WINDOWS TRUE)
elseif (APPLE)
    add_compile_definitions(MACOSX)
elseif (LINUX)
    add_compile_definitions(LINUX)
else ()
    message(ERROR "Platform not defined")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(DEBUG TRUE)
endif ()

function(capitalize IN OUT)
    string(SUBSTRING ${IN} 0 1 FIRST_LETTER)
    string(SUBSTRING ${IN} 1 -1 THE_REST)
    string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
    string(CONCAT CAPITALIZED ${FIRST_LETTER} ${THE_REST})
    set(${OUT}
            ${CAPITALIZED}
            PARENT_SCOPE)
endfunction()
set(COMPONENTS abs add baseConvert subtract multiply decimalConvert comparison power division)
set(TARGETS ${COMPONENTS} util)
set(TEST_TARGETS_TEMP util fraction number expression ${COMPONENTS})

foreach (TEST_TARGET IN LISTS TEST_TARGETS_TEMP)
    set(TARGET_NAME "test")
    capitalize(${TEST_TARGET} FILE_NAME)
    string(CONCAT TARGET_NAME ${TARGET_NAME} ${FILE_NAME})
    list(APPEND TEST_TARGETS ${TARGET_NAME})
endforeach ()

add_subdirectory(src/)
add_subdirectory(tests/)
add_subdirectory(include/) # The CMakeLists file there adds the include/ directory to everything
add_subdirectory(lib/)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)


if (DEBUG)
    # Patch the compile_commands.json using the Python script
    add_custom_target(
            fix_ccjson ALL
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/patch_compile_commands.py
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Patching compile_commands.json"
    )

    add_custom_target(
            add_header_comments ALL
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/add_copyright_header.py
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Adding header comments"
    )
endif ()
