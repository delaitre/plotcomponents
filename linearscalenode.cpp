#include "linearscalenode.hpp"
#include "linearscale.hpp"
#include "scalemap.hpp"

LinearScaleNode::LinearScaleNode()
    : m_geometry(QSGGeometry::defaultAttributes_Point2D(), 0)
{
    m_geometry.setDrawingMode(GL_QUADS);
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
    double baselineThickness = 3;
    double tickThickness = 1;

    // Draw each tick with three rectangles:
    //  - one for the baseline part to go the tick
    //  - one for the tick itself
    //  - one for the part owned by both the baseline and the tick

    // vertical:              horizontal:
    // .----.--.              .------.--.
    // |tick|  |              |  bl  |  |
    // .----.--.              .------.--.
    //      |  |                     |ti|
    //      |bl|                     |ck|
    //      |  |                     .--.
    //      .--.

    // Then, draw a rectangle for the end of the baseline
    m_geometry.allocate(tickCount * 4 * 3 + 4);
    QSGGeometry::Point2D* vertex = m_geometry.vertexDataAsPoint2D();

    if (orientation == Qt::Horizontal)
    {
        double lastPos = 0.;

        for (int i = 0; i < tickCount; ++i)
        {
            double tickPos = scaleMap->mapToPixel(ticks[i]);
            double tickPosFrom = tickPos - tickThickness / 2.;
            double tickPosTo = tickPos + tickThickness / 2.;

            // Baseline to the tick
            vertex[i * 12 + 0].x = lastPos;
            vertex[i * 12 + 0].y = 0.;
            vertex[i * 12 + 1].x = tickPosFrom;
            vertex[i * 12 + 1].y = 0.;
            vertex[i * 12 + 2].x = tickPosFrom;
            vertex[i * 12 + 2].y = baselineThickness;
            vertex[i * 12 + 3].x = lastPos;
            vertex[i * 12 + 3].y = baselineThickness;

            // Part owned by both
            vertex[i * 12 + 4].x = tickPosFrom;
            vertex[i * 12 + 4].y = 0.;
            vertex[i * 12 + 5].x = tickPosTo;
            vertex[i * 12 + 5].y = 0.;
            vertex[i * 12 + 6].x = tickPosTo;
            vertex[i * 12 + 6].y = baselineThickness;
            vertex[i * 12 + 7].x = tickPosFrom;
            vertex[i * 12 + 7].y = baselineThickness;

            // Tick
            vertex[i * 12 + 8].x = tickPosFrom;
            vertex[i * 12 + 8].y = baselineThickness;
            vertex[i * 12 + 9].x = tickPosTo;
            vertex[i * 12 + 9].y = baselineThickness;
            vertex[i * 12 + 10].x = tickPosTo;
            vertex[i * 12 + 10].y = height;
            vertex[i * 12 + 11].x = tickPosFrom;
            vertex[i * 12 + 11].y = height;

            lastPos = tickPosTo;
        }

        // End of the baseline
        vertex[tickCount * 12 + 0].x = lastPos;
        vertex[tickCount * 12 + 0].y = 0.;
        vertex[tickCount * 12 + 1].x = width;
        vertex[tickCount * 12 + 1].y = 0.;
        vertex[tickCount * 12 + 2].x = width;
        vertex[tickCount * 12 + 2].y = baselineThickness;
        vertex[tickCount * 12 + 3].x = lastPos;
        vertex[tickCount * 12 + 3].y = baselineThickness;
    }
    else
    {
        double lastPos = height;

        for (int i = 0; i < tickCount; ++i)
        {
            double tickPos = height - scaleMap->mapToPixel(ticks[i]);
            double tickPosFrom = tickPos + tickThickness / 2.;
            double tickPosTo = tickPos - tickThickness / 2.;

            // Baseline to the tick
            vertex[i * 12 + 0].x = width;
            vertex[i * 12 + 0].y = lastPos;
            vertex[i * 12 + 1].x = width;
            vertex[i * 12 + 1].y = tickPosFrom;
            vertex[i * 12 + 2].x = width - baselineThickness;
            vertex[i * 12 + 2].y = tickPosFrom;
            vertex[i * 12 + 3].x = width - baselineThickness;
            vertex[i * 12 + 3].y = lastPos;

            // Part owned by both
            vertex[i * 12 + 4].x = width;
            vertex[i * 12 + 4].y = tickPosFrom;
            vertex[i * 12 + 5].x = width;
            vertex[i * 12 + 5].y = tickPosTo;
            vertex[i * 12 + 6].x = width - baselineThickness;
            vertex[i * 12 + 6].y = tickPosTo;
            vertex[i * 12 + 7].x = width - baselineThickness;
            vertex[i * 12 + 7].y = tickPosFrom;

            // Tick
            vertex[i * 12 + 8].x = width - baselineThickness;
            vertex[i * 12 + 8].y = tickPosFrom;
            vertex[i * 12 + 9].x = width - baselineThickness;
            vertex[i * 12 + 9].y = tickPosTo;
            vertex[i * 12 + 10].x = 0.;
            vertex[i * 12 + 10].y = tickPosTo;
            vertex[i * 12 + 11].x = 0.;
            vertex[i * 12 + 11].y = tickPosFrom;

            lastPos = tickPosTo;
        }

        // End of the baseline
        vertex[tickCount * 12 + 0].x = width;
        vertex[tickCount * 12 + 0].y = lastPos;
        vertex[tickCount * 12 + 1].x = width;
        vertex[tickCount * 12 + 1].y = 0.;
        vertex[tickCount * 12 + 2].x = width - baselineThickness;
        vertex[tickCount * 12 + 2].y = 0.;
        vertex[tickCount * 12 + 3].x = width - baselineThickness;
        vertex[tickCount * 12 + 3].y = lastPos;
    }

    markDirty(QSGNode::DirtyGeometry);
}
