//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_BOUNDARY_H
#define GAME_BOUNDARY_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"

#define  LOG_BOUNDARY_TAG    "Boundary"

class Boundary: public ModelInterface
{
public:
    Boundary();
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void update();
private:

};


#endif //GAME_BOUNDARY_H
