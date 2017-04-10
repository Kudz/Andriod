//
// Created by kamil7 on 2017-04-10.
//

#include "BrickDescription.h"

BrickDescription::BrickDescription()
{
    this->_vertexes.clear();
    double xOffset = 0.15;
    double yOffset = 0.04;
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

std::vector<double> BrickDescription::getDrawingPoints()
{
    return this->_vertexes;
}
