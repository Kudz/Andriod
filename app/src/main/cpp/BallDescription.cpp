//
// Created by kamil7 on 2017-04-08.
//

#include "BallDescription.h"

BallDescription::BallDescription()
{
    std::vector<glm::vec2> circlePoints = this->createCircle(BALL_RADIUS, 20);
    this->_vertexes.clear();

    auto addPointsToVector = [](std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint)
    {
        doubleVector.push_back(0.0f);
        doubleVector.push_back(0.0f);
        doubleVector.push_back(0.0f);

        doubleVector.push_back(firstPoint[0]);
        doubleVector.push_back(firstPoint[1]);
        doubleVector.push_back(0.0f);

        doubleVector.push_back(secondPoint[0]);
        doubleVector.push_back(secondPoint[1]);
        doubleVector.push_back(0.0f);
    };

    for(uint i = 0; i < circlePoints.size(); i++)
    {
        if(i == 0)
        {
            addPointsToVector(this->_vertexes, circlePoints.at(circlePoints.size() - 1), circlePoints.at(i));
        }
        else
        {
            addPointsToVector(this->_vertexes, circlePoints.at(i-1), circlePoints.at(i));
        }

    }
//    SharedData::logInfo(LOG_BALL_TAG, "end Of Ball description constructor");
}

std::vector<float> BallDescription::getDrawingPoints()
{
    return this->_vertexes;
}

std::vector<glm::vec2> BallDescription::createCircle(float radius, int pointsAmount)
{
    float stepAngleValue = 2*M_PI/pointsAmount;
    std::vector<glm::vec2> result;
    for(uint i = 0; i < pointsAmount; i++)
    {
        float xValue = cosf(stepAngleValue*i)*radius;
        float yValue = sinf(stepAngleValue*i)*radius;
        result.push_back(glm::vec2(xValue, yValue));
    }
    return result;
}