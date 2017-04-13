//
// Created by kamil7 on 2017-04-08.
//

#include "Ball.h"

Ball::Ball()
{
    this->_velocity = BALL_MIN_SPEED;
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_triangleDrawingName = std::string("Ball");
    this->_movmentVector = glm::vec2(0.01f, 0.02f);
    this->_homePosition = glm::vec2(0.0f, BOTTOM_SCREEN_POSITION + BOARD_HEIGHT + BALL_RADIUS);
    this->resetBall();
}

Ball::Ball(float xPosition, float yPosition)
{
    this->_isVisible = true;
    this->_modelMatrix = glm::mat4(1.0f);
    this->_modelMatrix[3][0] = xPosition;
    this->_modelMatrix[3][1] = yPosition;
    this->_triangleDrawingName = std::string("Ball");
    this->_movmentVector = glm::vec2(0.0f, 0.0f);
}

void Ball::setHomePosition()
{
    this->_modelMatrix[3][0] = this->_homePosition[0];
    this->_modelMatrix[3][1] = this->_homePosition[1];
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

    this->_modelMatrix[3][0] = newXTranslationValue;
    this->_modelMatrix[3][1] = newYTranslationValue;

    this->_velocityDecreaseCounter++;
    if(this->_velocityDecreaseCounter == DECREASE_VELOCITY_AT)
    {
        this->decreaseVelocity();
        this->_velocityDecreaseCounter = 0;
    }
}

void Ball::setVisibility(bool value)
{
    this->_isVisible = value;
}

bool Ball::getVisibility()
{
    return this->_isVisible;
}

float Ball::normalizeXPosition(float screenPosition)
{
    float result;
    float screenWidth = SharedData::getScreenWidth();
    result = (2.0f * screenPosition)/(float)screenWidth -1.0f;
    return result;
}

float Ball::normalizeYPosition(float screenPosition)
{
    float result;
    float screenWidth = SharedData::getScreenWidth();
    float screenHeight = SharedData::getScreenHeight();
    result = (-2.0f * screenPosition)/(float)screenWidth +screenHeight/screenWidth;
    return result;
}

bool Ball::setDirectionAngle()
{
    float xPosition = this->normalizeXPosition(SharedData::getXTouchPosition());
    float yPosition = this->normalizeYPosition(SharedData::getYTouchPosition());

//    std::string message = "xPosition = " + a2s<>(xPosition);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());
//    message = "yPosition = " + a2s<>(yPosition);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());

    if(yPosition > BOTTOM_SCREEN_POSITION + BOARD_HEIGHT + 2*BALL_RADIUS)
    {
        float tangent = (yPosition - this->_homePosition[1])/(xPosition - this->_homePosition[0]);
        this->_directionAngle = atanf(tangent);
        if(this->_directionAngle < 0.0f)
        {
            this->_directionAngle = this->_directionAngle + M_PI;
        }
        this->computeMovementVector();

//        std::string message = "this->_directionAngle = " + a2s<>(this->_directionAngle);
//        SharedData::logInfo(LOG_BALL_TAG, message.c_str());

        return true;
    }
    return false;
}

void Ball::computeMovementVector()
{
    this->_movmentVector[0] = cosf(this->_directionAngle)*this->_velocity;
    this->_movmentVector[1] = sinf(this->_directionAngle)*this->_velocity;

//    std::string message = "_movementVector = " + a2s<>(this->_movmentVector[1]);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());
}

glm::vec2 Ball::getMovementVector()
{
    return this->_movmentVector;
}

float Ball::getDirectionAngle()
{
    return this->_directionAngle;
}

void Ball::increaseVelocity()
{
    this->_velocity = this->_velocity + 0.01;
    if(this->_velocity > BALL_MAX_SPEED)
    {
        this->_velocity = BALL_MAX_SPEED;
    }
//    std::string message = "_velocity = " + a2s<>(this->_velocity);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());
}

void Ball::decreaseVelocity()
{
    this->_velocity = this->_velocity - 0.01;
    if(this->_velocity < BALL_MIN_SPEED)
    {
        this->_velocity = BALL_MIN_SPEED;
    }
}

void Ball::setNewPosition(float xPosition, float yPosition)
{
    this->_modelMatrix[3][0] = xPosition;
    this->_modelMatrix[3][1] = yPosition;
}

void Ball::increaseDirectionAngle(float angleChange)
{
    this->_directionAngle = this->_directionAngle + angleChange;
    if(this->_directionAngle > 2*M_PI)
    {
        this->_directionAngle = this->_directionAngle - 2*M_PI;
    }
//    std::string message = "_directionAngle = " + a2s<>(this->_directionAngle);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());
    this->computeMovementVector();
}

void Ball::reverseX()
{
    this->_movmentVector[0] = -this->_movmentVector[0];
    this->_directionAngle = atan2(this->_movmentVector[1], this->_movmentVector[0]);
    if(this->_directionAngle < 0.0f)
    {
        this->_directionAngle = 2*M_PI + this->_directionAngle;
    }
    this->computeMovementVector();
}

void Ball::reverseY()
{
    this->_movmentVector[1] = -this->_movmentVector[1];
    this->_directionAngle = atan2(this->_movmentVector[1], this->_movmentVector[0]);
    if(this->_directionAngle < 0.0f)
    {
        this->_directionAngle = 2*M_PI + this->_directionAngle;
    }
//    std::string message = "_directionAngle = " + a2s<>(this->_directionAngle);
//    SharedData::logInfo(LOG_BALL_TAG, message.c_str());
    this->computeMovementVector();
}

void Ball::reverseXY()
{
    this->_movmentVector[0] = -this->_movmentVector[0];
    this->_movmentVector[1] = -this->_movmentVector[1];
    this->_directionAngle = atan2(this->_movmentVector[1], this->_movmentVector[0]);
    if(this->_directionAngle < 0.0f)
    {
        this->_directionAngle = 2*M_PI + this->_directionAngle;
    }
    this->computeMovementVector();
}

void Ball::resetBall()
{
    this->setHomePosition();
    this->_velocity = BALL_MIN_SPEED;
    this->_velocityDecreaseCounter = 0;
}