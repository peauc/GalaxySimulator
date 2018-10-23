cmake_minimum_required(VERSION 3.12)
project(MulticoreGalaxy)

include_directories(inc /usr/local/include)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL)
find_package(GLUT)
find_package(tbb REQUIRED)

file(GLOB_RECURSE UTILS_SOURCE
        src/utils/*)
file(GLOB_RECURSE UTILS_INCLUDE
        inc/utils/*.hpp)

file(GLOB_RECURSE LOGIC_SOURCE
        src/logic/*.cpp)
file(GLOB_RECURSE LOGIC_INCLUDE
        inc/logic/*.hpp)

file(GLOB_RECURSE DISPLAY_SOURCE
        src/display/*.cpp)
file(GLOB_RECURSE DISPLAY_INCLUDE
        inc/display/*.hpp)

link_directories("/usr/local/lib/")
add_executable(MulticoreGalaxy
        ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
        ${UTILS_SOURCE} ${UTILS_INCLUDE}
        ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE}
        src/main.cpp)
target_link_libraries(MulticoreGalaxy ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY} tbb)
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)



