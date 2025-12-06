cmake_minimum_required(VERSION 3.16)
project(learnOpenGL)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${CMAKE_SOURCE_DIR}/includes      # glad/glad.h and glad/KHR/khrplatform.h
    /opt/homebrew/include             # GLFW headers
)

link_directories(/opt/homebrew/lib)

add_executable(hello_window
    src/part1/hello_window.cpp
    src/glad.c
)

add_executable(hello_triangle
    src/part1/hello_triangle.cpp
    src/glad.c
)

add_executable(shaders
    src/part1/shaders.cpp
    src/glad.c
)

add_executable(textures
    src/part1/textures.cpp
    src/glad.c
)

add_executable(coordinates
    src/part1/coordinates.cpp
    src/glad.c
)

foreach(target hello_window hello_triangle shaders textures coordinates)
    target_link_libraries(${target}
        glfw
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endforeach()