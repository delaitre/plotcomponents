#include "valuemapper.hpp"

ValueMapper::ValueMapper(QObject* parent)
    : QObject(parent)
{
}

double ValueMapper::mapped(double value) const
{
    // No mapping by default
    return value;
}

double ValueMapper::invMapped(double value) const
{
    // No mapping by default
    return value;
}
