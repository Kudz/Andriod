//
// Created by kamil7 on 2017-03-30.
//

#include "Board.h"

Board::Board()
: _isMoving(false)
{
    //do I need that?
    this->_screenHeight = SharedData::getScreenHeight();
    LOG_BOARD_SHADER_I("screen height = %d", this->_screenHeight);

    this->_boardWidth = 0.6f;
    this->_boardHeight = 0.08f;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Board");
    this->_xMax = 1.0f -0.02f - this->_boardWidth/2;
    this->_xMin = -1.0f + 0.02f + this->_boardWidth/2;
    this->_yPosition = -1.4f + _boardHeight/2 + 0.1f;
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
    bool isTouching = SharedData::getMovementStatus();

//    std::string message = "isTouching = " + a2s<bool>(isTouching);
//    SharedData::logInfo(LOG_BOARD_TAG, message.c_str());

//    message = "this->_isMoving = " + a2s<bool>(this->_isMoving);
//    SharedData::logInfo(LOG_BOARD_TAG, message.c_str());

//    message = "this->_savedXPositionNorm = " + a2s<bool>(this->_savedXPositionNorm);
//    SharedData::logInfo(LOG_BOARD_TAG, message.c_str());

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