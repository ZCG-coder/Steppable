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

add_library(util STATIC argParse.cpp colors.cpp logging.cpp rounding.cpp symbols.cpp testing.cpp util.cpp)
set_target_properties(util PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(steppable STATIC number.cpp fraction.cpp expression.cpp)
set_target_properties(steppable PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(CALCULATOR_FILES)

function(COPY_TO_BIN TARGET_NAME)
    if (DEFINED STP_BUILD_COMPONENT_EXECUTABLE)
        if (WINDOWS)
            add_custom_command(TARGET ${TARGET_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                    ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME}.exe)
        else ()
            add_custom_command(TARGET ${TARGET_NAME}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                    ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME})
        endif ()
    endif ()
endfunction()

foreach (COMPONENT IN LISTS COMPONENTS)
    message(TRACE "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    # No longer offering executables for each component automatically.

    if (DEFINED STP_BUILD_COMPONENT_EXECUTABLE)
        add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
        target_link_libraries(${COMPONENT} calc)
    endif ()

    list(APPEND CALCULATOR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT}/${COMPONENT}.cpp
                                 ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT}/${COMPONENT}Report.cpp)

    COPY_TO_BIN(${COMPONENT})
endforeach ()

add_library(calc STATIC ${CALCULATOR_FILES} fraction.cpp number.cpp expression.cpp)
set_target_properties(calc PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(steppable PRIVATE ${STP_BASE_DIRECTORY}/include/)
target_include_directories(calc PRIVATE ${STP_BASE_DIRECTORY}/include/)
target_include_directories(util PRIVATE ${STP_BASE_DIRECTORY}/include/)

target_link_libraries(steppable util)
target_link_libraries(calc steppable)
target_compile_definitions(calc PRIVATE NO_MAIN)
