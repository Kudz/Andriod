//
// Created by kamil7 on 2017-04-06.
//

#include "BoardDescription.h"

BoardDescription::BoardDescription()
{
    this->_vertexes.clear();
    double xOffset = 0.2;
    double yOffset = 0.02;
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

std::vector<double> BoardDescription::getDrawingPoints()
{
    return this->_vertexes;
}
