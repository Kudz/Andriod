//
// Created by kamil7 on 2017-04-11.
//

#include "NumberDescription.h"

NumberDescription::NumberDescription(std::string text)
{
    std::vector<float> points = NumberBase::getNumber(text);
    this->_vertexes.insert(std::end(this->_vertexes), std::begin(points), std::end(points));
}

std::vector<float> NumberDescription::getDrawingPoints()
{
    return this->_vertexes;
}