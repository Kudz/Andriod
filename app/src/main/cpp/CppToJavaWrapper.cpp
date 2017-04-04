//
// Created by kamil7 on 2017-03-30.
//

#include "CppToJavaWrapper.h"

namespace CppToJava
{
    namespace
    {
        std::shared_ptr<GameScene> gameScene;
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr)
    {
        AAssetManager* assetManager = AAssetManager_fromJava(env, mgr);
        if (assetManager == nullptr)
        {
            LOG_CPP_TO_JAVA_I("assetManager load unsuccessful");
        }
        else
        {
            LOG_CPP_TO_JAVA_I("assetManager load successful");
            SharedData::setAAssetManager(assetManager);
        }
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeScene(JNIEnv *env, jobject instance, jint width, jint height)
    {
        // setting scene resolution
        SharedData::setScreenResolution(width, height);

        // making triangle shaders
        std::string fragmentShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_fragment");
        std::string vertexShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_vertex");
        std::shared_ptr<TriangleShader> triangleShader(new TriangleShader(vertexShader, fragmentShader));
        SharedData::setTriangleShader(triangleShader);

        //making Scene
        gameScene = std::shared_ptr<GameScene>(new GameScene);
        LOG_CPP_TO_JAVA_I("scene initializing complete");
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_makeStep(JNIEnv *env, jobject instance)
    {
        gameScene->render();
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_cleanScene(JNIEnv *env, jobject instance)
    {

    }

}