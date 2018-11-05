cmake_minimum_required(VERSION 3.12)

set(CMAKE_VERBOSE_MAKEFILE ON)
project(MulticoreGalaxy)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include_directories(inc /usr/local/include)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(tbb REQUIRED)

if (APPLE)
    add_compile_definitions(APPLE)
    set(LINK ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY})
else()
    set(LINK glut GLU GL GLEW)
endif()

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
message("HELLO")
message(${LINK})
target_link_libraries(MulticoreGalaxy ${LINK} tbb)
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)
