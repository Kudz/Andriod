//
// Created by kamil7 on 2017-04-08.
//

#include "BoundaryDescription.h"

BoundaryDescription::BoundaryDescription()
{
    this->_vertexes.clear();

//    glm::vec2 point1(-0.98f, -0.9f);
//    glm::vec2 point2(-0.98f, 0.7f);
//    glm::vec2 point3(0.98f, 0.7f);
//    glm::vec2 point4(0.98f, -0.9f);

    glm::vec2 point1(LEFT_SCREEN_POSITION, BOTTOM_SCREEN_POSITION);
    glm::vec2 point2(LEFT_SCREEN_POSITION, TOP_SCREEN_POSITION);
    glm::vec2 point3(RIGHT_SCREEN_POSITION, TOP_SCREEN_POSITION);
    glm::vec2 point4(RIGHT_SCREEN_POSITION, BOTTOM_SCREEN_POSITION);

    auto addPointsToVector = [](std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint)
    {
        doubleVector.push_back(firstPoint[0]);
        doubleVector.push_back(firstPoint[1]);
        doubleVector.push_back(0.0f);

        doubleVector.push_back(secondPoint[0]);
        doubleVector.push_back(secondPoint[1]);
        doubleVector.push_back(0.0f);
    };

    addPointsToVector(this->_vertexes, point1, point2);
    addPointsToVector(this->_vertexes, point2, point3);
    addPointsToVector(this->_vertexes, point3, point4);
    addPointsToVector(this->_vertexes, point4, point1);
}

std::vector<float> BoundaryDescription::getDrawingPoints()
{
    return this->_vertexes;
}
