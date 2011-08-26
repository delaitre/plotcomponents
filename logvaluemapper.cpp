#include "logvaluemapper.hpp"
#include <cmath>

LogValueMapper::LogValueMapper(QObject* parent)
    : ValueMapper(parent)
{
}

double LogValueMapper::mapped(double value) const
{
    value = log10(value);
    if (value == NAN || value == -HUGE_VAL)
        value = 0;
    return value;
}

double LogValueMapper::invMapped(double value) const
{
    value = exp10(value);
    if (value == NAN || value == -HUGE_VAL)
        value = 0;
    return value;
}
