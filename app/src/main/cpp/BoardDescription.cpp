//
// Created by kamil7 on 2017-04-06.
//

#include "BoardDescription.h"

BoardDescription::BoardDescription()
{
    this->_vertexes.clear();
    double xOffset = BOARD_WIDTH/2;
    double yOffset = BOARD_HEIGHT/2;
    double zOffset = 0.0;

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

std::vector<float> BoardDescription::getDrawingPoints()
{
    return this->_vertexes;
}
