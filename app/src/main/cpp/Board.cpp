//
// Created by kamil7 on 2017-03-30.
//

#include "Board.h"

Board::Board()
: _isMoving(false)
{
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Board");
    this->_xMax = RIGHT_SCREEN_POSITION - BOARD_WIDTH/2;
    this->_xMin = LEFT_SCREEN_POSITION + BOARD_WIDTH/2;
    this->_yPosition = BOTTOM_SCREEN_POSITION + BOARD_HEIGHT/2;
    this->_modelMatrix[3][1] = this->_yPosition;
}

glm::vec4 Board::getColourVector()
{
    return this->_colour;
}

void Board::setColourVector(float red, float green, float blue, float alpha)
{
    this->_colour[0] = red;
    this->_colour[1] = green;
    this->_colour[2] = blue;
    this->_colour[3] = alpha;
}
glm::mat4 Board::getModelMatrix()
{
    return this->_modelMatrix;
}

std::string Board::getDrawingName()
{
    return this->_triangleDrawingName;
}

void Board::setXPosition(int xPosition)
{
}

float Board::normalizePosition(float screenPosition)
{
    float result;
    float screenWidth = SharedData::getScreenWidth();
    result = (2.0f * screenPosition)/(float)screenWidth -1.0f;
    return result;
}

void Board::update()
{
    bool isTouching = SharedData::getTouchingStatus();

    if(this->_isMoving)
    {
        if(isTouching)
        {
            float actualXPosition = SharedData::getXTouchPosition();
            float actualXPositionNorm = this->normalizePosition(actualXPosition);
            float xDifference = this->_savedXPositionNorm - actualXPositionNorm;

            float newXTranslationValue = this->_savedModelMatrix[3][0] - xDifference;
            if (newXTranslationValue < this->_xMin)
            {
                newXTranslationValue = this->_xMin;
            }
            else
            {
                if (newXTranslationValue > this->_xMax)
                {
                    newXTranslationValue = this->_xMax;
                }
            }
            this->_modelMatrix[3][0] = newXTranslationValue;
        }
        else
        {
            this->_isMoving =false;
        }
    }
    else
    {
        if(isTouching)
        {
            float actualXPosition = SharedData::getXTouchPosition();
            float actualXPositionNorm = this->normalizePosition(actualXPosition);
            this->_savedXPositionNorm = actualXPositionNorm;
            this->_savedModelMatrix = this->_modelMatrix;
            this->_isMoving = true;
        }
    }
}

void Board::setVisibility(bool value)
{
    this->_isVisible = value;
}

bool Board::getVisibility()
{
    return this->_isVisible;
}

void Board::resetBoard()
{
    this->_modelMatrix[3][0] = 0.0f;
    this->_modelMatrix[3][1] = this->_yPosition;
}