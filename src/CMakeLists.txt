file(GLOB UTILS *.cpp)
add_library(util ${UTILS})

set(CALCULATOR_FILES)

function(COPY_TO_BIN TARGET_NAME)
    if (WINDOWS)
        add_custom_command(TARGET ${TARGET_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME}.exe)
    else ()
        add_custom_command(TARGET ${TARGET_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}>
                ${CMAKE_CURRENT_BINARY_DIR}/../bin/${TARGET_NAME})
    endif ()
endfunction()

foreach (COMPONENT IN LISTS COMPONENTS)
    list(APPEND CALCULATOR_FILES ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
endforeach ()

add_library(calc ${CALCULATOR_FILES})
target_link_libraries(calc util)
target_include_directories(calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_compile_definitions(calc PRIVATE NO_MAIN)

foreach (COMPONENT IN LISTS COMPONENTS)
    message(STATUS "Adding component: ${COMPONENT}: ${COMPONENT}/${COMPONENT}.cpp, ${COMPONENT}/${COMPONENT}Report.cpp")

    add_executable(${COMPONENT} ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)
    target_link_libraries(${COMPONENT} util calc)

    list(APPEND CALCULATOR_FILES ${COMPONENT}/${COMPONENT}.cpp ${COMPONENT}/${COMPONENT}Report.cpp)

    COPY_TO_BIN(${COMPONENT})
endforeach ()

add_executable(main main/main.cpp)
target_link_libraries(main util calc)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
