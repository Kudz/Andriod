//
// Created by kamil7 on 2017-04-10.
//

#ifndef GAME_LETTERBASE_H
#define GAME_LETTERBASE_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "SharedData.h"

typedef std::vector<float> (*getLetterFuntionPointer)(float xPosition, float yPosition); // function pointer type
typedef std::unordered_map<std::string, getLetterFuntionPointer> LetterDictionary;

class LetterBase {
public:
    static void addPointsToVector(std::vector<float>& doubleVector, glm::vec2 firstPoint, glm::vec2 secondPoint);
    static std::vector<float> getLetter(std::string letterChar, float xPosition, float yPosition);

    static std::vector<float> getLetterC(float xPosition, float yPosition);
    static std::vector<float> getLetterE(float xPosition, float yPosition);
    static std::vector<float> getLetterF(float xPosition, float yPosition);
    static std::vector<float> getLetterI(float xPosition, float yPosition);
    static std::vector<float> getLetterL(float xPosition, float yPosition);
    static std::vector<float> getLetterO(float xPosition, float yPosition);
    static std::vector<float> getLetterR(float xPosition, float yPosition);
    static std::vector<float> getLetterS(float xPosition, float yPosition);
    static std::vector<float> getLetterT(float xPosition, float yPosition);
private:
    static float _halfLetterSize;
    static float _marginLetter;
    static LetterDictionary _letterDictionary;
};


#endif //GAME_LETTERBASE_H
