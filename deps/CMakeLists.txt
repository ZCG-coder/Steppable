INCLUDE(FetchContent)

# SQLite
FetchContent_Declare(
  SqliteTarball
  URL              https://sqlite.org/src/tarball/sqlite-20251128172825-281fc0e9af.tar.gz
  SOURCE_DIR       ${STP_BASE_DIRECTORY}/deps/sqlite
)
FetchContent_Populate(SqliteTarball)

# REPLXX for REPL operations
ADD_SUBDIRECTORY(replxx)

# Tree-sitter
SET(TREE_SITTER_RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/tree-sitter/lib" CACHE PATH "Tree-sitter runtime libraries")