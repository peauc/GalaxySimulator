cmake_minimum_required(VERSION 3.11)
project(MulticoreGalaxy LANGUAGES CXX CUDA)

include_directories(inc /usr/local/include)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

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

file(GLOB_RECURSE CUDA_FILES
		src/cuda/*.cu)
link_directories("/usr/local/lib/")
add_executable(MulticoreGalaxy
        ${LOGIC_SOURCE} ${LOGIC_INCLUDE}
        ${UTILS_SOURCE} ${UTILS_INCLUDE}
        ${DISPLAY_SOURCE} ${DISPLAY_INCLUDE}
		${CUDA_FILES}
        src/main.cpp)
target_compile_features(MulticoreGalaxy PUBLIC cxx_std_11)
set_target_properties(MulticoreGalaxy PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(MulticoreGalaxy ${GLFW_LIBRARIES} ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY} tbb)
target_include_directories(MulticoreGalaxy PRIVATE ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} /usr/local/include)



