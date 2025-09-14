cmake_minimum_required(VERSION 3.16)
project(Real-Time-Voxel-Path-Tracer LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)  # Enable optimizations

# Grab all source files inside src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Define the executable
add_executable(Real-Time-Voxel-Path-Tracer ${SOURCES})

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Include headers from include/
target_include_directories(Real-Time-Voxel-Path-Tracer PRIVATE include)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(Real-Time-Voxel-Path-Tracer PRIVATE sfml-graphics sfml-window sfml-system)

# Compiler warnings
if (MSVC)
    target_compile_options(Real-Time-Voxel-Path-Tracer PRIVATE /W4 /permissive-)
else()
    target_compile_options(Real-Time-Voxel-Path-Tracer PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
