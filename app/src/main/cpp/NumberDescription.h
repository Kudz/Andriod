//
// Created by kamil7 on 2017-04-11.
//

#ifndef GAME_NUMBERDESCRIPTION_H
#define GAME_NUMBERDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"
#include "NumberBase.h"

class NumberDescription: public ModelDescriptionInterface
{
public:
    NumberDescription(std::string text);
    std::vector<float> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<float> _vertexes;
};


#endif //GAME_NUMBERDESCRIPTION_H
