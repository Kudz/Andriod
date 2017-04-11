//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_BOUNDARYDESCRIPTION_H
#define GAME_BOUNDARYDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"

#define  LOG_BOARD_TAG    "BoardDescription"

class BoundaryDescription: public ModelDescriptionInterface
{
public:
    BoundaryDescription();
    std::vector<float> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<float> _vertexes;
};

#endif //GAME_BOUNDARYDESCRIPTION_H
