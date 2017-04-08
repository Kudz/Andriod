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

        //making Scene
//        gameScene = std::shared_ptr<GameScene>(new GameScene);
        gameScene = std::move(std::shared_ptr<GameScene>(new GameScene));
        LOG_CPP_TO_JAVA_I("scene initializing complete");
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_makeStep(JNIEnv *env, jobject instance)
    {
        gameScene->render();
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_cleanScene(JNIEnv *env, jobject instance)
    {

    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeShader(JNIEnv *env, jobject instance)
    {
        std::string message = "use count = " + a2s<int>(SharedData::getTriangleShader().use_count());
        SharedData::logInfo(LOG_CPP_TO_JAVA_TAG, message.c_str());

        // making triangle shaders
        int useCunter = SharedData::getTriangleShader().use_count();
        if(useCunter)
        {
            SharedData::setTriangleShader(nullptr);
        }
        std::string vertexShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_v");
        std::string fragmentShader = SharedData::getContentOfAssetFile("Shaders/triangle_shader_f");
//        std::unique_ptr<TriangleShader> triangleShader(new TriangleShader(vertexShader, fragmentShader));
        std::shared_ptr<TriangleShader> triangleShader(new TriangleShader(vertexShader, fragmentShader), TriangleShaderNamespace::freeBuffers);
        SharedData::setTriangleShader(triangleShader);

        // making line shaders
        useCunter = SharedData::getLineShader().use_count();
        if(useCunter)
        {
            SharedData::setLineShader(nullptr);
        }
        vertexShader = SharedData::getContentOfAssetFile("Shaders/line_shader_v");
        fragmentShader = SharedData::getContentOfAssetFile("Shaders/line_shader_f");
        std::shared_ptr<LineShader> lineShader(new LineShader(vertexShader, fragmentShader), LineShaderNamespace::freeBuffers);
        SharedData::setLineShader(lineShader);

        SharedData::logInfo(LOG_CPP_TO_JAVA_TAG, "end of initialization");
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_setTouchMovement(JNIEnv * env, jobject obj, jboolean isMoving, jfloat xPosition, jfloat yPosition)
    {
//        std::string message = "xDifference = " + a2s<float>(xPosition);
//        SharedData::logInfo(LOG_CPP_TO_JAVA_TAG, message.c_str());
//        message = "ScreenWidth = " + a2s<float>((float)SharedData::getScreenWidth());
//        SharedData::logInfo(LOG_CPP_TO_JAVA_TAG, message.c_str());
//        float xChange = xDifference*2/(float)SharedData::getScreenWidth();
//        float yChange = yDifference*2/(float)SharedData::getScreenHeight();
//        message = "xChange = " + a2s<float>(xChange);
//        SharedData::logInfo(LOG_CPP_TO_JAVA_TAG, message.c_str());
//        SharedData::setTouchMovement(isMoving, xChange, yChange);
        SharedData::setTouchMovement(isMoving, xPosition, yPosition);
    }

    JNIEXPORT void JNICALL Java_kuklinski_kamil_game_JavaToCppWrapper_initializeMatrices(JNIEnv *env, jobject instance)
    {
        SharedData::setProjectionMatrix(glm::mat4(1.0f));
        SharedData::setViewMatrix(glm::mat4(1.0f));
    }
}
