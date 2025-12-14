#####################################################################################################
#  Copyright (c) 2023-2025 NWSOFT                                                                   #
#                                                                                                   #
#  Permission is hereby granted, free of charge, to any person obtaining a copy                     #
#  of this software and associated documentation files (the "Software"), to deal                    #
#  in the Software without restriction, including without limitation the rights                     #
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                        #
#  copies of the Software, and to permit persons to whom the Software is                            #
#  furnished to do so, subject to the following conditions:                                         #
#                                                                                                   #
#  The above copyright notice and this permission notice shall be included in all                   #
#  copies or substantial portions of the Software.                                                  #
#                                                                                                   #
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                       #
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                         #
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                      #
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                           #
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                    #
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                    #
#  SOFTWARE.                                                                                        #
#####################################################################################################

OPTION(BUILD_SHARED_LIBS "Build using shared libraries" ON)
OPTION(TREE_SITTER_REUSE_ALLOCATOR "Reuse the library allocator" OFF)

SET(TREE_SITTER_ABI_VERSION
    15
    CACHE STRING "Tree-sitter ABI version"
)
IF(NOT ${TREE_SITTER_ABI_VERSION} MATCHES "^[0-9]+$")
    UNSET(TREE_SITTER_ABI_VERSION CACHE)
    MESSAGE(FATAL_ERROR "TREE_SITTER_ABI_VERSION must be an integer")
ENDIF()

INCLUDE(GNUInstallDirs)

ADD_LIBRARY(tree-sitter-stp src/parser.c)
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/scanner.c)
    TARGET_SOURCES(tree-sitter-stp PRIVATE src/scanner.c)
ENDIF()

TARGET_INCLUDE_DIRECTORIES(
    tree-sitter-stp
    PRIVATE src
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/bindings/c>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

TARGET_COMPILE_DEFINITIONS(
    tree-sitter-stp PRIVATE $<$<BOOL:${TREE_SITTER_REUSE_ALLOCATOR}>:TREE_SITTER_REUSE_ALLOCATOR>
                            $<$<CONFIG:Debug>:TREE_SITTER_DEBUG>
)

SET_TARGET_PROPERTIES(
    tree-sitter-stp
    PROPERTIES C_STANDARD 11
               POSITION_INDEPENDENT_CODE ON
               SOVERSION "${TREE_SITTER_ABI_VERSION}.${PROJECT_VERSION_MAJOR}"
               DEFINE_SYMBOL ""
)

CONFIGURE_FILE(bindings/c/tree-sitter-stp.pc.in "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter-stp.pc" @ONLY)

INSTALL(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bindings/c/tree_sitter"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING
    PATTERN "*.h"
)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/tree-sitter-stp.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
INSTALL(TARGETS tree-sitter-stp LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

FILE(GLOB QUERIES queries/*.scm)
INSTALL(FILES ${QUERIES} DESTINATION "${CMAKE_INSTALL_DATADIR}/tree-sitter/queries/stp")

INCLUDE(buildMain.cmake)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
