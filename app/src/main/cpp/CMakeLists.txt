cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_definitions(-DSOURCEFOLDERPATH="${CMAKE_CURRENT_SOURCE_DIR}")

set(ALL_INCLUDE_DIRS SharedData.h)
include_directories(${ALL_INCLUDE_DIRS})

add_library(cppToJava SHARED
    CppToJavaWrapper.cpp
    GameScene.cpp
    Shaders.cpp
    TriangleShader.cpp
    LineShader.cpp
    SharedData.cpp
    ModelDescriptionInterface.cpp
    ModelInterface.cpp
    TriangleDrawing.cpp
    Board.cpp
    BoardDescription.cpp
    LineDrawing.cpp
    Boundary.cpp
    BoundaryDescription.cpp
    Ball.cpp
    BallDescription.cpp
    Brick.cpp
    BrickDescription.cpp
    )
target_link_libraries(cppToJava android log EGL GLESv2)