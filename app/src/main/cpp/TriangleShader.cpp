//
// Created by kamil7 on 2017-03-28.
//

#include "TriangleShader.h"

//TriangleShader::TriangleShader()
//{
////    this->compileProgram();
//}

TriangleShader::TriangleShader(std::string vertexShader, std::string fragmentShader)
: _vertexShaderCharArray("attribute vec4 vPosition;\n"
                                 "uniform mat4 P;\n"
                                 "uniform mat4 V;\n"
                                 "uniform mat4 M;\n"
                                 "uniform vec4 vertColor;\n"
                                 "varying vec4 col;\n"
                                 "void main(){\n"
                                 "gl_Position = P * V * M * vPosition;\n"
                                 "col = vertColor;\n"
                                 "}\n"), _fragmentShaderCharArray("precision mediump float;\n"
                                                                            "varying vec4 col;\n"
                                                                            "void main(){\n"
                                                                            "gl_FragColor = col;\n"
                                                                            "}\n")
{
    this->_vertexShaderString = vertexShader;
    this->_fragmentShaderString = fragmentShader;
    this->compileProgram();
    this->setShaderParameters();
}

void TriangleShader::compileProgram()
{
    this->_programID = glCreateProgram();
    DisplayGLError("ERROR: Could not create the shader program");

    this->_vertexShader = loadShader(GL_VERTEX_SHADER, this->_vertexShaderCharArray);
    this->_fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->_fragmentShaderCharArray);
//    this->_vertexShader = loadShader(GL_VERTEX_SHADER, this->_vertexShaderString.c_str());
//    this->_fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->_fragmentShaderString.c_str());
    glAttachShader(this->_programID, this->_vertexShader);
    glAttachShader(this->_programID, this->_fragmentShader);
    glLinkProgram(this->_programID);
    DisplayGLError("ERROR: Could not link the shader program");
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkStatus);
    LOG_TRIANGLE_SHADER_I("Link Status = %d",  linkStatus);
}

void TriangleShader::setShaderParameters()
{
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->getProgramID(), GL_LINK_STATUS, &linkStatus);
    if(!linkStatus)
    {
        this->checkCompilationStatus();
    }

    _projectionMatrixUniformLocation = glGetUniformLocation(this->_programID, "P");
    _viewMatrixUniformLocation = glGetUniformLocation(this->_programID, "V");
    _modelMatrixUniformLocation = glGetUniformLocation(this->_programID, "M");
    _colourVectorUniformLocation = glGetUniformLocation(this->_programID, "vertColor");
    DisplayGLError("ERROR: Could not get the shader uniform locations");
    _vertexPositionAttributeLocation = glGetAttribLocation(this->_programID, "vPosition");
    DisplayGLError("ERROR: Could not get the shader attribute locations");
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

void TriangleShader::checkCompilationStatus()
{
    GLint vertexCompilationStatus = 0;
    glGetShaderiv(this->_vertexShader, GL_COMPILE_STATUS, &vertexCompilationStatus);
    GLint fragmentCompilationStatus = 0;
    glGetShaderiv(this->_vertexShader, GL_COMPILE_STATUS, &fragmentCompilationStatus);
    if(vertexCompilationStatus == 0 && fragmentCompilationStatus == 0)
    {
        LOG_TRIANGLE_SHADER_I("Shaders are not compiled");
        this->_vertexShader = loadShader(GL_VERTEX_SHADER, this->_vertexShaderCharArray);
        this->_fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->_fragmentShaderCharArray);
//        this->_vertexShader = loadShader(GL_VERTEX_SHADER, this->_vertexShaderString.c_str());
//        this->_fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->_fragmentShaderString.c_str());
    }

    GLint linkProgramStatus = GL_FALSE;
    glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkProgramStatus);
    if(linkProgramStatus == 0)
    {
        this->_programID = glCreateProgram();
        DisplayGLError("ERROR: Could not create the shader program");
        LOG_TRIANGLE_SHADER_I("program is not linked");
        glAttachShader(this->_programID, this->_vertexShader);
        glAttachShader(this->_programID, this->_fragmentShader);
        glLinkProgram(this->_programID);
//        DisplayGLError("ERROR: Could not link the shader program");
//        LOG_TRIANGLE_SHADER_I("ProgramID = %d",  this->_programID);
//        glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkProgramStatus);
//        LOG_TRIANGLE_SHADER_I("Link Status = %d",  linkProgramStatus);
        this->setShaderParameters();
    }
}

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