cmake_minimum_required(VERSION 3.16)
project(RealTimeGLTFViewer LANGUAGES C CXX)

# C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources: include main.cpp, glad.c, and any other .cpp files
file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Compiler flags
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /O2)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -O3)
endif()

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    assimp
    GL       # OpenGL system library
    dl       # dynamic loader (Linux)
    pthread  # required by GLFW
)
