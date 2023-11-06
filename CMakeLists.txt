cmake_minimum_required(VERSION 3.14)
project(CAS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    add_compile_definitions(WINDOWS)
    if (MSVC) # MSVC Has no UTF-8 support by default
        add_compile_options(/utf-8)
    endif ()
    set(WINDOWS TRUE)
elseif (APPLE)
    add_compile_definitions(MACOSX)
elseif (LINUX)
    add_compile_definitions(LINUX)
else ()
    message(ERROR "Platform not defined")
endif ()

function(capitalize IN OUT)
    string(SUBSTRING ${IN} 0 1 FIRST_LETTER)
    string(SUBSTRING ${IN} 1 -1 THE_REST)
    string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
    string(CONCAT CAPITALIZED ${FIRST_LETTER} ${THE_REST})
    set(${OUT}
            ${CAPITALIZED}
            PARENT_SCOPE)
endfunction()
set(COMPONENTS add subtract multiply baseConvert comparison)
set(TARGETS ${COMPONENTS} util)
set(TEST_TARGETS_TEMP ${COMPONENTS})
foreach (TEST_TARGET IN LISTS TEST_TARGETS_TEMP)
    set(TARGET_NAME "test")
    capitalize(${TEST_TARGET} FILE_NAME)
    string(CONCAT TARGET_NAME ${TARGET_NAME} ${FILE_NAME})
    list(APPEND TEST_TARGETS ${TARGET_NAME})
endforeach ()

add_subdirectory(src/)
add_subdirectory(tests/)
add_subdirectory(include/) # The CMakeLists file there adds the include/ directory to everything

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
