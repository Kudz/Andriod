//
// Created by kamil7 on 2017-04-10.
//

#ifndef GAME_LINETEXTDESCRIPTION_H
#define GAME_LINETEXTDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"
#include "LetterBase.h"

#define  LOG_LINE_TEXT_DESCRIPTION_TAG    "LineTextDescription"

class LineTextDescription: public ModelDescriptionInterface
{
public:
    LineTextDescription(std::string text);
    std::vector<float> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<float> _vertexes;
};


#endif //GAME_LINETEXTDESCRIPTION_H
