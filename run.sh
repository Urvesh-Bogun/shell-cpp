#!/bin/bash

echo "Starting shell..."

cmake -B build -S .
cmake --build build
./build/tests/unit_test
./build/shell
