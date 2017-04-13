//
// Created by kamil7 on 2017-04-11.
//

#ifndef GAME_NUMBERBASE_H
#define GAME_NUMBERBASE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "SharedData.h"

typedef std::vector<float> (*getNumberFuntionPointer)(); // function pointer type
typedef std::unordered_map<std::string, getNumberFuntionPointer> NumberDirectory;

class NumberBase {
public:
    static void addPointsToVector(std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint);
    static std::vector<float> getNumber(std::string letterChar);

    static std::vector<float> getNumber0();
    static std::vector<float> getNumber1();
    static std::vector<float> getNumber2();
    static std::vector<float> getNumber3();
    static std::vector<float> getNumber4();
    static std::vector<float> getNumber5();
    static std::vector<float> getNumber6();
    static std::vector<float> getNumber7();
    static std::vector<float> getNumber8();
    static std::vector<float> getNumber9();
private:
    static float _halfNumberSize;
    static float _marginNumber;
    static NumberDirectory _numberDirectory;
    static std::vector<glm::vec2> _points;
};


#endif //GAME_NUMBERBASE_H
