cmake_minimum_required(VERSION 3.8)
project(CAS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    add_compile_definitions(WINDOWS)
elseif(APPLE)
    add_compile_definitions(MACOSX)
elseif(LINUX)
    add_compile_definitions(LINUX)
else()
    message(ERROR "Platform not defined")
endif()

add_subdirectory(src/)
