INCLUDE(FetchContent)

# SQLite
FetchContent_Declare(sqlite3
	GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
	GIT_BRANCH     master
)
FetchContent_MakeAvailable(sqlite3)

# REPLXX for REPL operations
ADD_SUBDIRECTORY(replxx)

# Tree-sitter
SET(TREE_SITTER_RUNTIME "${CMAKE_CURRENT_SOURCE_DIR}/tree-sitter/lib" CACHE PATH "Tree-sitter runtime libraries")
