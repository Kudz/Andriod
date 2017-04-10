//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_BALLDESCRIPTION_H
#define GAME_BALLDESCRIPTION_H

#include <math.h>

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"

#define  LOG_BALL_TAG    "BallDescription"

class BallDescription: public ModelDescriptionInterface
{
public:
    BallDescription();
    std::vector<double> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<double> _vertexes;
    std::vector<glm::vec2> createCircle(float radius, int pointsAmount);
};


#endif //GAME_BALLDESCRIPTION_H
