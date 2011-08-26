#ifndef SCALEMAP_HPP
#define SCALEMAP_HPP

#include <QtDeclarative/qdeclarative.h>
#include <QtCore/QObject>
#include <QtCore/QPointer>

class ValueMapper;

class ScaleMap : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ScaleMap)

    Q_PROPERTY(ValueMapper* valueMapper READ valueMapper WRITE setValueMapper NOTIFY valueMapperChanged)
    Q_PROPERTY(double scaleMinimum READ scaleMinimum WRITE setScaleMinimum NOTIFY scaleMinimumChanged)
    Q_PROPERTY(double scaleMaximum READ scaleMaximum WRITE setScaleMaximum NOTIFY scaleMaximumChanged)
    Q_PROPERTY(double pixelLength READ pixelLength WRITE setPixelLength NOTIFY pixelLengthChanged)

public:

    explicit ScaleMap(QObject* parent = 0);

    ValueMapper* valueMapper() const;
    double scaleMinimum() const;
    double scaleMaximum() const;
    double pixelLength() const;

    Q_INVOKABLE double mapToPixel(double scaleValue) const;
    Q_INVOKABLE double mapToScale(double pixelValue) const;

public slots:

    void setValueMapper(ValueMapper* mapper);
    void setScaleMinimum(double minimum);
    void setScaleMaximum(double maximum);
    void setPixelLength(double length);

signals:

    void valueMapperChanged(ValueMapper* mapper);
    void scaleMinimumChanged(double minimum);
    void scaleMaximumChanged(double maximum);
    void pixelLengthChanged(double lenght);

private:

    void update();

private:

    QPointer<ValueMapper> m_valueMapper;
    double m_scaleMinimum;
    double m_scaleMaximum;
    double m_pixelLength;

    // Cached value
    double m_mappedScaleMinimum;
    double m_pixelLengthDivMappedScaleRange;
};

QML_DECLARE_TYPE(ScaleMap)

#endif // SCALEMAP_HPP
