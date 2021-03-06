//
// Created by kamil7 on 2017-03-31.
//

#include "SharedData.h"

namespace SharedData
{
    namespace
    {
        AAssetManager* assetManager;
        int screenWidth = 0;
        int screenHeight = 0;

        //depricated
        bool isMoving = false;
        float xMovement = 0.0f;
        float yMovement = 0.0f;

        float xTouchPosition = 0.0f;
        float yTouchPosition = 0.0f;
        bool isTouching = false;

        std::shared_ptr<TriangleShader> triangleShader;
        std::shared_ptr<LineShader> lineShader;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
    }

    void setAAssetManager(AAssetManager* assetManagerData)
    {
        assetManager = assetManagerData;
    }

    void setScreenResolution(int width, int height)
    {
        LOG_SHARED_DATA_I("initializing width = %d\n", width);
        LOG_SHARED_DATA_I("initializing height = %d\n", height);
        screenWidth = width;
        screenHeight = height;
//        projectionMatrix = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.0f, 5.0f);
//        viewMatrix = glm::mat4(1.0f);
//        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, 2.0f));
        float ratio = (float)height/(float)width;
        projectionMatrix = glm::ortho(-1.0f, 1.0f, -ratio, ratio, -1.0f, 1.0f);
        viewMatrix = glm::mat4(1.0f);
//        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -2.0f));
//        projectionMatrix = glm::mat4(1.0f);
//        viewMatrix = glm::mat4(1.0f);
    }

    void setTriangleShader(std::shared_ptr<TriangleShader> triangleShaderData)
    {
//        LOG_SHARED_DATA_I("setTriangleShader beginning");
        triangleShader = std::move(triangleShaderData);
//        LOG_SHARED_DATA_I("setTriangleShader ending");
    }

    std::shared_ptr<TriangleShader> getTriangleShader()
    {
        return triangleShader;
    }

    void setLineShader(std::shared_ptr<LineShader> lineShaderData)
    {
        lineShader = std::move(lineShaderData);
    }

    std::shared_ptr<LineShader> getLineShader()
    {
        return lineShader;
    }

    void setTouchPosition(float xTouchPositionData, float yTouchPositionData)
    {
        xTouchPosition = xTouchPositionData;
        yTouchPosition = yTouchPositionData;
    }

    void setTouchStatus(bool isTouchingData)
    {
        isTouching = isTouchingData;
    }

    void setTouchMovement(bool isMovingData, float xMovementData, float yMovementData)
    {
//        LOG_SHARED_DATA_I("setTouchMovement xMovementData = %f", xMovementData);
        isMoving = isMovingData;
        xMovement = xMovementData;
        yMovement = yMovementData;
    }

    float getXTouchPosition()
    {
        return xTouchPosition;
//        return xMovement;
    }

    float getYTouchPosition()
    {
//        return yMovement;
        return yTouchPosition;
    }

    bool getTouchingStatus()
    {
        return isTouching;
    }

    bool getMovementStatus()
    {
        return isMoving;
    }

    void setProjectionMatrix(glm::mat4 projectionMatrixData)
    {
        projectionMatrix = projectionMatrixData;
    }

    void setViewMatrix(glm::mat4 viewMatrixData)
    {
        viewMatrix = viewMatrixData;
    }

    glm::mat4 getProjectionMatrix()
    {
        return projectionMatrix;
    }

    glm::mat4 getViewMatrix()
    {
        return viewMatrix;
    }

    int getScreenWidth()
    {
        return screenWidth;
    }

    int getScreenHeight()
    {
        return screenHeight;
    }

    std::string getContentOfAssetFile(const char* fileName)
    {
        if(assetManager == nullptr)
        {
            LOG_SHARED_DATA_I("assetManager not founded");
            return std::string();
        }
        AAsset* assetFile = AAssetManager_open(assetManager, fileName, AASSET_MODE_BUFFER );
        if (assetFile == nullptr) {
            LOG_SHARED_DATA_I("assetFile not founded");
            return std::string();
        }

        char* assetBuff = (char*) AAsset_getBuffer(assetFile);
        std::istringstream iss(assetBuff);
        std:string fromStream = iss.str();
        iss.clear();
        assetBuff = nullptr;

        AAsset_close(assetFile);

//        LOG_SHARED_DATA_I("stringStream :");
//        logInfo(LOG_SHARED_DATA_TAG, fromStream.c_str());

        return fromStream;
    }

    void checkGLError(const char* tag, const char* error_message)
    {
        for (GLint error = glGetError(); error; error = glGetError())
        {
            __android_log_print(ANDROID_LOG_ERROR, tag, "after %s() glError (%d)\n", error_message, error);
//            LOG_SHADER_I("in %s after %s() glError (0x%x)\n", tag, error_message, error);
        }
    }

    void logInfo(const char* tag, const char* message)
    {
        __android_log_print(ANDROID_LOG_INFO, tag, "%s\n", message);
    }
}