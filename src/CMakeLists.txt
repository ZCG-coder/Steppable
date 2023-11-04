file(GLOB UTILS *.cpp)
add_library(util ${UTILS})

foreach (COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
    target_link_libraries(${COMPONENT} util)
endforeach ()

add_executable(main main/main.cpp)
add_dependencies(main util)
target_link_libraries(main util)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)