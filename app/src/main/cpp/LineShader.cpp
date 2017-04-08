//
// Created by kamil7 on 2017-04-08.
//

#include "LineShader.h"

LineShader::LineShader(std::string vertexShader, std::string fragmentShader)
{
    this->compileProgram(vertexShader, fragmentShader);
    this->setShaderParameters();
}

void LineShader::compileProgram(std::string vertexShader, std::string fragmentShader)
{
    this->_programID = glCreateProgram();
    DisplayGLError("ERROR: Could not create the shader program");

    this->_vertexShader = loadShader2(GL_VERTEX_SHADER, vertexShader.c_str());
    this->_fragmentShader = loadShader2(GL_FRAGMENT_SHADER, fragmentShader.c_str());
    glAttachShader(this->_programID, this->_vertexShader);
    glAttachShader(this->_programID, this->_fragmentShader);
    glLinkProgram(this->_programID);
    DisplayGLError("ERROR: Could not link the shader program");
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkStatus);
    LOG_LINE_SHADER_I("Link Status = %d",  linkStatus);
}

void LineShader::setShaderParameters()
{
    _projectionMatrixUniformLocation = glGetUniformLocation(this->_programID, "P");
    _viewMatrixUniformLocation = glGetUniformLocation(this->_programID, "V");
    _modelMatrixUniformLocation = glGetUniformLocation(this->_programID, "M");
    _colourVectorUniformLocation = glGetUniformLocation(this->_programID, "vertColor");
    DisplayGLError("ERROR: Could not get the shader uniform locations");
    _vertexPositionAttributeLocation = glGetAttribLocation(this->_programID, "vPosition");
    DisplayGLError("ERROR: Could not get the shader attribute locations");
}

GLuint LineShader::getProgramID(int part)
{
    return this->ShaderIds[part];
}

GLuint LineShader::getProgramID()
{
    return this->_programID;
}

GLuint LineShader::getProjectionMatrixUniformLocation()
{
    return this->_projectionMatrixUniformLocation;
}

GLuint LineShader::getViewMatrixUniformLocation()
{
    return this->_viewMatrixUniformLocation;
}

GLuint LineShader::getModelMatrixUniformLocation()
{
    return this->_modelMatrixUniformLocation;
}

GLuint LineShader::getColourVectorUniformLocation()
{
    return this->_colourVectorUniformLocation;
}

GLuint LineShader::getVertexPositionAttributeLocation()
{
    return this->_vertexPositionAttributeLocation;
}

namespace  LineShaderNamespace {
    void freeBuffers(LineShader *triangleShaderData) {
        //it seems that when new onSurfaceCreated is called there is not possible to detach shaders
        LOG_LINE_SHADER_I("TriangleShader destructor");
    }
}