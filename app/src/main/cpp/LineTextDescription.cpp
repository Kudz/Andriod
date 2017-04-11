//
// Created by kamil7 on 2017-04-10.
//

#include "LineTextDescription.h"

LineTextDescription::LineTextDescription(std::string text)
{
    for(uint i = 0; i < text.size(); i++)
    {
        float xOffset = 0.11f;
        float yOffset = 0.3f;
        std::vector<float> points = LetterBase::getLetter(text.substr(i,1), xOffset*i, 0.0f);
        this->_vertexes.insert(std::end(this->_vertexes), std::begin(points), std::end(points));
    }
}

std::vector<float> LineTextDescription::getDrawingPoints()
{
    return this->_vertexes;
}