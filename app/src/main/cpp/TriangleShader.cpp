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
//    LOG_TRIANGLE_SHADER_I("ProgramID = %d",  this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not create the shader program");

    this->ShaderIds[1] = loadShader2(GL_FRAGMENT_SHADER, fragmentShader.c_str());
//    LOG_TRIANGLE_SHADER_I("FragmentShaderID = %d",  this->ShaderIds[1]);
//    GLint compiled = 0;
//    glGetShaderiv(this->ShaderIds[1], GL_COMPILE_STATUS, &compiled);
//    LOG_TRIANGLE_SHADER_I("Fragment Shader compilation status = %d",  compiled);
    this->ShaderIds[2] = loadShader2(GL_VERTEX_SHADER, vertexShader.c_str());
//    LOG_TRIANGLE_SHADER_I("VertexShaderID = %d",  this->ShaderIds[2]);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glAttachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glLinkProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not link the shader program");
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->ShaderIds[0], GL_LINK_STATUS, &linkStatus);
    LOG_TRIANGLE_SHADER_I("Link Status = %d",  linkStatus);
}

GLuint TriangleShader::getProgramID(int part)
{
    return this->ShaderIds[part];
}

TriangleShader::~TriangleShader()
{
    LOG_TRIANGLE_SHADER_I("TriangleShader destructor");
    glDetachShader(this->ShaderIds[0], this->ShaderIds[1]);
    glDetachShader(this->ShaderIds[0], this->ShaderIds[2]);
    glDeleteShader(this->ShaderIds[1]);
    glDeleteShader(this->ShaderIds[2]);
    glDeleteProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not destroy the shaders");
}
