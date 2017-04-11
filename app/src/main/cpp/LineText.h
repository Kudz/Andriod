//
// Created by kamil7 on 2017-04-10.
//

#ifndef GAME_LINETEXT_H
#define GAME_LINETEXT_H

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"
#include "LineDrawing.h"
#include "LineTextDescription.h"

#define  LOG_LINE_TEXT_TAG    "LineText"

class LineText: public ModelInterface
{
public:
    LineText(std::string text, float xPosition, float yPosition);
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void update();
    void setVisibility(bool value);
    bool getVisibility();
private:
    std::shared_ptr<LineDrawing> _lineDrwawing;
};

#endif //GAME_LINETEXT_H
