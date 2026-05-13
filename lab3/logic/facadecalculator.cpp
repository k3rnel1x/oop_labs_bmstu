#include "facadecalculator.hpp"

double FacadeCalculator::calcExpression(QString exp)
{
    QByteArray ba = exp.toUtf8();
    return _calcExp(std::string(ba.constData()));
}

double FacadeCalculator::_calcExp(std::string _exp)
{
    std::string postfix = toPostfix(_exp);
    return calcInPostfix(postfix);
}