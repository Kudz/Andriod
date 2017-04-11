//
// Created by kamil7 on 2017-04-10.
//

#include "BrickDescription.h"

BrickDescription::BrickDescription()
{
    this->_vertexes.clear();
    float xOffset = BRICK_WIDTH/2;
    float yOffset = BRICK_HEIGHT/2;
    float zOffset = 0.0;

    this->_vertexes.push_back(-xOffset);
    this->_vertexes.push_back(yOffset);
    this->_vertexes.push_back(zOffset);

    this->_vertexes.push_back(-xOffset);
    this->_vertexes.push_back(-yOffset);
    this->_vertexes.push_back(zOffset);

    this->_vertexes.push_back(xOffset);
    this->_vertexes.push_back(yOffset);
    this->_vertexes.push_back(zOffset);

    this->_vertexes.push_back(xOffset);
    this->_vertexes.push_back(-yOffset);
    this->_vertexes.push_back(zOffset);

    this->_vertexes.push_back(-xOffset);
    this->_vertexes.push_back(-yOffset);
    this->_vertexes.push_back(zOffset);

    this->_vertexes.push_back(xOffset);
    this->_vertexes.push_back(yOffset);
    this->_vertexes.push_back(zOffset);
}

std::vector<float> BrickDescription::getDrawingPoints()
{
    return this->_vertexes;
}
