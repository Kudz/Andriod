//
// Created by kamil7 on 2017-04-07.
//

#ifndef GAME_TRIANGLEMODELINTERFACE_H
#define GAME_TRIANGLEMODELINTERFACE_H

#include "glm/glm.hpp" //vec3, vec4, ivec4, mat4
#include "glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective
#include "glm/gtc/type_ptr.hpp" // value_ptr
#include "glm/ext.hpp" //to_string

class ModelInterface {
public:
    virtual glm::vec4 getColourVector() = 0; //return colourVector
    virtual void setColourVector(float red, float green, float blue, float alpha) = 0;
    virtual glm::mat4 getModelMatrix() = 0;
    virtual std::string getDrawingName() = 0;
    virtual void setVisibility(bool value) = 0;
    virtual bool getVisibility() = 0;
protected:
    glm::mat4 _modelMatrix; //home position is at identity matrix
    glm::vec4 _colour;
    std::string _triangleDrawingName;
    bool _isVisible;
};


#endif //GAME_TRIANGLEMODELINTERFACE_H
