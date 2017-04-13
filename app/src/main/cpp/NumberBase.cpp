//
// Created by kamil7 on 2017-04-11.
//

#include "NumberBase.h"

float NumberBase::_halfNumberSize = NUMBER_SIZE/2.0f;
float NumberBase::_marginNumber = _halfNumberSize/5.0f;
NumberDirectory NumberBase::_numberDirectory {
        { "0", NumberBase::getNumber0 },
        { "1", NumberBase::getNumber1 },
        { "2", NumberBase::getNumber2 },
        { "3", NumberBase::getNumber3 },
        { "4", NumberBase::getNumber4 },
        { "5", NumberBase::getNumber5 },
        { "6", NumberBase::getNumber6 },
        { "7", NumberBase::getNumber7 },
        { "8", NumberBase::getNumber8 },
        { "9", NumberBase::getNumber9 }
};

// .4 .5
// .2 .3
// .0 .1
std::vector<glm::vec2> NumberBase::_points {
        { glm::vec2(-(_halfNumberSize - _marginNumber), -_halfNumberSize) },
        { glm::vec2((_halfNumberSize - _marginNumber), -_halfNumberSize) },
        { glm::vec2(-(_halfNumberSize - _marginNumber), 0.0f) },
        { glm::vec2((_halfNumberSize - _marginNumber), 0.0f) },
        { glm::vec2(-(_halfNumberSize - _marginNumber), _halfNumberSize) },
        { glm::vec2((_halfNumberSize - _marginNumber), _halfNumberSize) }
};

std::vector<float> NumberBase::getNumber(std::string numberChar)
{
    std::vector<float> result;
    getNumberFuntionPointer wantedFunction = _numberDirectory.at(numberChar);
    result = wantedFunction();

    return result;
}

std::vector<float> NumberBase::getNumber0()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(0), _points.at(1));
    addPointsToVector(result, _points.at(1), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(4));
    addPointsToVector(result, _points.at(4), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber1()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(1), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(2));

    return result;
}

std::vector<float> NumberBase::getNumber2()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(3));
    addPointsToVector(result, _points.at(2), _points.at(3));
    addPointsToVector(result, _points.at(2), _points.at(0));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber3()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(3));
    addPointsToVector(result, _points.at(2), _points.at(3));
    addPointsToVector(result, _points.at(3), _points.at(1));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber4()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(1), _points.at(5));
    addPointsToVector(result, _points.at(4), _points.at(2));
    addPointsToVector(result, _points.at(2), _points.at(3));

    return result;
}

std::vector<float> NumberBase::getNumber5()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(4), _points.at(2));
    addPointsToVector(result, _points.at(2), _points.at(3));
    addPointsToVector(result, _points.at(3), _points.at(1));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;

}

std::vector<float> NumberBase::getNumber6()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(4), _points.at(0));
    addPointsToVector(result, _points.at(2), _points.at(3));
    addPointsToVector(result, _points.at(3), _points.at(1));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber7()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber8()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(0), _points.at(4));
    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(5), _points.at(1));
    addPointsToVector(result, _points.at(3), _points.at(2));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;
}

std::vector<float> NumberBase::getNumber9()
{
    std::vector<float> result;

    addPointsToVector(result, _points.at(4), _points.at(5));
    addPointsToVector(result, _points.at(4), _points.at(2));
    addPointsToVector(result, _points.at(2), _points.at(3));
    addPointsToVector(result, _points.at(5), _points.at(1));
    addPointsToVector(result, _points.at(1), _points.at(0));

    return result;
}

void NumberBase::addPointsToVector(std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint)
{
    doubleVector.push_back(firstPoint[0]);
    doubleVector.push_back(firstPoint[1]);
    doubleVector.push_back(0.0f);

    doubleVector.push_back(secondPoint[0]);
    doubleVector.push_back(secondPoint[1]);
    doubleVector.push_back(0.0f);
};