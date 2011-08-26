#ifndef LOGVALUEMAPPER_HPP
#define LOGVALUEMAPPER_HPP

#include "valuemapper.hpp"

class LogValueMapper : public ValueMapper
{
    Q_OBJECT
    Q_DISABLE_COPY(LogValueMapper)

public:

    explicit LogValueMapper(QObject *parent = 0);

    Q_INVOKABLE virtual double mapped(double value) const;
    Q_INVOKABLE virtual double invMapped(double value) const;
};

QML_DECLARE_TYPE(LogValueMapper)

#endif // LOGVALUEMAPPER_HPP
