#!/bin/bash


find code -name "*.cpp" -exec echo "formatting {}" \; -exec clang-format -i {} \;
find code -name "*.hpp" -exec echo "formatting {}" \; -exec clang-format -i {} \;

find test -name "*.cpp" -exec echo "formatting {}" \; -exec clang-format -i {} \;
find test -name "*.hpp" -exec echo "formatting {}" \; -exec clang-format -i {} \;