set (Python_FIND_VIRTUALENV FIRST)
unset (Python_EXECUTABLE)
find_package (Python COMPONENTS Interpreter Development REQUIRED)

# # Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
message(STATUS "Found nanobind: ${Python_EXECUTABLE}")
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(bindings NB_STATIC LTO bindings.cpp)
target_link_options(bindings PRIVATE -Bsymbolic)
set_target_properties(bindings PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(bindings PRIVATE calc steppable)
target_compile_definitions(bindings PRIVATE NO_MAIN)
target_include_directories(bindings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
