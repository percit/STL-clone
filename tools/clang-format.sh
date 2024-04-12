#!/usr/bin/env sh

# Find all C/C++ source files and format them with clang-format
find src -regex '.*\.\(cpp\|hpp\|h\)' -exec clang-format -style=file -i {} \;
