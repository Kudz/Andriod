//
// Created by kamil7 on 2017-03-30.
//

#ifndef GAME_BRICKSMASHER_H
#define GAME_BRICKSMASHER_H

#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <memory>

#include "TriangleShader.h"

#define  LOG_TAG    "CppToJava"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace CppToJava
{
    extern "C"
    {
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr);
    }
};


#endif //GAME_BRICKSMASHER_H
