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

# Add include directory to all targets
FOREACH(TARGET IN LISTS TEST_TARGETS)
    TARGET_INCLUDE_DIRECTORIES(${TARGET} PUBLIC ${STP_BASE_DIRECTORY}/include/)
ENDFOREACH(TARGET)

IF (STP_BUILD_GUI EQUAL 1)
    FIND_PACKAGE(SDL2 REQUIRED)
    ADD_LIBRARY(imgui
                imgui/imgui.cpp
                imgui/imgui_draw.cpp
                imgui/imgui_widgets.cpp
                imgui/imgui_tables.cpp
                imgui/imgui_demo.cpp
                imgui/backends/imgui_impl_sdl2.cpp
                imgui/backends/imgui_impl_opengl3.cpp)

    # If we have freetype, we can use it to render text
    FIND_PACKAGE(Freetype QUIET)
    IF (FREETYPE_FOUND)
        MESSAGE(STATUS "Found Freetype")
        ADD_LIBRARY(imgui_freetype STATIC "${STP_BASE_DIRECTORY}/include/imgui/misc/freetype/imgui_freetype.cpp")
        TARGET_INCLUDE_DIRECTORIES(imgui_freetype PRIVATE "${STP_BASE_DIRECTORY}/include/imgui")
        TARGET_LINK_LIBRARIES(imgui_freetype PRIVATE ${FREETYPE_LIBRARIES})
        TARGET_LINK_LIBRARIES(imgui PRIVATE imgui_freetype)
        TARGET_INCLUDE_DIRECTORIES(imgui_freetype PRIVATE ${FREETYPE_INCLUDE_DIRS})
        TARGET_COMPILE_DEFINITIONS(imgui PRIVATE IMGUI_ENABLE_FREETYPE)
    ENDIF()

    IF (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        TARGET_LINK_LIBRARIES(imgui PRIVATE "-framework CoreFoundation")
    ENDIF()

    TARGET_LINK_LIBRARIES(imgui PRIVATE SDL2::SDL2)
    TARGET_INCLUDE_DIRECTORIES(imgui PRIVATE ${SDL2_INCLUDE_DIRS})
    TARGET_INCLUDE_DIRECTORIES(imgui PRIVATE "${STP_BASE_DIRECTORY}/include/imgui")
ENDIF()
