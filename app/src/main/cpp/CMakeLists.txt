cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_definitions(-DSOURCEFOLDERPATH="${CMAKE_CURRENT_SOURCE_DIR}")

set(ALL_INCLUDE_DIRS TriangleShader.h)
include_directories(${ALL_INCLUDE_DIRS})

add_library(smasher SHARED smasher.cpp Shaders.cpp TriangleShader.cpp)

target_link_libraries(smasher android log EGL GLESv2)

add_library(cppToJava SHARED CppToJavaWrapper.cpp Shaders.cpp TriangleShader.cpp)
target_link_libraries(cppToJava android log EGL GLESv2)