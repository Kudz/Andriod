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
#include "ModelDescriptionInterface.h"
#include "ModelInterface.h"

#define  LOG_TRIANGLE_DRAWING_TAG    "TriangleDrawing"

class TriangleDrawing
{
public:
    TriangleDrawing();
    TriangleDrawing(ModelDescriptionInterface& triangleDescriptionObject);
    ~TriangleDrawing();
    void draw(std::shared_ptr<ModelInterface> triangleModelObject);
private:
    //drawing stuff
    GLfloat* Vertices;
    GLuint _buffer;
    int VertexNumber;
    void CreateBuffers();
};


#endif //GAME_TRIANGLEDRAWING_H
