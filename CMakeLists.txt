cmake_minimum_required(VERSION 3.16)
project(Real-Time-Voxel-Path-Tracer LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Grab all source files inside src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Define the executable
add_executable(Real-Time-Voxel-Path-Tracer ${SOURCES})
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Include headers from include/
target_include_directories(Real-Time-Voxel-Path-Tracer PRIVATE include)

# ---- Compiler warnings ----
if (MSVC)
    target_compile_options(Real-Time-Voxel-Path-Tracer PRIVATE /W4 /permissive- /O2)
else()
    target_compile_options(Real-Time-Voxel-Path-Tracer PRIVATE -Wall -Wextra -pedantic -O3)
endif()

# ---- Find and link Assimp ----
find_package(assimp REQUIRED)
target_include_directories(Real-Time-Voxel-Path-Tracer PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_link_libraries(Real-Time-Voxel-Path-Tracer PRIVATE assimp)

# ---- Find and link GLM ----
find_package(glm REQUIRED)
if (glm_FOUND)
    target_include_directories(Real-Time-Voxel-Path-Tracer PRIVATE ${GLM_INCLUDE_DIRS})
endif()

# ---- Optional: enable multi-threading for future path tracing ----
find_package(Threads REQUIRED)
target_link_libraries(Real-Time-Voxel-Path-Tracer PRIVATE Threads::Threads)
