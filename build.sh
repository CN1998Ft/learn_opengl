#!/usr/bin/env bash
cd "$(dirname "$0")" && echo "[Current dir: $PWD]"

build()
{
    mac='^darwin.*$'
    linux='^linux.*$'

    INCLUDE="-I./src/include"
    CFLAGS="-std=c++17 -Wall -g"
    SRC="./src/gl.c ./src/*.cpp"
    LIBS="-lglfw"
    OUTFILE="-o ./build/main"
    if [[ "$OSTYPE" =~ $mac ]]; then
        echo "[Building mac version learning OpenGL project]"
        INCLUDE+=" -I/opt/homebrew/include"
        LIBS+=" -L/opt/homebrew/lib \
-framework OpenGL -framework Cocoa -framework IOKit \
-framework CoreVideo"
    elif [[ "$OSTYPE" =~ $linux ]]; then
        echo "[Building linux version learning OpenGL project]"
        LIBS+=" -lGL -lX11 -lpthread -lXrandr -lXi -ldl"
    fi

    echo "gcc $CFLAGS $INCLUDE $SRC $LIBS $OUTFILE"
    g++ $CFLAGS $INCLUDE $SRC $LIBS $OUTFILE
}

clean()
{
    rm -rf ./build > /dev/null 2>&1
    mkdir ./build > /dev/null 2>&1
    echo '*' > ./build/.gitignore
}

if [[ ! -d ./build ]]; then
    mkdir ./build > /dev/null 2>&1
    echo '*' > ./build/.gitignore
fi

if [[ "$#" == 0 ]]; then
    clean
    build
elif [[ "$1" == "clean" ]]; then
    clean
elif [[ "$1" == "cmake" ]]; then
    clean
    cmake -B build
    cmake --build build
fi
