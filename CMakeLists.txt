cmake_minimum_required(VERSION 3.16)
project(ShapetileProcess)

set(CMAKE_CXX_STANDARD 14)

add_executable(ShapetileProcess main.cpp include/Shape.h)

target_link_libraries(ShapetileProcess shp)