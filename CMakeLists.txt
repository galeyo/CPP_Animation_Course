cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(CPP_Animation_Course)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)
set(GLFW_ROOT_DIR dependencies/glfw)
set(GLAD_ROOT_DIR dependencies/glad)

add_subdirectory(${GLFW_ROOT_DIR})
add_subdirectory(${GLAD_ROOT_DIR})
add_subdirectory(src/OpenGL)
add_subdirectory(src/Vulkan)