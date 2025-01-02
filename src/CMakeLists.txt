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

ADD_LIBRARY(
    util STATIC
    argParse.cpp
    colors.cpp
    logging.cpp
    symbols.cpp
    testing.cpp
    util.cpp
    getString.cpp
    platform.cpp
    format.cpp
    constants.cpp
)
SET_TARGET_PROPERTIES(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

ADD_LIBRARY(steppable STATIC number.cpp fraction.cpp)
SET_TARGET_PROPERTIES(steppable PROPERTIES POSITION_INDEPENDENT_CODE ON)

SET(CALCULATOR_FILES)

FOREACH(COMPONENT IN LISTS COMPONENTS)
    STRING(REPLACE "::" ";" COMPONENT_PARTS ${COMPONENT})
    LIST(LENGTH COMPONENT_PARTS LEN)
    IF(NOT LEN EQUAL 2)
        MESSAGE(FATAL_ERROR "Incorrect format of target name.")
    ENDIF()
    LIST(GET COMPONENT_PARTS 0 ORIGIN)
    LIST(GET COMPONENT_PARTS 1 NAME)
    SET(TARGET_NAME ${ORIGIN}_${NAME})
    MESSAGE(TRACE "Adding component: ${NAME}: ${ORIGIN}/${NAME}/${NAME}.cpp, ${ORIGIN}/${NAME}/${NAME}Report.cpp")

    # No longer offering executables for each component automatically.
    IF(STP_BUILD_COMPONENT_EXECUTABLE)
        ADD_EXECUTABLE(${TARGET_NAME} ${ORIGIN}/${NAME}/${NAME}.cpp ${ORIGIN}/${NAME}/${NAME}Report.cpp)
        TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PRIVATE ${STP_BASE_DIRECTORY}/include/)
        TARGET_LINK_LIBRARIES(${TARGET_NAME} PRIVATE func)
    ENDIF()

    LIST(APPEND CALCULATOR_FILES ${ORIGIN}/${NAME}/${NAME}.cpp ${ORIGIN}/${NAME}/${NAME}Report.cpp)
ENDFOREACH()

# FUNC: Library containing all Steppable functions.
ADD_LIBRARY(func STATIC ${CALCULATOR_FILES} fraction.cpp rounding.cpp factors.cpp number.cpp)
SET_TARGET_PROPERTIES(func PROPERTIES POSITION_INDEPENDENT_CODE ON)

TARGET_INCLUDE_DIRECTORIES(steppable PRIVATE ${STP_BASE_DIRECTORY}/include/)
TARGET_INCLUDE_DIRECTORIES(func PRIVATE ${STP_BASE_DIRECTORY}/include/)
TARGET_INCLUDE_DIRECTORIES(util PRIVATE ${STP_BASE_DIRECTORY}/include/)

TARGET_LINK_LIBRARIES(steppable PRIVATE util)
TARGET_LINK_LIBRARIES(func PRIVATE steppable)
TARGET_COMPILE_DEFINITIONS(func PRIVATE NO_MAIN)
TARGET_COMPILE_DEFINITIONS(steppable PRIVATE NO_MAIN)
