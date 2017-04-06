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

#define  LOG_TAG    "libsmasher"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//AAssetManager *assMgr;

AAssetManager* assetManager;

static void printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

auto gVertexShader =
        "attribute vec4 vPosition;\n"
                "void main() {\n"
                "  gl_Position = vPosition;\n"
                "}\n";

auto gFragmentShader =
        "precision mediump float;\n"
                "void main() {\n"
                "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
                "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;
int screenWidth;
int screenHeight;

bool setupGraphics(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    LOGI("gProgram = %d\n",
         gProgram);
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

GLfloat middleX = 0.0f;

const GLfloat xOffset = 0.2f;
const GLfloat yOffset = 0.02f;

GLfloat gTriangleVertices[] = { -xOffset + middleX, yOffset, -xOffset + middleX, -yOffset, xOffset + middleX, yOffset,
                                      xOffset + middleX, -yOffset, -xOffset + middleX, -yOffset, xOffset + middleX, yOffset};

//const GLfloat gTriangleVertices[] = { -xOffset, yOffset, -xOffset, -yOffset, xOffset, yOffset,
//                                      xOffset, -yOffset, -xOffset, -yOffset, xOffset, yOffset};

void renderFrame()
{
//    static float grey = 1.0f;
//    glClearColor(grey, grey, grey, 1.0f);
//    checkGlError("glClearColor");
//    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 6);
    checkGlError("glDrawArrays");

    glUseProgram(0);
}

//kuklinski.kamil.game  SmasherCPP
// Java_kuklinski_kamil_game_SmasherCPP

extern "C" {
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_init(JNIEnv * env, jobject obj,  jint width, jint height);
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_step(JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_moveBoard(JNIEnv * env, jobject obj,  jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_assetLoad(JNIEnv *env, jobject instance, jobject mgr);
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_displayString(JNIEnv *env, jobject instance, jstring mgr);
JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_loadTriangleShader(JNIEnv *env, jobject instance);
//JNIEXPORT void JNICALL Java_kuklinski_kamil_game_IntroActivity_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr);
};

JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_moveBoard(JNIEnv * env, jobject obj,  jfloat x, jfloat y)
{
    GLfloat xChange = x/screenWidth;
//    middleX = middleX + xChange;
    for(int i = 0; i < 12; i = i + 2)
    {
        gTriangleVertices[i] = gTriangleVertices[i] + xChange;
    }

//    std::string sourceFolderPath = @res;
//    LOGI("sourceFolderPath = %s\n", sourceFolderPath.c_str());

//    LOGI("x = %d\n", x);
}

JNIEXPORT void JNICALL
Java_kuklinski_kamil_game_SmasherCPP_assetLoad(JNIEnv *env, jobject instance, jobject mgr)
//Java_kuklinski_kamil_game_IntroActivity_assetLoad(JNIEnv *env, jobject instance, jobject mgr)
{
//    assetManager = AAssetManager_fromJava(env, mgr);
//    AAssetManager *assMgr = AAssetManager_fromJava(env, mgr);
//    AAsset* asset = AAssetManager_open(assMgr, "Shaders/triangle_shader_fragment", AASSET_MODE_UNKNOWN);
//    if (NULL == asset) {
//        LOGI("asset not found");
//    }
//    else
//    {
//        LOGI("asset found");
//    }
//    long size = AAsset_getLength(asset);
//    char* buffer = (char*) malloc (sizeof(char)*size);
//    AAsset_read (asset,buffer,size);
//    LOGI("file = %s\n", buffer);
//    AAsset_close(asset);
//    free(buffer);
}

JNIEXPORT void JNICALL
Java_kuklinski_kamil_game_SmasherCPP_displayString(JNIEnv *env, jobject instance, jstring mgr)
//Java_kuklinski_kamil_game_IntroActivity_assetLoad(JNIEnv *env, jobject instance, jobject mgr)
{
//    LOGI("string = %s\n", mgr);
}

//JNIEXPORT void JNICALL Java_kuklinski_kamil_game_IntroActivity_loadAssetManager(JNIEnv *env, jobject instance, jobject mgr)
//{
//    assetManager = AAssetManager_fromJava(env, mgr);
//    AAssetManager *assMgr = AAssetManager_fromJava(env, mgr);
//    AAsset* asset = AAssetManager_open(assMgr, "Shaders/triangle_shader_fragment", AASSET_MODE_UNKNOWN);
//    if (NULL == asset) {
//        LOGI("asset not found");
//    }
//    else
//    {
//        LOGI("asset found");
//    }
//    long size = AAsset_getLength(asset);
//    char* buffer = (char*) malloc (sizeof(char)*size);
//    AAsset_read (asset,buffer,size);
//    LOGI("file = %s\n", buffer);
//    AAsset_close(asset);
//    free(buffer);
//}

JNIEXPORT void JNICALL Java_kuklinski_kamil_game_SmasherCPP_loadTriangleShader(JNIEnv *env, jobject instance)
{
//    if(assetManager == nullptr)
//    {
//        LOGI("assetManager = nullptr");
//    } else
//    {
//        LOGI("assetManager != nullptr");
//    }
//    AAsset* asset = AAssetManager_open(assetManager, "Shaders/triangle_shader_fragment", AASSET_MODE_UNKNOWN);
//    if (NULL == asset) {
//        LOGI("asset not found");
//    }
//    else
//    {
//        LOGI("asset found");
//    }
//      long size = AAsset_getLength(asset);
//      char* buffer = (char*) malloc (sizeof(char)*size);
//      AAsset_read (asset,buffer,size);
//      LOGI("file = %s\n", buffer);
//      AAsset_close(asset);
//      std::string fragmentShader(buffer);
//      free(buffer);
//
//      asset = AAssetManager_open(assetManager, "Shaders/triangle_shader_vertex", AASSET_MODE_UNKNOWN);
//      if (NULL == asset) {
//          LOGI("asset not found");
//      }
//      else
//      {
//          LOGI("asset found");
//      }
//      size = AAsset_getLength(asset);
//      buffer = (char*) malloc (sizeof(char)*size);
//      AAsset_read (asset,buffer,size);
//      LOGI("file = %s\n", buffer);
//      AAsset_close(asset);
//      std::string vertexShader(buffer);
//      free(buffer);
//
//      TriangleShader triangleShader(vertexShader, fragmentShader);

}