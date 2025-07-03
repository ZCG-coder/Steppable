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

IF(NOT ${STP_NO_BINDINGS}) # Only create the bindings if needed
    SET(Python_EXECUTABLE ${Python3_EXECUTABLE})

    # Detect the installed nanobind package and import it into CMake
    EXECUTE_PROCESS(
        COMMAND "${Python3_EXECUTABLE}" -m nanobind --cmake_dir
        OUTPUT_STRIP_TRAILING_WHITESPACE
        OUTPUT_VARIABLE NB_DIR
    )
    MESSAGE(TRACE "Found nanobind: ${NB_DIR}")
    LIST(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
    FIND_PACKAGE(nanobind CONFIG REQUIRED)

    # Python bindings for Steppable.
    SET(Python_INTERPRETER_ID
        ${Python3_INTERPRETER_ID}
        CACHE INTERNAL "Compatibility for nanobind"
    )
    NANOBIND_ADD_MODULE(steppyble STABLE_ABI NB_STATIC LTO bindings.cpp)

    IF(NOT ${WINDOWS})
        TARGET_LINK_OPTIONS(steppyble PRIVATE -Bsymbolic)
    ENDIF()
    SET_TARGET_PROPERTIES(steppyble PROPERTIES POSITION_INDEPENDENT_CODE ON)
    TARGET_LINK_LIBRARIES(steppyble PRIVATE func steppable)
    TARGET_COMPILE_DEFINITIONS(steppyble PRIVATE NO_MAIN STP_BINDINGS)
    TARGET_INCLUDE_DIRECTORIES(steppyble PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
ENDIF()
