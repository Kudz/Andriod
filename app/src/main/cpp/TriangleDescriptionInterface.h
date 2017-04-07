//
// Created by kamil7 on 2017-04-04.
//

#ifndef GAME_TRIANGLEOBJECTINTERFACE_H
#define GAME_TRIANGLEOBJECTINTERFACE_H

#include <iostream>
#include <vector>

class TriangleDescriptionInterface
{
public:
    virtual std::vector<double> getDrawingPoints() = 0; //return drawing points for OpenGL
};


#endif //GAME_TRIANGLEOBJECTINTERFACE_H
