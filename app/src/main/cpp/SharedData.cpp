//
// Created by kamil7 on 2017-03-31.
//

#include "SharedData.h"

namespace SharedData
{
    namespace
    {
        AAssetManager* assetManager;
        int screenWidth;
        int screenHeight;
//        std::unique_ptr<TriangleShader> triangleShader;
        std::shared_ptr<TriangleShader> triangleShader;
    }

    void setAAssetManager(AAssetManager* assetManagerData)
    {
        assetManager = assetManagerData;
    }

    void setScreenResolution(int width, int height)
    {
        LOG_SHARED_DATA_I("initializing width = %d\n", width);
        screenWidth = width;
        screenHeight= height;
    }

    void setTriangleShader(std::shared_ptr<TriangleShader> triangleShaderData)
    {
        LOG_SHARED_DATA_I("setTriangleShader beginning");
        triangleShader = std::move(triangleShaderData);
        LOG_SHARED_DATA_I("setTriangleShader ending");
    }

    std::shared_ptr<TriangleShader> getTriangleShader()
    {
        return triangleShader;
    }

//    void setTriangleShader(std::unique_ptr<TriangleShader> triangleShaderData)
//    {
//        LOG_SHARED_DATA_I("setTriangleShader beginning");
//        triangleShader = std::move(triangleShaderData);
////        triangleShader = triangleShaderData;
//        LOG_SHARED_DATA_I("setTriangleShader ending");
//    }
//
//    std::unique_ptr<TriangleShader> getTriangleShader()
//    {
//        return triangleShader;
//    }

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
        //old way
//        long bufferSize = AAsset_getLength(assetFile);
//        char* buffer = (char*) malloc (sizeof(char)*bufferSize);
//        AAsset_read (assetFile, buffer, bufferSize);

        //new way
        char* assetBuff = (char*) AAsset_getBuffer(assetFile);
        std::istringstream iss(assetBuff);
        std:string fromStream = iss.str();
        iss.clear();
        assetBuff = nullptr;

        AAsset_close(assetFile);

//        LOG_SHARED_DATA_I("buffer size : %d", bufferSize);
//        LOG_SHARED_DATA_I("char* : %s", buffer);
//        LOG_SHARED_DATA_I("char* : %s", buffer);
//
//        std::string result(buffer);
//
//        LOG_SHARED_DATA_I("string :");
//        logInfo(LOG_SHARED_DATA_TAG, result.c_str());

        LOG_SHARED_DATA_I("stringStream :");
        logInfo(LOG_SHARED_DATA_TAG, fromStream.c_str());

//        free(buffer);

//        return result;
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