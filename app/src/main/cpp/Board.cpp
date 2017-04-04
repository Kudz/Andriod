//
// Created by kamil7 on 2017-03-30.
//

#include "Board.h"

Board::Board()
: _boardWidth(0.4f), _boardHeight(0.04f)
{
    this->_screenHeight = SharedData::getScreenHeight();
    LOG_BOARD_SHADER_I("screen height = %d", this->_screenHeight);
    double xOffset = 0.2;
    double yOffset = 0.02;
    double zOffset = 0.0;

    std::vector<double> vertices;

    vertices.push_back(-xOffset);
    vertices.push_back(yOffset);
    vertices.push_back(zOffset);

    vertices.push_back(-xOffset);
    vertices.push_back(-yOffset);
    vertices.push_back(zOffset);

    vertices.push_back(xOffset);
    vertices.push_back(yOffset);
    vertices.push_back(zOffset);

    vertices.push_back(xOffset);
    vertices.push_back(-yOffset);
    vertices.push_back(zOffset);

    vertices.push_back(-xOffset);
    vertices.push_back(-yOffset);
    vertices.push_back(zOffset);

    vertices.push_back(xOffset);
    vertices.push_back(yOffset);
    vertices.push_back(zOffset);

    this->_vertexes = vertices;
}

void Board::setXPosition(int xPosition)
{
}

std::vector<double> Board::getDrawingPoints()
{
    return this->_vertexes;
}