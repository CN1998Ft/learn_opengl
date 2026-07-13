@echo off
setlocal enabledelayedexpansion
cd /D "%~dp0"

if not exist ..\build (
    mkdir ..\build
    echo * > ..\build\.gitignore
)

if "%~1"=="clean" (
    del /S /Q /F ..\build
)

if "%~1"=="" (
    pushd ..\build
    cl.exe /Femain.exe /EHsc /MD /std:c++17 /Zi /W4 /I"../code/include" ^
    /I"C:\\Users\\93581\\scoop\\apps\\glfw\\current\\include" ^
    ../code/gl.c ../code/*.cpp /link ^
    /LIBPATH:"C:\\Users\\93581\\scoop\\apps\\glfw\\current\\lib-vc2022" ^
    glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib
    popd
)
