# REPLXX for REPL operations
ADD_SUBDIRECTORY(replxx)

# Tree-sitter
SET(TREE_SITTER_RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/tree-sitter/lib" CACHE PATH "Tree-sitter runtime libraries")