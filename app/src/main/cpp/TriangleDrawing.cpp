//
// Created by kamil7 on 2017-04-04.
//

#include "TriangleDrawing.h"

TriangleDrawing::TriangleDrawing()
{
    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, "TriangleDrawing() won't work, there is a lot of things to activate");
}
//numberOfVertices - amount of vertex
TriangleDrawing::TriangleDrawing(GLuint programID, std::shared_ptr<TriangleObjectInterface> drawingObject, int frequency, int mode)
{
//  std::cout<<"number of vertices = "<<numberOfVertices<<std::endl;
    this->ProgramID = programID;
    this->_drawingObject = drawingObject;
    std::vector<double> vertices = this->_drawingObject->getDrawingPoints();
    this->VertexNumber = vertices.size()/3;
    this->Vertices = new GLfloat[this->VertexNumber*3];
    this->BuffersFrequency = frequency;
    this->_drawingMode = mode;
    for(int i = 0; i < this->VertexNumber*3; i++)
    {
        this->Vertices[i] = vertices.at(i);
    }
    this->_glmM = glm::mat4(1.0f);
    this->ColourVector = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    this->CreateBuffers();
//  std::cout<<"end of DrawingBase::DrawingBase"<<std::endl;
}
void TriangleDrawing::CreateBuffers()
{
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &linkStatus);
    std::string message = "Link Status = " + a2s<GLint>(linkStatus);
    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, message.c_str());

    ProjectionMatrixUniformLocation = glGetUniformLocation(this->ProgramID, "P"); //move to program
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not get projection uniform location");
    ViewMatrixUniformLocation = glGetUniformLocation(this->ProgramID, "V");
    ModelMatrixUniformLocation = glGetUniformLocation(this->ProgramID, "M");
    ColourVectorUniformLocation = glGetUniformLocation(this->ProgramID, "vertColor");
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not get the shader uniform locations");
    glGenBuffers(1, &this->_buffer);
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not generate the buffer objects");
    glBindBuffer(GL_ARRAY_BUFFER, this->_buffer); ///GL_ARRAY_BUFFER, which signifies that the data provided contains vertex attributes

    switch(this->BuffersFrequency)
    {
        case 1:
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->VertexNumber*3, this->Vertices, GL_DYNAMIC_DRAW);
            break;
        case 2:
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->VertexNumber*3, this->Vertices, GL_STREAM_DRAW);
            break;
        default:
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->VertexNumber*3, this->Vertices, GL_STATIC_DRAW);
    }
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

void TriangleDrawing::setColour(float red, float green, float blue, float alpha)
{
    this->ColourVector[0] = red;
    this->ColourVector[1] = green;
    this->ColourVector[2] = blue;
    this->ColourVector[3] = alpha;
}

void TriangleDrawing::draw(glm::mat4* per, glm::mat4* vis)
{
//  std::cout<<"DrawingBase::draw begining"<<std::endl;
//  std::cout<<"this->ProgramID = "<<this->ProgramID<<std::endl;
    std::string message = "ProgramID = " + a2s<int>(this->ProgramID);
    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, message.c_str());
    glUseProgram(this->ProgramID);
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not use the shader program");

//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, glm::to_string(*per).c_str());
    glUniformMatrix4fv(this->ProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(*per));
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not set the projection uniform matrix");

//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, glm::to_string(*vis).c_str());
    glUniformMatrix4fv(this->ViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(*vis));

//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, glm::to_string(this->_glmM).c_str());
    glUniformMatrix4fv(this->ModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->_glmM));

//    SharedData::logInfo(LOG_TRIANGLE_DRAWING_TAG, glm::to_string(this->ColourVector).c_str());
    glUniform4fv(this->ColourVectorUniformLocation, 1, glm::value_ptr(this->ColourVector));
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR: Could not set the shader uniforms");
//  std::cout<<"this->BufferIds[0] = "<<this->BufferIds[0]<<std::endl;
    if(this->BuffersFrequency > 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->_buffer);
        glBufferSubData(GL_ARRAY_BUFFER,  0,  sizeof(GLfloat)*this->VertexNumber*3,  this->Vertices);
    }
    glDrawArrays(GL_TRIANGLES, 0, this->VertexNumber);
//  glDrawElements(GL_LINES, this->VertexNumber, GL_UNSIGNED_INT, (GLvoid*)0);
    SharedData::checkGLError(LOG_TRIANGLE_DRAWING_TAG, "ERROR:  Could not draw object");
    glUseProgram(0);
}

void TriangleDrawing::updateVertices()
{
    std::vector<double> vertices = this->_drawingObject->getDrawingPoints();
    for(int i = 0; i < this->VertexNumber*3; i++)
    {
        this->Vertices[i] = vertices.at(i);
    }
}