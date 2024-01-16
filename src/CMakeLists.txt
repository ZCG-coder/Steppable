#####################################################################################################
#  Copyright (c) 2024 NWSOFT                                                                        #
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

file(GLOB UTILS *.cpp)
add_library(util ${UTILS})

set(CALCULATOR_FILES)

function(COPY_TO_BIN TARGET_NAME)
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
endfunction()

foreach (COMPONENT IN LISTS COMPONENTS)
    list(APPEND CALCULATOR_FILES ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
endforeach ()

add_library(calc ${CALCULATOR_FILES})
target_link_libraries(calc util)
target_include_directories(calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_compile_definitions(calc PRIVATE NO_MAIN)

foreach (COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
    target_link_libraries(${COMPONENT} calc)

    list(APPEND CALCULATOR_FILES ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)

    COPY_TO_BIN(${COMPONENT})
endforeach ()

add_executable(main main/main.cpp)
target_link_libraries(main calc)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
