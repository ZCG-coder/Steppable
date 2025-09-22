FUNCTION(INSTALL_TO_BIN target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/bin
    )
ENDFUNCTION()