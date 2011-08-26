#include "scalemap.hpp"
#include "valuemapper.hpp"

ScaleMap::ScaleMap(QObject* parent)
    : QObject(parent)
    , m_valueMapper(0)
    , m_scaleMinimum(0)
    , m_scaleMaximum(1000)
    , m_pixelLength(0)
{
    update();
}

ValueMapper* ScaleMap::valueMapper() const
{
    return m_valueMapper;
}

void ScaleMap::setValueMapper(ValueMapper* mapper)
{
    if (m_valueMapper != mapper)
    {
        m_valueMapper = mapper;
        update();
        emit valueMapperChanged(mapper);
    }
}

double ScaleMap::scaleMinimum() const
{
    return m_scaleMinimum;
}

void ScaleMap::setScaleMinimum(double minimum)
{
    if (m_scaleMinimum != minimum)
    {
        m_scaleMinimum = minimum;
        update();
        emit scaleMinimumChanged(minimum);
    }
}

double ScaleMap::scaleMaximum() const
{
    return m_scaleMaximum;
}

void ScaleMap::setScaleMaximum(double maximum)
{
    if (m_scaleMaximum != maximum)
    {
        m_scaleMaximum = maximum;
        update();
        emit scaleMaximumChanged(maximum);
    }
}

double ScaleMap::pixelLength() const
{
    return m_pixelLength;
}

void ScaleMap::setPixelLength(double length)
{
    if (m_pixelLength != length && length >= 0.)
    {
        m_pixelLength = length;
        update();
        emit pixelLengthChanged(length);
    }
}

double ScaleMap::mapToPixel(double scaleValue) const
{
    Q_ASSERT(m_valueMapper);

    // Corner case if the scale range is invalid
    if (m_pixelLengthDivMappedScaleRange <= 0.)
        return 0.;

    // The function to map a scale value to a pixel one is the following linear interpolation:
    // pixelValue = pixelMin + (pixelMax - pixelMin) * (f(scaleValue) - f(scaleMin)) / (f(scaleMax) - f(scaleMin))
    // The function f is the mapping function implemented in the value mapper (e.g. identity or log)
    // As some values are cached in the update() function, this leads us to the following optimized code

    return m_pixelLengthDivMappedScaleRange * (m_valueMapper->mapped(scaleValue) - m_mappedScaleMinimum);
}

double ScaleMap::mapToScale(double pixelValue) const
{
    Q_ASSERT(m_valueMapper);

    // Corner case if the pixel length is invalid
    if (m_pixelLength <= 0.)
        return 0.;

    // The function to map a pixel value to a scale is the following linear interpolation:
    // scaleValue = invF(f(scaleMin) + (pixelValue - pixelMin) * (f(scaleMax) - f(scaleMin)) / (pixelMax - pixelMin))
    // The function f is the mapping function implemented in the value mapper (e.g. identity or log)
    // The function invF is the inverse function of f (e.g. identity for identity, exp for log)
    // As some values are cached in the update() function, this leads us to the following optimized code

    return m_valueMapper->invMapped(m_mappedScaleMinimum + pixelValue / m_pixelLengthDivMappedScaleRange);
}

void ScaleMap::update()
{
    if (m_valueMapper)
    {
        // Update cache values
        m_mappedScaleMinimum = m_valueMapper->mapped(m_scaleMinimum);
        double mappedScaleRange = m_valueMapper->mapped(m_scaleMaximum) - m_mappedScaleMinimum;
        if (m_pixelLength <= 0. || mappedScaleRange <= 0.)
            m_pixelLengthDivMappedScaleRange = 0.;
        else
            m_pixelLengthDivMappedScaleRange = m_pixelLength / mappedScaleRange;
    }
    else
    {
        m_mappedScaleMinimum = 0.;
        m_pixelLengthDivMappedScaleRange = 0.;
    }
}
