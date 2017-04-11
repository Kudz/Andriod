//
// Created by kamil7 on 2017-04-10.
//

#ifndef GAME_BRICKDESCRIPTION_H
#define GAME_BRICKDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"

class BrickDescription: public ModelDescriptionInterface {
public:
    BrickDescription();
    std::vector<float> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<float> _vertexes;
};


#endif //GAME_BRICKDESCRIPTION_H
