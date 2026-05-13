#pragma once
#include <QString>
#include <string>

#include "deixtralg.hpp"

class FacadeCalculator
{
public:
    double calcExpression(QString exp);

private:
    double _calcExp(std::string _exp);
    
};

