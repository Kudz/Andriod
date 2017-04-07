//
// Created by kamil7 on 2017-04-06.
//

#ifndef GAME_TRIANGLEOBJECTDESCRIPTION_H
#define GAME_TRIANGLEOBJECTDESCRIPTION_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "TriangleDescriptionInterface.h"

#define  LOG_BOARD_TAG    "BoardDescription"

class BoardDescription: public TriangleDescriptionInterface {
public:
    BoardDescription();
    std::vector<double> getDrawingPoints(); //return drawing points for OpenGL
private:
    std::vector<double> _vertexes;
};


#endif //GAME_TRIANGLEOBJECTDESCRIPTION_H
