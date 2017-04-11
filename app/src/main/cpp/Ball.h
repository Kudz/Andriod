//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_BALL_H
#define GAME_BALL_H

#include <vector>

#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"

#define DECREASE_VELOCITY_AT 20

#define  LOG_BALL_TAG    "Ball"

class Ball: public ModelInterface
{
public:
    Ball();
    Ball(float xPosition, float yPosition);
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void setVisibility(bool value);
    bool getVisibility();

    void update();
    void setHomePosition();
    bool setDirectionAngle();
    glm::vec2 getMovementVector();
    float getDirectionAngle();
    void increaseVelocity();
    void decreaseVelocity();
    void setNewPosition(float xPosition, float yPosition);
    void increaseDirectionAngle(float angleChange);
    void reverseX();
    void reverseY();
    void resetBall();
private:
    glm::vec2 _homePosition;

    int _velocityDecreaseCounter;
    float _velocity;
    float _directionAngle;
    float normalizeXPosition(float screenPosition);
    float normalizeYPosition(float screenPosition);
    void computeMovementVector();
    glm::vec2 _movmentVector;

};


#endif //GAME_BALL_H
