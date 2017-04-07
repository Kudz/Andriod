//
// Created by kamil7 on 2017-03-28.
//

#include "TriangleShader.h"

//TriangleShader::TriangleShader()
//{
////    this->compileProgram();
//}

TriangleShader::TriangleShader(std::string vertexShader, std::string fragmentShader)
{
    this->compileProgram(vertexShader, fragmentShader);
    this->setShaderParameters();
}

void TriangleShader::compileProgram(std::string vertexShader, std::string fragmentShader)
{
    this->_programID = glCreateProgram();
//    this->ShaderIds[0] = glCreateProgram();
    DisplayGLError("ERROR: Could not create the shader program");

    this->_vertexShader = loadShader2(GL_VERTEX_SHADER, vertexShader.c_str());
    this->_fragmentShader = loadShader2(GL_FRAGMENT_SHADER, fragmentShader.c_str());
    glAttachShader(this->_programID, this->_vertexShader);
    glAttachShader(this->_programID, this->_fragmentShader);
    glLinkProgram(this->_programID);
//    this->ShaderIds[1] = loadShader2(GL_FRAGMENT_SHADER, fragmentShader.c_str());
//    this->ShaderIds[2] = loadShader2(GL_VERTEX_SHADER, vertexShader.c_str());
//    glAttachShader(this->ShaderIds[0], this->ShaderIds[1]);
//    glAttachShader(this->ShaderIds[0], this->ShaderIds[2]);
//    glLinkProgram(this->ShaderIds[0]);
    DisplayGLError("ERROR: Could not link the shader program");
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkStatus);
//    glGetProgramiv(this->ShaderIds[0], GL_LINK_STATUS, &linkStatus);
    LOG_TRIANGLE_SHADER_I("Link Status = %d",  linkStatus);
}

void TriangleShader::setShaderParameters()
{
    _projectionMatrixUniformLocation = glGetUniformLocation(this->_programID, "P");
    _viewMatrixUniformLocation = glGetUniformLocation(this->_programID, "V");
    _modelMatrixUniformLocation = glGetUniformLocation(this->_programID, "M");
    _colourVectorUniformLocation = glGetUniformLocation(this->_programID, "vertColor");
    DisplayGLError("ERROR: Could not get the shader uniform locations");
    _vertexPositionAttributeLocation = glGetAttribLocation(this->_programID, "vPosition");
    DisplayGLError("ERROR: Could not get the shader attribute locations");
}

GLuint TriangleShader::getProgramID(int part)
{
    return this->ShaderIds[part];
}

GLuint TriangleShader::getProgramID()
{
    return this->_programID;
}

GLuint TriangleShader::getProjectionMatrixUniformLocation()
{
    return this->_projectionMatrixUniformLocation;
}

GLuint TriangleShader::getViewMatrixUniformLocation()
{
    return this->_viewMatrixUniformLocation;
}

GLuint TriangleShader::getModelMatrixUniformLocation()
{
    return this->_modelMatrixUniformLocation;
}

GLuint TriangleShader::getColourVectorUniformLocation()
{
    return this->_colourVectorUniformLocation;
}

GLuint TriangleShader::getVertexPositionAttributeLocation()
{
    return this->_vertexPositionAttributeLocation;
}

//TriangleShader::~TriangleShader()
//{
//    LOG_TRIANGLE_SHADER_I("TriangleShader destructor");
//    glDetachShader(this->ShaderIds[0], this->ShaderIds[1]);
//    glDetachShader(this->ShaderIds[0], this->ShaderIds[2]);
//    glDeleteShader(this->ShaderIds[1]);
//    glDeleteShader(this->ShaderIds[2]);
//    glDeleteProgram(this->ShaderIds[0]);
//    DisplayGLError("ERROR: Could not destroy the shaders");
//}

namespace  TriangleShaderNamespace {
    void freeBuffers(TriangleShader *triangleShaderData) {
        //it seems that when new onSurfaceCreated is called there is not possible to detach shaders
        LOG_TRIANGLE_SHADER_I("TriangleShader destructor");
//        glDetachShader(triangleShaderData->getProgramID(0), triangleShaderData->getProgramID(1));
//        glDetachShader(triangleShaderData->getProgramID(0), triangleShaderData->getProgramID(2));
//        glDeleteShader(triangleShaderData->getProgramID(1));
//        glDeleteShader(triangleShaderData->getProgramID(2));
//        glDeleteProgram(triangleShaderData->getProgramID(0));
        DisplayGLError("ERROR: Could not destroy the shaders");
    }
}