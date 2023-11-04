file(GLOB UTILS *.cpp)
add_library(util ${UTILS})

foreach (COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
    target_link_libraries(${COMPONENT} util)
endforeach ()
