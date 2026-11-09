#!/bin/bash

echo "Starting shell..."

cmake -B build -S .
cmake --build build --target all

./build/tests/unit_test
./build/shell
