//
// Created by kamil7 on 2017-04-10.
//

#ifndef GAME_BRICK_H
#define GAME_BRICK_H


#include <android/log.h>

#include <GLES2/gl2.h>

#include "SharedData.h"
#include "ModelInterface.h"

#define  LOG_BRICK_TAG    "Brick"
#define  LOG_BRICK_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_BRICK_TAG,__VA_ARGS__)

class Brick: public ModelInterface
{
public:
    Brick(float xPosition, float yPosition);
    glm::vec4 getColourVector();
    void setColourVector(float red, float green, float blue, float alpha);
    glm::mat4 getModelMatrix();
    std::string getDrawingName();
    void update();
private:
    float _xPosition;
    float _yPosition;
    void generateRandomColour();
    float getFloat();
};

#endif //GAME_BRICK_H
