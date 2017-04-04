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
        std::shared_ptr<TriangleShader> triangleShader;
    }

    void setAAssetManager(AAssetManager* assetManagerData)
    {
        assetManager = assetManagerData;
    }

    void setScreenResolution(int width, int height)
    {
        LOG_SHARED_DATA_I("initializing width = %l\n", width);
        screenWidth = width;
        screenHeight= height;
    }

    void setTriangleShader(std::shared_ptr<TriangleShader> triangleShaderData)
    {
        triangleShader = triangleShaderData;
    }

    std::shared_ptr<TriangleShader> getTriangleShader()
    {
        return triangleShader;
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
        AAsset* assetFile = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
        if (assetFile == nullptr) {
            LOG_SHARED_DATA_I("assetFile not founded");
            return std::string();
        }
        long size = AAsset_getLength(assetFile);
        char* buffer = (char*) malloc (sizeof(char)*size);
        AAsset_read (assetFile, buffer, size);
        AAsset_close(assetFile);
        std::string result(buffer);
        free(buffer);

        return result;
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