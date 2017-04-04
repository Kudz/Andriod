//
// Created by kamil7 on 2017-03-30.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "TriangleObjectInterface.h"

#define  LOG_BOARD_TAG    "Board"
#define  LOG_BOARD_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_BOARD_TAG,__VA_ARGS__)

class Board: public TriangleObjectInterface
{
public:
    Board();
    void setXPosition(int xPosition);
    std::vector<double> getDrawingPoints(); //return drawing points for OpenGL
private:
    float _homePosition[2]; // 0 - x position, 1 y - position
    float _boardWidth;
    float _boardHeight;
    float _actualPosition[2];
    int _screenWidth;
    int _screenHeight;
    GLuint _programID;
    std::vector<double> _vertexes;
};


#endif //GAME_BOARD_H
