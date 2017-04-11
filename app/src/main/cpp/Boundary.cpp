//
// Created by kamil7 on 2017-04-08.
//

#include "Boundary.h"

Boundary::Boundary()
{
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Boundary");
}

glm::vec4 Boundary::getColourVector()
{
    return this->_colour;
}

void Boundary::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 Boundary::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string Boundary::getDrawingName()
{
    return this->_triangleDrawingName;
}

void Boundary::setVisibility(bool value)
{
    this->_isVisible = value;
}

bool Boundary::getVisibility()
{
    return this->_isVisible;
}