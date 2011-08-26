#ifndef VALUEMAPPER_HPP
#define VALUEMAPPER_HPP

#include <QtDeclarative/qdeclarative.h>
#include <QtCore/QObject>

class ValueMapper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ValueMapper)

public:

    explicit ValueMapper(QObject *parent = 0);

    Q_INVOKABLE virtual double mapped(double value) const;
    Q_INVOKABLE virtual double invMapped(double value) const;
};

QML_DECLARE_TYPE(ValueMapper)

#endif // VALUEMAPPER_HPP
