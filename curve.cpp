#include "curve.hpp"
#include "curvenode.hpp"
#include "scalemap.hpp"
#include <cmath>

namespace
{

QVector<double> buildCurve(int pointCount)
{
    QVector<double> data;
    data.reserve(pointCount * 2);
    double sinStep = 4 * (2 * 3.1415) / pointCount;
    for (int i = 0; i < pointCount; ++i)
    {
        data << i * (10000. / pointCount);
        data << i * (10000. / pointCount);
        //data << sin(i * sinStep);
    }

    return data;
}

} // anonymous namespace

Curve::Curve(QSGItem *parent)
    : QSGItem(parent)
    , m_xScaleMap(0)
    , m_yScaleMap(0)
{
    setFlag(ItemHasContents);
    setClip(true); // enable clipping by default
}

ScaleMap* Curve::xScaleMap() const
{
    return m_xScaleMap;
}

void Curve::setXScaleMap(ScaleMap* scaleMap)
{
    if (m_xScaleMap != scaleMap)
    {
        m_xScaleMap = scaleMap;
        emit xScaleMapChanged(scaleMap);
    }
}

ScaleMap* Curve::yScaleMap() const
{
    return m_yScaleMap;
}

void Curve::setYScaleMap(ScaleMap* scaleMap)
{
    if (m_yScaleMap != scaleMap)
    {
        m_yScaleMap = scaleMap;
        emit yScaleMapChanged(scaleMap);
    }
}

const QVector<double>& Curve::data() const
{
    return m_data;
}

void Curve::geometryChanged(const QRectF &newGeometry,
                            const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry);

    if (m_xScaleMap)
        m_xScaleMap->setPixelLength(newGeometry.width());
    if (m_yScaleMap)
        m_yScaleMap->setPixelLength(newGeometry.height());
}

QSGNode* Curve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);

    if (width() <= 0 || height() <= 0)
    {
        delete oldNode;
        return 0;
    }

    CurveNode* curveNode = static_cast<CurveNode*>(oldNode);
    if (!curveNode)
        curveNode = new CurveNode;

    m_data = buildCurve(4000);
    curveNode->updateFromCurve(this);

    return curveNode;
}
