//
// Created by kamil7 on 2017-04-10.
//

#include "Brick.h"

Brick::Brick(float xPosition, float yPosition)
{
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Brick");

    this->_xPosition = xPosition;
    this->_yPosition = yPosition;
    this->_modelMatrix[3][0] = this->_xPosition;
    this->_modelMatrix[3][1] = this->_yPosition;

    this->generateRandomColour();
}

void Brick::generateRandomColour()
{
    this->setColourVector(this->getFloat(), this->getFloat(), this->getFloat(), 1.0f);
}

float Brick::getFloat()
{
    return (((float)std::rand()*(0.9f - 0.1f) / RAND_MAX) + 0.1f);
}

glm::vec4 Brick::getColourVector()
{
    return this->_colour;
}

void Brick::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 Brick::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string Brick::getDrawingName()
{
    return this->_triangleDrawingName;
}

void Brick::update()
{

}