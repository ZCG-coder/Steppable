include(FetchContent)

# Get SDL and imgui
SET(CMAKE_C_STANDARD 11)
FetchContent_Declare(
    sdl3
    URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.18/SDL3-3.2.18.tar.gz
)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(sdl3)

FetchContent_Populate(imgui
  URL https://github.com/ocornut/imgui/archive/docking.zip
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
)
add_library(imgui_sdlopengl STATIC
  include/imgui/imgui.cpp
  include/imgui/imgui_draw.cpp
  include/imgui/imgui_demo.cpp
  include/imgui/imgui_tables.cpp
  include/imgui/imgui_widgets.cpp
  include/imgui/backends/imgui_impl_sdl3.cpp
  include/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui_sdlopengl
PUBLIC
  include/imgui
  include/imgui/backends
  ${sdl3_SOURCE_DIR}/include
)
target_link_libraries(imgui_sdlopengl
  PUBLIC
  SDL3::SDL3)

# Build compression tool
add_executable(_stp_btcc include/imgui/misc/fonts/binary_to_compressed_c.cpp)

target_compile_options(imgui_sdlopengl PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/w>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-w>
)
target_compile_options(_stp_btcc PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/w>
  $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-w>
)

# Build main executable
add_executable(steppable_main main.cpp guiUtils.cpp)
target_link_libraries(steppable_main PRIVATE
  imgui_sdlopengl
  steppable
  ${SDL3_LIBRARIES}
  ${OPENGL_gl_LIBRARY})
target_include_directories(steppable_main PRIVATE ${STP_BASE_DIRECTORY}/include)
