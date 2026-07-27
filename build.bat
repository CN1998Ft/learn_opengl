@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"

if not exist .\build (
    mkdir .\build
    echo * > .\build\.gitignore
)

if "%~1"=="clean" (
    rmdir /S /Q .\build
)

if "%~1"=="" (
    pushd .\build
    cl.exe /Femain.exe /EHsc /MD /std:c++17 /Zi /W4 /I"../src/include" ^
    /I"%USERPROFILE%\scoop\apps\glfw\current\include" ^
    ../src/gl.c ../src/*.cpp /link ^
    /LIBPATH:"%USERPROFILE%\scoop\apps\glfw\current\lib-vc2022" ^
    glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib
    popd
)

if "%~1"=="cmake" (
    build.bat clean
    cmake -B build
    echo * > .\build\.gitignore
    cmake --build build
)
