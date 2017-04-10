//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_BALL_H
#define GAME_BALL_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"

#define  LOG_BALL_TAG    "Ball"

class Ball: public ModelInterface
{
public:
    Ball();
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void update();
private:
    glm::vec2 _movmentVector;
};


#endif //GAME_BALL_H
