//
// Created by kamil7 on 2017-03-29.
//

#ifndef GAME_SHADER_H
#define GAME_SHADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GLES2/gl2.h>

#include <android/log.h>

#define  LOG_SHADER_TAG    "shader"
#define  LOG_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_SHADER_TAG,__VA_ARGS__)
#define  LOG_SHADER_E(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_SHADER_TAG,__VA_ARGS__)

GLuint LoadShader(std::string filename, GLenum shader_type);
GLuint LoadShader(GLenum shaderType, const char* text);
void DisplayGLError(const char* error_message);

#endif //GAME_SHADER_H
