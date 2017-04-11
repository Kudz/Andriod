//
// Created by kamil7 on 2017-04-10.
//

#include "LetterBase.h"

float LetterBase::_halfLetterSize = LETTER_SIZE/2.0f;
float LetterBase::_marginLetter = _halfLetterSize/5.0f;
LetterDictionary LetterBase::_letterDictionary {
        { "C", LetterBase::getLetterC },
        { "E", LetterBase::getLetterE },
        { "F", LetterBase::getLetterF },
        { "I", LetterBase::getLetterI },
        { "L", LetterBase::getLetterL },
        { "O", LetterBase::getLetterO },
        { "R", LetterBase::getLetterR },
        { "S", LetterBase::getLetterS },
        { "T", LetterBase::getLetterT }
};

std::vector<float> LetterBase::getLetter(std::string letterChar, float xPosition, float yPosition)
{
    std::vector<float> result;
    getLetterFuntionPointer wantedFunction = _letterDictionary.at(letterChar);
    result = wantedFunction(xPosition, yPosition);

    return result;
}

std::vector<float> LetterBase::getLetterC(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point3, point4);

    return result;
}

std::vector<float> LetterBase::getLetterE(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point5(xPosition - (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point6(xPosition + (_halfLetterSize - _marginLetter), yPosition);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point3, point4);
    addPointsToVector(result, point5, point6);

    return result;
}

std::vector<float> LetterBase::getLetterF(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point3(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition - (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point5(xPosition + (_halfLetterSize - _marginLetter), yPosition);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point4, point5);

    return result;
}

std::vector<float> LetterBase::getLetterI(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point5(xPosition, yPosition + _halfLetterSize);
    glm::vec2 point6(xPosition, yPosition - _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point3, point4);
    addPointsToVector(result, point5, point6);

    return result;
}

std::vector<float> LetterBase::getLetterL(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);

    return result;
}

std::vector<float> LetterBase::getLetterO(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point3, point4);
    addPointsToVector(result, point4, point1);

    return result;

}

std::vector<float> LetterBase::getLetterR(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point3(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition + (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point5(xPosition - (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point6(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point3, point4);
    addPointsToVector(result, point4, point5);
    addPointsToVector(result, point5, point6);

    return result;
}

std::vector<float> LetterBase::getLetterS(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition - (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point2(xPosition + (_halfLetterSize - _marginLetter), yPosition - _halfLetterSize);
    glm::vec2 point3(xPosition + (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point4(xPosition - (_halfLetterSize - _marginLetter), yPosition);
    glm::vec2 point5(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point6(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point2, point3);
    addPointsToVector(result, point3, point4);
    addPointsToVector(result, point4, point5);
    addPointsToVector(result, point5, point6);

    return result;
}

std::vector<float> LetterBase::getLetterT(float xPosition, float yPosition)
{
    std::vector<float> result;

    glm::vec2 point1(xPosition - (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point2(xPosition + (_halfLetterSize - _marginLetter), yPosition + _halfLetterSize);
    glm::vec2 point3(xPosition, yPosition + _halfLetterSize);
    glm::vec2 point4(xPosition, yPosition - _halfLetterSize);

    addPointsToVector(result, point1, point2);
    addPointsToVector(result, point3, point4);

    return result;
}

void LetterBase::addPointsToVector(std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint)
{
    doubleVector.push_back(firstPoint[0]);
    doubleVector.push_back(firstPoint[1]);
    doubleVector.push_back(0.0f);

    doubleVector.push_back(secondPoint[0]);
    doubleVector.push_back(secondPoint[1]);
    doubleVector.push_back(0.0f);
};