cmake_minimum_required(VERSION 3.12)
project(MulticoreGalaxy)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
option(USE_CUDA "Use CUDA" ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(tbb REQUIRED)

include_directories(inc /usr/local/include)



if (APPLE)
    add_compile_definitions(APPLE)
    set(LINK ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY} tbb)
else()
    set(LINK "glut"
            "GLU"
            "GL"
            "GLEW" "tbb")
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

file(GLOB_RECURSE SOURCE_CUDA
        src/cuda/*.cu)
file(GLOB_RECURSE INCLUDE_CUDA
        inc/cuda/*.hpp)

if( ("${CMAKE_VERSION}" VERSION_EQUAL 3.8) OR
("${CMAKE_VERSION}" VERSION_GREATER 3.8) )
    # Modern CMake
    if(USE_CUDA)
        enable_language("CUDA")
        add_executable(MulticoreGalaxy  ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
                ${UTILS_SOURCE} ${UTILS_INCLUDE} ${INCLUDE_CUDA}
                ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE} ${SOURCE_CUDA} src/main.cpp)
        add_executable(MulticoreGalaxyWithoutCuda
                ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
                ${UTILS_SOURCE} ${UTILS_INCLUDE}
                ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE} src/main.cpp)
    else(USE_CUDA)
        add_executable(MulticoreGalaxy  ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
                ${UTILS_SOURCE} ${UTILS_INCLUDE} ${INCLUDE_CUDA}
                ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE} src/main.cpp)
    endif()
else()
    # Old CMake
    add_executable(MulticoreGalaxy  ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
            ${UTILS_SOURCE} ${UTILS_INCLUDE} ${INCLUDE_CUDA}
            ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE} src/main.cpp)
    if(USE_CUDA)
        find_package(CUDA 8.0)
        if(NOT CUDA_FOUND)
            message(STATUS "CUDA not found")
            set(USE_CUDA OFF)
        else()
            CUDA_ADD_LIBRARY(MulticoreGalaxy_gpu ${SOURCE_CUDA})
            target_link_libraries(MulticoreGalaxy MulticoreGalaxy_gpu)
        endif()
    endif()
endif()

link_directories("/usr/local/lib/")
target_link_libraries(MulticoreGalaxy ${LINK})
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)
target_link_libraries(MulticoreGalaxyWithoutCuda ${LINK})
target_include_directories(MulticoreGalaxyWithoutCuda PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)
