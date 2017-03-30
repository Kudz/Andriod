//
// Created by kamil7 on 2017-03-30.
//

#include "CppToJavaWrapper.h"

namespace CppToJava
{
    namespace
    {
        AAssetManager* assetManager;
        TriangleShader* triangleShader;
        int screenWidth;
        int screenHeight;
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr)
    {
        assetManager = AAssetManager_fromJava(env, mgr);
        if (assetManager == nullptr) {
            LOGI("assetManager == nullptr");
        }
        else
        {
            LOGI("assetManager != nullptr");
        }
    }
}