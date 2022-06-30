#!/bin/bash

find src/ -iname "*.cpp" -o -iname "*.hpp" -exec clang-format -i {};
