#!/bin/sh

cloc $(git ls-files --recurse-submodules) \
     --exclude-dir=doxygen-awesome-css \
     --exclude-dir=deps