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

ADD_LIBRARY(util STATIC argParse.cpp colors.cpp logging.cpp symbols.cpp testing.cpp util.cpp getString.cpp platform.cpp)
SET_TARGET_PROPERTIES(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

ADD_LIBRARY(steppable STATIC number.cpp fraction.cpp)
SET_TARGET_PROPERTIES(steppable PROPERTIES POSITION_INDEPENDENT_CODE ON)

SET(CALCULATOR_FILES)

FUNCTION(COPY_TO_BIN TARGET_NAME)
    IF(DEFINED STP_BUILD_COMPONENT_EXECUTABLE)
        IF(WINDOWS)
            ADD_CUSTOM_COMMAND(
                TARGET ${TARGET_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                        ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME}.exe
            )
        ELSE()
            ADD_CUSTOM_COMMAND(
                TARGET ${TARGET_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                        ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME}
            )
        ENDIF()
    ENDIF()
ENDFUNCTION()

FOREACH(COMPONENT IN LISTS COMPONENTS)
    MESSAGE(TRACE "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    # No longer offering executables for each component automatically.
    IF(DEFINED STP_BUILD_COMPONENT_EXECUTABLE)
        ADD_EXECUTABLE(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
        TARGET_INCLUDE_DIRECTORIES(${COMPONENT} PRIVATE ${STP_BASE_DIRECTORY}/include/)
        TARGET_LINK_LIBRARIES(${COMPONENT} PRIVATE calc)
    ENDIF()

    LIST(APPEND CALCULATOR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT}/${COMPONENT}.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT}/${COMPONENT}Report.cpp
    )

    COPY_TO_BIN(${COMPONENT})
ENDFOREACH()

ADD_LIBRARY(calc STATIC ${CALCULATOR_FILES} fraction.cpp rounding.cpp factors.cpp number.cpp)
SET_TARGET_PROPERTIES(calc PROPERTIES POSITION_INDEPENDENT_CODE ON)

TARGET_INCLUDE_DIRECTORIES(steppable PRIVATE ${STP_BASE_DIRECTORY}/include/)
TARGET_INCLUDE_DIRECTORIES(calc PRIVATE ${STP_BASE_DIRECTORY}/include/)
TARGET_INCLUDE_DIRECTORIES(util PRIVATE ${STP_BASE_DIRECTORY}/include/)

TARGET_LINK_LIBRARIES(steppable PRIVATE util)
TARGET_LINK_LIBRARIES(calc PRIVATE steppable)
TARGET_COMPILE_DEFINITIONS(calc PRIVATE NO_MAIN)
TARGET_COMPILE_DEFINITIONS(steppable PRIVATE NO_MAIN)
