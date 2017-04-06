//
// Created by kamil7 on 2017-04-04.
//

#ifndef GAME_TRIANGLEDRAWING_H
#define GAME_TRIANGLEDRAWING_H

#include "glm/glm.hpp" //vec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

#include <GLES2/gl2.h>
#include <memory>

#include "SharedData.h"
#include "TriangleObjectInterface.h"

#define  LOG_TRIANGLE_DRAWING_TAG    "TriangleDrawing"

class TriangleDrawing
{
public:
    TriangleDrawing();
    TriangleDrawing(GLuint programID, std::shared_ptr<TriangleObjectInterface> drawingObject, int frequency = 0, int mode = 0);
    ~TriangleDrawing();
    TriangleDrawing( const TriangleDrawing &obj); //copy constructor
    void setColour(float red, float green, float blue, float alpha);
    void draw(glm::mat4* per, glm::mat4* vis);
    //~ void updateVertices(GLfloat* vertices); //depreciated
    void updateVertices();
private:
    //drawing stuff
    GLfloat* Vertices;
    std::shared_ptr<TriangleObjectInterface> _drawingObject;
    GLuint ProjectionMatrixUniformLocation;
    GLuint ViewMatrixUniformLocation;
    GLuint ModelMatrixUniformLocation;
    GLuint ColourVectorUniformLocation;
    GLuint _vertexPositionAttributeLocation;
    GLuint _buffer;
    int VertexNumber;
    GLuint ProgramID;
    glm::mat4 _glmM; // drawing purpose
    glm::vec4 ColourVector;
    int BuffersFrequency; // 0 - Static, 1 - Dynamic, 2 - Stream
    int _drawingMode; // 0 - GL_LINES, 1 - GL_POINTS; not used yet
    void CreateBuffers();
};


#endif //GAME_TRIANGLEDRAWING_H
