#include "curve.hpp"
#include "curvenode.hpp"
#include "scalemap.hpp"
#include <cmath>

namespace
{

QPainterPath buildCurve(int pointCount)
{
    QPainterPath path;
    double sinStep = 4 * (2 * 3.1415) / pointCount;
    for (int i = 0; i < pointCount; ++i)
    {
        path.lineTo(i * (10000. / pointCount), i * (10000. / pointCount));
        //path.lineTo(i, sin(i * sinStep));
    }

    return path;
}

} // anonymous namespace

Curve::Curve(QQuickItem *parent)
    : QQuickItem(parent)
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

    m_curve = buildCurve(4000);
    curveNode->updateFromCurve(this, m_curve);

    return curveNode;
}
