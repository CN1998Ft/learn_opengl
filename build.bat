@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"

if "%~1"=="clean" (
    rmdir /S /Q .\build
)

if not exist .\build (
    mkdir .\build
    echo * > .\build\.gitignore
)

if "%~1"=="" (
    build clean
    cl.exe /Fe.\build\main.exe /Fd.\build\ /Fo.\build\ /EHsc /MD /std:c++17 /Zi /W4 ^
    /I"./src/include" /I"%USERPROFILE%\scoop\apps\glfw\current\include" ^
    ./src/gl.c ./src/*.cpp /link ^
    /LIBPATH:"%USERPROFILE%\scoop\apps\glfw\current\lib-vc2022" ^
    glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib
)

if "%~1"=="cmake" (
    build.bat clean
    cmake -B build
    echo * > .\build\.gitignore
    cmake --build build
)

if "%~1"=="clangd" (
    del .\compile_commands.json >nul 2>nul
    build.bat clean
    cmake -B build -S . -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=On
    move .\build\compile_commands.json .\compile_commands.json
    build.bat clean
)
