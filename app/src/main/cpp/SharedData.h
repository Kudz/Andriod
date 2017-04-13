//
// Created by kamil7 on 2017-03-31.
//

#ifndef GAME_SHAREDDATA_H
#define GAME_SHAREDDATA_H

#include <iostream>
#include <sstream>
#include <memory>

#include "glm/glm.hpp" //vec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

#include <android/asset_manager.h>

#include "TriangleShader.h"
#include "LineShader.h"

#define TOP_SCREEN_POSITION 1.15f
#define LEFT_SCREEN_POSITION -0.98f
#define BOTTOM_SCREEN_POSITION -1.3f
#define RIGHT_SCREEN_POSITION 0.98f

#define BOARD_WIDTH 0.6f
#define BOARD_HEIGHT 0.08f

#define BRICK_WIDTH 0.3f
#define BRICK_HEIGHT 0.08f

#define BALL_RADIUS 0.04f
#define BALL_MIN_SPEED 0.03f
#define BALL_MAX_SPEED 0.08f

#define LETTER_SIZE 0.1f
#define NUMBER_SIZE 0.1f

#define  LOG_SHARED_DATA_TAG    "SharedData"
#define  LOG_SHARED_DATA_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_SHARED_DATA_TAG,__VA_ARGS__)

using std::string;
using std::stringstream;
template <class kind>
string a2s(kind t)
{
    stringstream i2;
    string i;
    i2<<t;
    i2>>i;
    return i;
}

template <class kind>
kind s2a(string t)
{
    stringstream i2;
    kind i;
    i2<<t;
    i2>>i;
    return i;
}

namespace SharedData
{
    void setAAssetManager(AAssetManager* assetManagerData);
    void setScreenResolution(int width, int height);
    void setTriangleShader(std::shared_ptr<TriangleShader> triangleShaderData);
    std::shared_ptr<TriangleShader> getTriangleShader();
    void setLineShader(std::shared_ptr<LineShader> lineShaderData);
    std::shared_ptr<LineShader> getLineShader();
    int getScreenWidth();
    int getScreenHeight();
    void setTouchMovement(bool isMovingData, float xMovementData, float yMovementData); //depricated
    void setTouchPosition(float xTouchPositionData, float yTouchPositionData);
    void setTouchStatus(bool isTouchingData);
    bool getTouchingStatus();
    float getXTouchPosition();
    float getYTouchPosition();

    bool getMovementStatus(); //depricated
    void setProjectionMatrix(glm::mat4 projectionMatrixData);
    void setViewMatrix(glm::mat4 viewMatrixData);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    std::string getContentOfAssetFile(const char* fileName);
    void checkGLError(const char* tag, const char* error_message);
    void logInfo(const char* tag, const char* message);
}

#endif //GAME_SHAREDDATA_H