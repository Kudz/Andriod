//
// Created by kamil7 on 2017-03-28.
//

#ifndef GAME_TRIANGLE_SHADER_H
#define GAME_TRIANGLE_SHADER_H

#include <iostream>
#include <GLES2/gl2.h>

#include "Shaders.h"

#define  LOG_TRIANGLE_SHADER_TAG    "shader"
#define  LOG_TRIANGLE_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TRIANGLE_SHADER_TAG,__VA_ARGS__)

class TriangleShader
{
    public:
        TriangleShader();
        TriangleShader(std::string vertexShader, std::string fragmentShader);
        ~TriangleShader();
        GLuint getProgramID(int part);
    private:
        GLuint ShaderIds[3];
        void compileProgram(std::string vertexShader, std::string fragmentShader);
//        GLuint loadShader(GLenum shaderType, const char* pSource);
};


#endif //GAME_SHADER_H
