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

set(Python_FIND_VIRTUALENV ONLY)
unset(Python_EXECUTABLE)
find_package(
    Python
    COMPONENTS Development Interpreter
    REQUIRED)

# Detect the installed nanobind package and import it into CMake
execute_process(
    COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE NB_DIR)
message(TRACE "Found nanobind: ${NB_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

# Python bindings for Steppable.
set(Python_INTERPRETER_ID ${Python3_INTERPRETER_ID} CACHE INTERNAL "Compatibility for nanobind")
nanobind_add_module(steppyble STABLE_ABI NB_STATIC LTO bindings.cpp)

if(NOT ${WINDOWS})
    target_link_options(steppyble PRIVATE -Bsymbolic)
endif()
set_target_properties(steppyble PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(steppyble PRIVATE calc steppable)
target_compile_definitions(steppyble PRIVATE NO_MAIN)
target_include_directories(steppyble PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
