//
// Created by kamil7 on 2017-04-08.
//

#ifndef GAME_LINESHADER_H
#define GAME_LINESHADER_H

#include <iostream>
#include <GLES2/gl2.h>

#include "Shaders.h"

#define  LOG_LINE_SHADER_TAG    "LineShader"
#define  LOG_LINE_SHADER_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_LINE_SHADER_TAG,__VA_ARGS__)

class LineShader
{
public:
    LineShader(std::string vertexShader, std::string fragmentShader);
    ~LineShader();
    GLuint getProgramID();
    GLuint getProjectionMatrixUniformLocation();
    GLuint getViewMatrixUniformLocation();
    GLuint getModelMatrixUniformLocation();
    GLuint getColourVectorUniformLocation();
    GLuint getVertexPositionAttributeLocation();
    void checkCompilationStatus();
private:
    GLuint _programID;
    GLuint _vertexShader;
    GLuint _fragmentShader;
    std::string _vertexShaderString;
    std::string _fragmentShaderString;
    const char* _vertexShaderCharArray;
    const char* _fragmentShaderCharArray;
    void compileProgram();

    GLuint _projectionMatrixUniformLocation;
    GLuint _viewMatrixUniformLocation;
    GLuint _modelMatrixUniformLocation;
    GLuint _colourVectorUniformLocation;
    GLuint _vertexPositionAttributeLocation;
    void setShaderParameters();
};

namespace LineShaderNamespace
{
    void freeBuffers(LineShader* lineShaderData);
}


#endif //GAME_LINESHADER_H
