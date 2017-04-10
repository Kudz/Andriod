//
// Created by kamil7 on 2017-04-04.
//

#include "TriangleDrawing.h"

TriangleDrawing::TriangleDrawing()
{
    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, "TriangleDrawing() won't work, there is a lot of things to activate");
}

TriangleDrawing::TriangleDrawing(ModelDescriptionInterface& triangleDescriptionObject)
{
    std::vector<double> vertices = triangleDescriptionObject.getDrawingPoints();
    this->VertexNumber = vertices.size()/3;
    this->Vertices = new GLfloat[this->VertexNumber*3];
    for(int i = 0; i < this->VertexNumber*3; i++)
    {
        this->Vertices[i] = vertices.at(i);
    }
    this->CreateBuffers();
}

void TriangleDrawing::CreateBuffers()
{
//    GLint linkStatus = GL_FALSE;
//    glGetProgramiv(SharedData::getTriangleShader()->getProgramID(), GL_LINK_STATUS, &linkStatus);
//    std::string message = "Link Status in createBuffer = " + a2s<GLint>(linkStatus);
//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, message.c_str());

    glGenBuffers(1, &this->_buffer);
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not generate the buffer objects");
    glBindBuffer(GL_ARRAY_BUFFER, this->_buffer); ///GL_ARRAY_BUFFER, which signifies that the data provided contains vertex attributes

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->VertexNumber*3, this->Vertices, GL_STATIC_DRAW);

    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not bind the VAO (Vertex Array Onject) to the VBO (Vertex Buffer Object)");
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unload buffer
}

TriangleDrawing::~TriangleDrawing()
{
    if (this->Vertices != NULL)
    {
        delete[] this->Vertices;
        this->Vertices = NULL;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->_buffer);
}

void TriangleDrawing::draw(std::shared_ptr<ModelInterface> triangleModelObject)
{
    glUseProgram(SharedData::getTriangleShader()->getProgramID());
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not use the shader program");

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(SharedData::getTriangleShader()->getProgramID(), GL_LINK_STATUS, &linkStatus);
    if(!linkStatus)
    {
        SharedData::getTriangleShader()->checkCompilationStatus();
    }
//    std::string message = "Link Status in drawing = " + a2s<GLint>(linkStatus);
//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, message.c_str());

    glUniformMatrix4fv(SharedData::getTriangleShader()->getProjectionMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(SharedData::getProjectionMatrix()));
    glUniformMatrix4fv(SharedData::getTriangleShader()->getViewMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(SharedData::getViewMatrix()));
    glUniformMatrix4fv(SharedData::getTriangleShader()->getModelMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(triangleModelObject->getModelMatrix()));
    glUniform4fv(SharedData::getTriangleShader()->getColourVectorUniformLocation(), 1, glm::value_ptr(triangleModelObject->getColourVector()));
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not set the shader uniforms");

    glBindBuffer(GL_ARRAY_BUFFER, this->_buffer);

    glVertexAttribPointer(SharedData::getTriangleShader()->getVertexPositionAttributeLocation(), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SharedData::getTriangleShader()->getVertexPositionAttributeLocation());
    glDrawArrays(GL_TRIANGLES, 0, this->VertexNumber);
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR:  Could not draw object");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}