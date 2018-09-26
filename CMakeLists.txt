cmake_minimum_required(VERSION 3.12)
project(MulticoreGalaxy)

include_directories(inc)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL)
find_package(GLUT)

file(GLOB_RECURSE SOURCE
        src/*.cpp)
file(GLOB_RECURSE INCLUDE
        inc/*.hpp)

add_executable(MulticoreGalaxy ${SOURCE} ${INCLUDE} src/main.cpp)
target_link_libraries(MulticoreGalaxy ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY} pthread)
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
