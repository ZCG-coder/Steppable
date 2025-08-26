INCLUDE(FetchContent)

IF(STP_HAS_GUI)
    # JSON 11
    ADD_LIBRARY(json11 include/json11/json11.cpp)

    # Get SDL and imgui
    SET(CMAKE_C_STANDARD 11)
    FETCHCONTENT_DECLARE(sdl3 URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.18/SDL3-3.2.18.tar.gz)
    SET(SDL_TEST_LIBRARY
        OFF
        CACHE BOOL "" FORCE
    )
    FETCHCONTENT_MAKEAVAILABLE(sdl3)

    FETCHCONTENT_POPULATE(
        imgui
        URL https://github.com/ocornut/imgui/archive/docking.zip
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
    )
    ADD_LIBRARY(
        imgui_sdlopengl STATIC
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/backends/imgui_impl_sdl3.cpp
        include/imgui/backends/imgui_impl_sdlrenderer3.cpp
    )
    TARGET_INCLUDE_DIRECTORIES(imgui_sdlopengl PUBLIC include/imgui include/imgui/backends ${sdl3_SOURCE_DIR}/include)
    TARGET_LINK_LIBRARIES(imgui_sdlopengl PUBLIC SDL3::SDL3)

    # Build compression tool
    ADD_EXECUTABLE(_stp_btcc include/imgui/misc/fonts/binary_to_compressed_c.cpp)

    TARGET_COMPILE_OPTIONS(
        imgui_sdlopengl PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/w>
                                $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-w>
    )
    TARGET_COMPILE_OPTIONS(
        _stp_btcc PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/w> $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-w>
    )

    ADD_LIBRARY(
        imNodeEditor include/imNodeEditor/crude_json.cpp include/imNodeEditor/imgui_canvas.cpp
                     include/imNodeEditor/imgui_node_editor.cpp include/imNodeEditor/imgui_node_editor_api.cpp
    )
    TARGET_INCLUDE_DIRECTORIES(imNodeEditor PRIVATE ${STP_BASE_DIRECTORY}/gui/include/imNodeEditor)
    TARGET_COMPILE_DEFINITIONS(imNodeEditor PUBLIC IMGUI_DEFINE_MATH_OPERATORS)
    TARGET_LINK_LIBRARIES(imNodeEditor PUBLIC imgui_sdlopengl)

    # Build main executable
    ADD_EXECUTABLE(steppable_main main.cpp guiUtils.cpp appState.cpp)
    TARGET_LINK_LIBRARIES(steppable_main PRIVATE steppable imNodeEditor ${SDL3_LIBRARIES} ${OPENGL_gl_LIBRARY})
    TARGET_INCLUDE_DIRECTORIES(
        steppable_main
        PRIVATE ${STP_BASE_DIRECTORY}/include ${STP_BASE_DIRECTORY}/gui ${STP_BASE_DIRECTORY}/gui/include
                ${STP_BASE_DIRECTORY}/gui/include/json11 ${STP_BASE_DIRECTORY}/gui/include/imNodeEditor
    )
    TARGET_INCLUDE_DIRECTORIES(steppable_main PUBLIC include/imnodes)
ENDIF()
