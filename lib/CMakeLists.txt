find_package(Python3 COMPONENTS Interpreter REQUIRED Development)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(bindings bindings.cpp ${G_CALCULATOR_FILES})
target_link_libraries(bindings PRIVATE steppable)
target_link_libraries(bindings PRIVATE calc)
target_link_libraries(bindings PRIVATE util)
target_include_directories(bindings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_compile_definitions(bindings PRIVATE NO_MAIN)

set_target_properties(bindings PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O3 -fPIC")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC")

if(APPLE)
    set_target_properties(bindings PROPERTIES LINK_FLAGS
                          "-undefined dynamic_lookup -F/Library/Frameworks -F/opt/homebrew/Frameworks \
                          -L/opt/homebrew/Frameworks/Python.framework/Versions/Current/lib            \
                          -L/Library/Frameworks/Python.framework/Versions/CurrentVersion/lib          \
                          -framework Python")
endif(APPLE)
