//
// Created by kamil7 on 2017-03-30.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "TriangleModelInterface.h"

#define  LOG_BOARD_TAG    "Board"
#define  LOG_BOARD_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_BOARD_TAG,__VA_ARGS__)

class Board: public TriangleModelInterface
{
public:
    Board();
    void setXPosition(int xPosition);
    glm::vec4 getColourVector();
    void setColour(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getTriangleDrawingName();
    void update();
private:
    float _boardWidth;
    float _boardHeight;
    int _screenWidth;
    int _screenHeight;
    float _xMax;
    float _xMin;
    float _yposition;

    //touching values
    bool _isMoving;
    float _savedXPositionNorm;
    float _savedYPositionNorm;
    glm::mat4 _savedModelMatrix;
    float normalizePosition(float screenPosition);
};


#endif //GAME_BOARD_H
