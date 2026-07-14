#!/usr/bin/env bash
cd "$(dirname "$0")" && echo "[Current dir: $PWD]"

build()
{
    mac='^darwin.*$'
    linux='^linux.*$'
    pushd ../build > /dev/null 2>&1

    INCLUDE="-I../code/include"
    CFLAGS="-std=c++17 -Wall -g"
    SRC="../code/gl.c ../code/*.cpp"
    LIBS="-lglfw"
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

    echo "gcc $CFLAGS $INCLUDE $SRC $LIBS -o main"
    g++ $CFLAGS $INCLUDE $SRC $LIBS -o main

    popd > /dev/null 2>&1
}

if [[ ! -d ../build ]]; then
    mkdir ../build > /dev/null 2>&1
    echo '*' > ../build/.gitignore
fi

if [[ "$#" == 0 ]]; then
    build
elif [[ "$1" == "clean" ]]; then
    rm -rf ../build > /dev/null 2>&1
fi
