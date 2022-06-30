#!/bin/bash

# Borrowed from: https://github.com/Chatterino/chatterino2/blob/master/tools/check-format.sh

fail="0"

while read -r file; do
    if ! diff -u <(cat "$file") <(clang-format "$file"); then
        echo "$file differs!"
        fail="1"
    fi
done < <(find src/ -type f \( -iname "*.hpp" -o -iname "*.cpp" \))

if [ "$fail" = "1" ]; then
    echo "At least one file is poorly formatted - check the output above"
    exit 1
fi

echo "Everything seems to be formatted properly! Good job"
