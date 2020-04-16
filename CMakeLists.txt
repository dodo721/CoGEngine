cmake_minimum_required(VERSION 3.0.0)
project(DodoVoxelEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# External library modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(CTest)
enable_testing()

# Project header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Include library header files
set(INCLUDE_DIRS
#    ${CMAKE_SOURCE_DIR}/external/glm
#    ${CMAKE_SOURCE_DIR}/external/glfw-3.3.2/include
#    ${CMAKE_SOURCE_DIR}/external/glad/include
)
include_directories(INCLUDE_DIRS)

# OpenGL
find_package(OpenGL REQUIRED)

# GLM
set(GLM_ROOT_DIR ${CMAKE_SOURCE_DIR}/external/glm)
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
include_directories(${GLM_INCLUDE_DIR})
#add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm)
#message(STATUS "GLM built externally")

# Build GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw-3.3.2)
message(STATUS "GLFW built externally")

# Build GLAD
#add_library(GLAD ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad)
message(STATUS "GLAD built externally")

set(LIBS OpenGL::GL glfw glad)

# Compile project source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SHADERS "shaders/*.vert" "shaders/*.frag")

add_executable(${PROJECT_NAME} ${SOURCES} ${SHADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
