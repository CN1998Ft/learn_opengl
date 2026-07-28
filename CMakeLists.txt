cmake_minimum_required(VERSION 3.30)

project(learn_opengl C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    src/main.cpp
    src/gl.c
)

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    if(MSVC)
        target_link_options(
            main
            PRIVATE
            /NODEFAULTLIB:MSVCRT
        )
    endif()
    file(TO_CMAKE_PATH "$ENV{USERPROFILE}/scoop/apps/glfw/current" SCOOP_GLFW)
    target_include_directories(
        main
        PRIVATE
        "${SCOOP_GLFW}/include"
    )
    target_link_directories(
        main
        PRIVATE
        "${SCOOP_GLFW}/lib-vc2022"
    )
    target_link_libraries(
        main
        PRIVATE
        glfw3
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    target_include_directories(
        main
        PRIVATE
        "/opt/homebrew/include"
    )
    target_link_directories(
        main
        PRIVATE
        "/opt/homebrew/lib"
    )
    target_link_libraries(
        main
        PRIVATE
        glfw3
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    find_package(glfw3 REQUIRED)
    target_link_libraries(
        main
        PRIVATE
        glfw
    )
endif()

find_package(OpenGL REQUIRED)

include_directories(
    src/include
)

target_link_libraries(main
    PRIVATE
    OpenGL::GL
)
