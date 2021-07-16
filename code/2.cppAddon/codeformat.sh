#!/bin/bash

find . -path '*/*.cpp' -o -path '*/*.h' | xargs clang-format -style=file -i
