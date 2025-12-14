INCLUDE(${STP_BASE_DIRECTORY}/cmake/install_to_bin.cmake)

SET(TREE_SITTER_LANG "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE PATH "Tree-sitter generated source")
SET(TREE_SITTER_SRC ${TREE_SITTER_RUNTIME}/src/lib.c ${TREE_SITTER_LANG}/parser.c CACHE FILEPATH "Tree-sitter source code")

SET(PROJECT_SRC_COMMON
    src/stpInit.cpp
    src/stpStore.cpp
    src/stpParseUtils.cpp
    src/stpApplyOperator.cpp
    src/stpErrors.cpp
    src/stpExprHandler.cpp
    src/stpInteractive.cpp
    src/stpInterrupt.cpp
    # Statement processors
    src/statementProcessors/stpAssignment.cpp
    src/statementProcessors/stpChunkProcessor.cpp
    src/statementProcessors/stpFunctionDeclStmt.cpp
    src/statementProcessors/stpIfElseStmt.cpp
    src/statementProcessors/stpSymbolDecl.cpp
    src/statementProcessors/stpWhileStmt.cpp
    # Expression processors
    src/exprProcessors/stpStringExpr.cpp
    src/exprProcessors/stpMatrixExpr.cpp
    src/exprProcessors/stpFnCallExpr.cpp
    src/exprProcessors/stpRangeExpr.cpp
    src/exprProcessors/stpSuffixExpr.cpp
)
SET(PROJECT_SRC src/main.cpp ${PROJECT_SRC_COMMON})

IF(NOT DEFINED STP_BASE_DIRECTORY)
    MESSAGE(FATAL_ERROR "This project is not supposed to be build standalone without Steppable.")
ENDIF()

ADD_EXECUTABLE(stp_parse ${PROJECT_SRC} ${TREE_SITTER_SRC})

TARGET_INCLUDE_DIRECTORIES(stp_parse PUBLIC ${TREE_SITTER_RUNTIME}/include ${TREE_SITTER_RUNTIME}/src/ ${TREE_SITTER_LANG} ${STP_BASE_DIRECTORY}/include)
TARGET_LINK_LIBRARIES(stp_parse PRIVATE steppable)

TARGET_LINK_LIBRARIES(stp_parse PRIVATE replxx)
TARGET_INCLUDE_DIRECTORIES(stp_parse PUBLIC replxx/include)

INSTALL_TO_BIN(stp_parse)
ADD_CUSTOM_COMMAND(TARGET stp_parse POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/queries ${CMAKE_BINARY_DIR}/bin/queries
)
