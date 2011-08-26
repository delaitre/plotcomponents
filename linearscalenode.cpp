#include "linearscalenode.hpp"
#include "linearscale.hpp"
#include "scalemap.hpp"

LinearScaleNode::LinearScaleNode()
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    m_geometry.setDrawingMode(GL_LINES);
    m_material.setColor(Qt::black);
    setMaterial(&m_material);
    setGeometry(&m_geometry);
}

QColor LinearScaleNode::color() const
{
    return m_material.color();
}

void LinearScaleNode::setColor(const QColor &color)
{
    if (color != m_material.color()) {
        m_material.setColor(color);
        markDirty(QSGNode::DirtyMaterial);
    }
}

void LinearScaleNode::updateFromLinearScale(LinearScale* scale)
{
    ScaleMap* scaleMap = scale->scaleMap();
    if (!scaleMap)
    {
        m_geometry.allocate(0);
        markDirty(QSGNode::DirtyGeometry);
        return;
    }

    double width = scale->width();
    double height = scale->height();
    Qt::Orientation orientation = scale->orientation();

    QVector<double> ticks;
    ticks << 1 << 10 << 100 << 1000 << 10000;
    //for (int i = 0; i < 30; ++i)
    //    ticks << (i * scaleMap->pixelLength() / 30);
    int tickCount = ticks.count();

    m_geometry.allocate(tickCount * 2 + 2); // 2 vertices per tick + 2 vertices for the baseline
    QSGGeometry::Point2D* vertex = m_geometry.vertexDataAsPoint2D();

    // Ticks
    for (int i = 0; i < tickCount; ++i)
    {
        double pixelPos = scaleMap->mapToPixel(ticks[i]);

        if (orientation == Qt::Horizontal)
        {
            vertex[i * 2].x = pixelPos;
            vertex[i * 2].y = height;
            vertex[i * 2 + 1].x = pixelPos;
            vertex[i * 2 + 1].y = 0.;
        }
        else
        {
            pixelPos = height - pixelPos; // y = 0 is at the top, so we subtract from the height

            vertex[i * 2].x = width;
            vertex[i * 2].y = pixelPos;
            vertex[i * 2 + 1].x = 0;
            vertex[i * 2 + 1].y = pixelPos;
        }
    }

    // Baseline
    QSGGeometry::Point2D& baselineFrom = vertex[m_geometry.vertexCount() - 2];
    QSGGeometry::Point2D& baselineTo = vertex[m_geometry.vertexCount() - 1];
    if (orientation == Qt::Horizontal)
    {
        baselineFrom.x = 0;
        baselineFrom.y = 0;
        baselineTo.x = width;
        baselineTo.y = 0;
    }
    else
    {
        baselineFrom.x = width;
        baselineFrom.y = height;
        baselineTo.x = width;
        baselineTo.y = 0;
    }

    markDirty(QSGNode::DirtyGeometry);
}
