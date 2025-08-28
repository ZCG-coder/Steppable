#!/bin/sh

cloc $(git ls-files --recurse-submodules "*.cpp") \
     $(git ls-files --recurse-submodules "*.hpp") \
     $(git ls-files --recurse-submodules "*.py*") \
     $(git ls-files --recurse-submodules "*.js") \
     $(git ls-files --recurse-submodules "**/CMakeLists.txt") \
     $(git ls-files --recurse-submodules "*.cmake") \
     --exclude-dir=doxygen-awesome-css