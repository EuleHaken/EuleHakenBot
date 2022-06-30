#!/bin/bash

find src/ \( -iname "*.hpp" -o -iname "*.cpp" \) -exec clang-format -style=file:./src/.clang-format -i {} \;
