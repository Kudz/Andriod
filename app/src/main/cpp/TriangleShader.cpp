//
// Created by kamil7 on 2017-03-28.
//

#include "TriangleShader.h"

TriangleShader::TriangleShader()
{
//    this->compileProgram();
}

TriangleShader::TriangleShader(std::string vertexShader, std::string fragmentShader)
{
    this->compileProgram(vertexShader, fragmentShader);
}

void TriangleShader::compileProgram(std::string vertexShader, std::string fragmentShader)
{
    this->ShaderIds[0] = glCreateProgram();
    DisplayGLError("ERROR: Could not create the shader program");
    this->ShaderIds[1] = LoadShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());
    this->ShaderIds[2] = LoadShader(GL_VERTEX_SHADER, vertexShader.c_str());
    glAttachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glLinkProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not link the shader program");
}

GLuint TriangleShader::getProgramID(int part)
{
    return this->ShaderIds[part];
}

TriangleShader::~TriangleShader()
{
    glDetachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glDetachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glDeleteShader(this->ShaderIds[1]);
    glDeleteShader(this->ShaderIds[2]);
    glDeleteProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not destroy the shaders");
}
