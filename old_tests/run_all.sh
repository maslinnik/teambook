#!/bin/bash

set -euo pipefail

# Конфигурация
SRC_DIR="./src"
BIN_DIR="./bin"
COMPILE_FLAGS="-std=c++20 -D_GLIBCXX_DEBUG -fsanitize=address,undefined -g"

# Компилируем все cpp-файлы
for cpp_file in "$SRC_DIR"/*.cpp; do
    if [ -f "$cpp_file" ]; then
        filename=$(basename "$cpp_file" .cpp)
        g++ $COMPILE_FLAGS "$cpp_file" -o "$BIN_DIR/$filename"
    fi
done

# Запускаем все бинарники
for binary in "$BIN_DIR"/*; do
    if [ -x "$binary" ] && [ -f "$binary" ]; then
        "$binary"
    fi
done