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

#include "GameScene.h"
#include "TriangleShader.h"
#include "SharedData.h"

#define  LOG_CPP_TO_JAVA_TAG    "CppToJava"
#define  LOG_CPP_TO_JAVA_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_CPP_TO_JAVA_TAG,__VA_ARGS__)
#define  LOG_CPP_TO_JAVA_E(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_CPP_TO_JAVA_TAG,__VA_ARGS__)

namespace CppToJava
{
    extern "C"
    {
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeScene(JNIEnv *env, jobject instance, jint width, jint height);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_makeStep(JNIEnv *env, jobject instance);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_cleanScene(JNIEnv *env, jobject instance);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeShader(JNIEnv *env, jobject instance);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_setTouchMovement(JNIEnv * env, jobject obj,  jfloat xDifference, jfloat yDifference);
        JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeMatrices(JNIEnv *env, jobject instance);
    }
};


#endif //GAME_BRICKSMASHER_H
