//
// Created by kamil7 on 2017-04-06.
//

#ifndef GAME_BOARDDESCRIPTION_H
#define GAME_BOARDDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelDescriptionInterface.h"

#define  LOG_BOARD_TAG    "BoardDescription"

class BoardDescription: public ModelDescriptionInterface {
public:
    BoardDescription();
    std::vector<float> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<float> _vertexes;
};


#endif //GAME_TRIANGLEOBJECTDESCRIPTION_H
