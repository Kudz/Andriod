//
// Created by kamil7 on 2017-04-11.
//

#include "Number.h"

Number::Number(std::string text)
{
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string(text);
    this->setColourVector(0.0f, 0.0f, 0.0f, 1.0f);

}

glm::vec4 Number::getColourVector()
{
    return this->_colour;
}

void Number::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 Number::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string Number::getDrawingName()
{
    return this->_triangleDrawingName;
}

void Number::setNewPosition(float xPosition, float yPosition)
{
    this->_modelMatrix[3][0] = xPosition;
    this->_modelMatrix[3][1] = yPosition;
}

void Number::setVisibility(bool value)
{
    this->_isVisible = value;
}

bool Number::getVisibility()
{
    return this->_isVisible;
}

void Number::setNewNumber(std::string numberData)
{
    this->_triangleDrawingName = numberData;
}
