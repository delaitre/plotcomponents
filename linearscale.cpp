#include "linearscale.hpp"
#include "linearscalenode.hpp"
#include "scalemap.hpp"

LinearScale::LinearScale(QSGItem* parent)
    : QSGItem(parent)
    , m_scaleMap(0)
    , m_orientation(Qt::Horizontal)
{
    setFlag(ItemHasContents);
}

ScaleMap* LinearScale::scaleMap() const
{
    return m_scaleMap;
}

void LinearScale::setScaleMap(ScaleMap* scaleMap)
{
    if (m_scaleMap != scaleMap)
    {
        m_scaleMap = scaleMap;
        emit scaleMapChanged(scaleMap);
    }
}

Qt::Orientation LinearScale::orientation() const
{
    return m_orientation;
}

void LinearScale::setOrientation(Qt::Orientation orientation)
{
    if (m_orientation != orientation)
    {
        m_orientation = orientation;
        emit orientationChanged(orientation);
    }
}

void LinearScale::geometryChanged(const QRectF &newGeometry,
                                  const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry);

    if (!m_scaleMap)
        return;

    if (m_orientation == Qt::Horizontal)
        m_scaleMap->setPixelLength(newGeometry.width());
    else
        m_scaleMap->setPixelLength(newGeometry.height());
}

QSGNode* LinearScale::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);

    if (width() <= 0 || height() <= 0)
    {
        delete oldNode;
        return 0;
    }

    LinearScaleNode* scaleNode = static_cast<LinearScaleNode*>(oldNode);
    if (!scaleNode)
        scaleNode = new LinearScaleNode;

    scaleNode->updateFromLinearScale(this);

    return scaleNode;
}
