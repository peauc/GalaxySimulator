cmake_minimum_required(VERSION 3.12)
# Build type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif ()
project(MulticoreGalaxy)
include_directories(inc /usr/local/include${OpenCL_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH $"${CMAKE_SOURCE_DIR}/cmake/Modules/" {CMAKE_MODULE_PATH})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
if (APPLE)
    add_compile_definitions(APPLE)
endif ()

find_package(OpenGL)
find_package(GLUT)
find_package(tbb REQUIRED)
find_package(OpenCL REQUIRED)

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

file(GLOB_RECURSE KERNEL
        src/opencl/*.cl)

if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_CXX_FLAGS "-D_REETRANT -Wall -Wextra -std=c++14")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0")
    elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -O3 -fno-strict-aliasing")
    endif ()
endif (CMAKE_COMPILER_IS_GNUCC)
link_directories("/usr/local/lib/")
add_executable(MulticoreGalaxy
        ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
        ${UTILS_SOURCE} ${UTILS_INCLUDE}
        ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE} ${KERNEL}
        src/main.cpp)
target_link_libraries(MulticoreGalaxy ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY} ${OpenCL_LIBRARY} tbb)
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)
