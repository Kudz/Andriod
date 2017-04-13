//
// Created by kamil7 on 2017-04-11.
//

#ifndef GAME_NUMBER_H
#define GAME_NUMBER_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"
#include "LineDrawing.h"
#include "NumberDescription.h"

class Number: public ModelInterface
{
public:
    Number(std::string text);
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void setNewPosition(float xPosition, float yPosition);
    void setNewNumber(std::string numberData);
    void setVisibility(bool value);
    bool getVisibility();
private:
    std::shared_ptr<LineDrawing> _lineDrwawing;
};


#endif //GAME_NUMBER_H
