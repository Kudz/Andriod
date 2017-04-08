//
// Created by kamil7 on 2017-04-08.
//

#include "LineDrawing.h"

LineDrawing::LineDrawing()
{
    SharedData::logInfo(LOG_LINE_DRAWING_TAG, "LineDrawing() won't work, there is a lot of things to activate");
}

LineDrawing::LineDrawing(ModelDescriptionInterface& lineDescriptionObject)
{
    std::vector<double> vertices = lineDescriptionObject.getDrawingPoints();
    this->VertexNumber = vertices.size()/3;
    this->Vertices = new GLfloat[this->VertexNumber*3];
    for(int i = 0; i < this->VertexNumber*3; i++)
    {
        this->Vertices[i] = vertices.at(i);
    }
    this->CreateBuffers();
}

void LineDrawing::CreateBuffers()
{
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(SharedData::getLineShader()->getProgramID(), GL_LINK_STATUS, &linkStatus);
    std::string message = "Link Status = " + a2s<GLint>(linkStatus);
    SharedData::logInfo(LOG_LINE_DRAWING_TAG, message.c_str());

    glGenBuffers(1, &this->_buffer);
    SharedData::checkGLError(LOG_LINE_DRAWING_TAG, "ERROR: Could not generate the buffer objects");
    glBindBuffer(GL_ARRAY_BUFFER, this->_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->VertexNumber*3, this->Vertices, GL_STATIC_DRAW);

    SharedData::checkGLError(LOG_LINE_DRAWING_TAG, "ERROR: Could not bind the VAO (Vertex Array Onject) to the VBO (Vertex Buffer Object)");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

LineDrawing::~LineDrawing()
{
    if (this->Vertices != NULL)
    {
        delete[] this->Vertices;
        this->Vertices = NULL;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->_buffer);
}

void LineDrawing::draw(std::shared_ptr<ModelInterface> lineModelObject)
{
    glUseProgram(SharedData::getLineShader()->getProgramID());
    SharedData::checkGLError(LOG_LINE_DRAWING_TAG, "ERROR: Could not use the shader program");

    glUniformMatrix4fv(SharedData::getLineShader()->getProjectionMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(SharedData::getProjectionMatrix()));
    glUniformMatrix4fv(SharedData::getLineShader()->getViewMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(SharedData::getViewMatrix()));
    glUniformMatrix4fv(SharedData::getLineShader()->getModelMatrixUniformLocation(), 1, GL_FALSE, glm::value_ptr(lineModelObject->getModelMatrix()));
    glUniform4fv(SharedData::getLineShader()->getColourVectorUniformLocation(), 1, glm::value_ptr(lineModelObject->getColourVector()));
    SharedData::checkGLError(LOG_LINE_DRAWING_TAG, "ERROR: Could not set the shader uniforms");

    glBindBuffer(GL_ARRAY_BUFFER, this->_buffer);

    glVertexAttribPointer(SharedData::getLineShader()->getVertexPositionAttributeLocation(), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(SharedData::getLineShader()->getVertexPositionAttributeLocation());
    glDrawArrays(GL_LINES, 0, this->VertexNumber);
    SharedData::checkGLError(LOG_LINE_DRAWING_TAG, "ERROR:  Could not draw object");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}