cmake_minimum_required(VERSION 3.12)
project(MulticoreGalaxy)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL)
find_package(GLUT)

add_executable(MulticoreGalaxy main.cpp)
