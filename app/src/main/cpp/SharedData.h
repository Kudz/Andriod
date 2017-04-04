//
// Created by kamil7 on 2017-03-31.
//

#ifndef GAME_SHAREDDATA_H
#define GAME_SHAREDDATA_H

#include <iostream>
#include <sstream>
#include <memory>

#include <android/asset_manager.h>

#include "TriangleShader.h"

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
    int getScreenWidth();
    int getScreenHeight();
    std::string getContentOfAssetFile(const char* fileName);
    void checkGLError(const char* tag, const char* error_message);
    void logInfo(const char* tag, const char* message);
}

#endif //GAME_SHAREDDATA_H