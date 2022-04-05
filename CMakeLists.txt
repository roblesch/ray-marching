cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(ray-marching)

file(GLOB_RECURSE ray-marching-source "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE ray-marching-headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*")

add_executable(ray-marching ${ray-marching-source} ${ray-marching-headers} src/vec3.h src/ray.h src/surface.h src/sphere.h src/scene.h src/material.h src/scene.cpp src/hit_record.h src/common.h)
