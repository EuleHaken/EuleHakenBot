#!/bin/bash

find src/ \( -iname "*.hpp" -o -iname "*.cpp" \) -exec clang-format -style=./src/.clang-format -i {} \;
