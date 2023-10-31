set(COMPONENTS add subtract multiply baseConvert comparison)

file(GLOB UTILS *.cpp)
add_library(util ${UTILS})
target_include_directories(util PUBLIC ../include/)

foreach(COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
    target_include_directories(${COMPONENT} PUBLIC ../include/)
    target_link_libraries(${COMPONENT} util)
endforeach()
