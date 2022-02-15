cmake_minimum_required(VERSION 3.16)
project(ShapefileProcess)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(ShapefileProcess main.cpp include/ShapeReader.h src/ShapeReader.cpp)
target_link_libraries(ShapefileProcess shp)