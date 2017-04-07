//
// Created by kamil7 on 2017-04-07.
//

#ifndef GAME_TRIANGLEMODELINTERFACE_H
#define GAME_TRIANGLEMODELINTERFACE_H

#include "glm/glm.hpp" //vec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

class TriangleModelInterface {
    virtual glm::vec4 getColourVector() = 0; //return colourVector
    virtual glm::vec4 getModelMatrix() = 0;
    virtual std::string getTriangleDrawingName() = 0;
};


#endif //GAME_TRIANGLEMODELINTERFACE_H
