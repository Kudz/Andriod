//
// Created by kamil7 on 2017-04-10.
//

#include "LineText.h"

LineText::LineText(std::string text, float xPosition, float yPosition)
{
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_modelMatrix[3][0] = xPosition;
    this->_modelMatrix[3][1] = yPosition;
    this->_triangleDrawingName = std::string(text);
    this->setColourVector(0.0f, 0.0f, 0.0f, 1.0f);

}

glm::vec4 LineText::getColourVector()
{
    return this->_colour;
}

void LineText::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 LineText::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string LineText::getDrawingName()
{
    return this->_triangleDrawingName;
}

void LineText::update()
{

}

void LineText::setVisibility(bool value)
{
    this->_isVisible = value;
}

bool LineText::getVisibility()
{
    return this->_isVisible;
}
