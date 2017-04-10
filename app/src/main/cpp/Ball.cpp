//
// Created by kamil7 on 2017-04-08.
//

#include "Ball.h"

Ball::Ball()
{
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Ball");
    this->_movmentVector = glm::vec2(0.01f, 0.02f);
}

glm::vec4 Ball::getColourVector()
{
    return this->_colour;
}

void Ball::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 Ball::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string Ball::getDrawingName()
{
    return this->_triangleDrawingName;
}

void Ball::update()
{
    float newXTranslationValue = this->_modelMatrix[3][0] + this->_movmentVector[0];
    float newYTranslationValue = this->_modelMatrix[3][1] + this->_movmentVector[1];

    //dimension of ball need to be accounted in computation
    if (newXTranslationValue < LEFT_SCREEN_POSITION) //zaminic nie makro a wartosc
    {
        this->_movmentVector[0] = -this->_movmentVector[0];
    }
    else
    {
        if (newXTranslationValue > RIGHT_SCREEN_POSITION)
        {
            this->_movmentVector[0] = -this->_movmentVector[0];
        }
    }

    if (newYTranslationValue < BOTTOM_SCREEN_POSITION)
    {
        this->_movmentVector[1] = -this->_movmentVector[1];
    }
    else
    {
        if (newYTranslationValue > TOP_SCREEN_POSITION)
        {
            this->_movmentVector[1] = -this->_movmentVector[1];
        }
    }

    this->_modelMatrix[3][0] = newXTranslationValue;
    this->_modelMatrix[3][1] = newYTranslationValue;
}