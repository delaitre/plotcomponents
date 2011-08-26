#include "curvenode.hpp"
#include "curve.hpp"
#include "scalemap.hpp"

CurveNode::CurveNode()
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    m_geometry.setDrawingMode(GL_LINE_STRIP);
    m_material.setColor(Qt::red);
    setMaterial(&m_material);
    setGeometry(&m_geometry);
}

QColor CurveNode::color() const
{
    return m_material.color();
}

void CurveNode::setColor(const QColor &color)
{
    if (color != m_material.color()) {
        m_material.setColor(color);
        markDirty(QSGNode::DirtyMaterial);
    }
}

void CurveNode::updateFromCurve(Curve* curve)
{
    ScaleMap* xScaleMap = curve->xScaleMap();
    ScaleMap* yScaleMap = curve->yScaleMap();
    if (!xScaleMap || !yScaleMap)
    {
        m_geometry.allocate(0);
        markDirty(QSGNode::DirtyGeometry);
        return;
    }

    double height = curve->height();
    const QVector<double>& data = curve->data();

    m_geometry.allocate(data.size() / 2);
    QSGGeometry::Point2D* vertex = m_geometry.vertexDataAsPoint2D();

    for (int i = 0; i < m_geometry.vertexCount(); ++i)
    {
        vertex[i].x = xScaleMap->mapToPixel(data[i * 2]);
        vertex[i].y = height - yScaleMap->mapToPixel(data[i * 2 + 1]); // y = 0 is at the top, so we subtract from the height
    }

    markDirty(QSGNode::DirtyGeometry);
}
